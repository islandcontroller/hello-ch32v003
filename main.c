/*!****************************************************************************
 * @file
 * main.c
 *
 * @brief
 * "Hello World"-like demo project for the CH32V003 RISC-V MCU.
 *
 * This project contains a simple set of modules to get the MCU running in a
 * minimal configuration:
 *  - Polling-mode serial I/O on USART1 (connected to WCH-LinkE USART)
 * All project files are also available online at:
 *  https://github.com/islandcontroller/hello-ch32v003
 *
 * @date  11.02.2022
 * @date  14.02.2022  Added core information printout
 * @date  17.02.2022  Added clocks, ESig information printout
 * @date  17.02.2022  Added LED animation
 * @date  23.02.2022  Added remote echo and serial input commands processing
 * @date  24.02.2022  Added temperature sensor and Vrefint info printout
 * @date  03.03.2022  Modified to used printf(), putchar() and getchar()
 * @date  04.03.2022  Added EEPROM demo
 * @date  10.03.2022  Added information block readout; Disabled EEPROM demo for
 *                    default configuration
 * @date  21.03.2023  Adapted from hello-ch32v103 for hello-ch32v003
 * @date  23.03.2023  Added SysTick interrupt demo
 * @date  02.10.2023  Moved system time to hw_stk
 * @date  02.10.2023  Added LED demo
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ch32v00x.h"
#include "hw_init.h"
#include "hw_stk.h"
#include "syscalls.h"
#include "dbgser.h"
#include "led.h"


/*- Macros -------------------------------------------------------------------*/
/*! @brief Hexdump items per row                                              */
#define HEXDUMP_ROW_ITEMS             16UL


/*- Private variables --------------------------------------------------------*/
/*! String lookup for XLEN definition field                                   */
const char* const apszMisaMxl[4] = {
  "0 - (undefined)",
  "1 - 32-bit XLEN",
  "2 - 64-bit XLEN",
  "3 - 128-bit XLEN"
};

/*! Lookup table for ISA Extensions                                           */
const char* const apszMisaExt[26] = {
  "A - Atomic extension",
  "B - (reserved) Bit-Manipulation extension",
  "C - Compressed extension",
  "D - Double-precision floating-point extension",
  "E - RV32E base ISA",
  "F - Single-precision floating-point extension",
  "G - Additional standard extensions present",
  "H - Hypervisor extension",
  "I - RV32I/RV64I/RV128I base ISA",
  "J - (reserved) Dynamically Translated Languages extension",
  "K - (reserved)",
  "L - (reserved) Decimal Floating-Point extension",
  "M - Integer Multiply/Divide extension",
  "N - User-level interrupts supported",
  "O - (reserved)",
  "P - (reserved) Packed-SIMD extension",
  "Q - Quad-precision floating-point extension",
  "R - (reserved)",
  "S - Supervisor mode implemented",
  "T - (reserved) Transactional Memory extension",
  "U - User mode implemented",
  "V - (reserved) Vector extension",
  "W - (reserved)",
  "X - Non-standard extensions present",
  "Y - (reserved)",
  "Z - (reserved)"
};


/*- Private functions --------------------------------------------------------*/
/*!****************************************************************************
 * @brief
 * Print plain-text info from MISA

 * @date  12.02.2022
 * @date  03.03.2022  Modified to use printf()
 ******************************************************************************/
static void vPrintCoreInfo(void)
{
  uint32_t ulMArchId = __get_MARCHID();
  uint32_t ulMVendorId = __get_MVENDORID();
  uint32_t ulMImpId = __get_MIMPID();
  uint32_t ulMISA = __get_MISA();

  printf(
    "-- Core Information ------------------------------\r\n"
  );

  /* Print register values                                */
  printf("MARCHID:   0x%08lX\r\n", ulMArchId);
  printf("MIMPID:    0x%08lX\r\n", ulMImpId);
  printf("MVENDORID: 0x%08lX\r\n", ulMVendorId);
  printf("MISA:      0x%08lX\r\n", ulMISA);

  /* Print MXL configuration                              */
  unsigned uMxl = (ulMISA >> 30) & 0x3UL;
  printf("  MXL:\r\n    %s\r\n", apszMisaMxl[uMxl]);

  /* Print extensions information                         */
  printf("  Extensions:\r\n");
  for (unsigned i = 0; i < 26; ++i)
  {
    if (ulMISA & (1UL << i)) printf("    %s\r\n", apszMisaExt[i]);
  }
}

/*!****************************************************************************
 * @brief
 * Print plain-text system core clock information
 *
 * @note
 * Run SystemCoreClockUpdate() at least once before calling this function to
 * ensure HCLK value recalculation.
 *
 * @date  14.02.2022
 * @date  03.03.2022  Modified to use printf()
 ******************************************************************************/
static void vPrintSysCoreClk(void)
{
  printf(
    "-- Clocks ----------------------------------------\r\n"
  );

  unsigned uKHz = SystemCoreClock / 1000;
  unsigned uMHz = uKHz / 1000;
  unsigned uKHzRem = uKHz % 1000;
  printf("f_HCLK = %d.%03d MHz\r\n", uMHz, uKHzRem);
}

/*!****************************************************************************
 * @brief
 * Print flash size and device ID information
 *
 * @date  17.02.2022
 * @date  03.03.2022  Modified to use printf()
 ******************************************************************************/
static void vPrintEsigInfo(void)
{
  const volatile uint16_t* puiFlSize = (const void*)0x1FFFF7E0UL;
  const volatile uint32_t* pulUID = (const void*)0x1FFFF7E8UL;

  printf(
    "-- ESIG ------------------------------------------\r\n"
  );

  printf("FLASH Size: %d KB\r\n", *puiFlSize);
  printf("Unique ID: %08lX %08lX %08lX\r\n", pulUID[2], pulUID[1], pulUID[0]);
}

/*!****************************************************************************
 * @brief
 * Print Hexdump of memory buffer
 *
 * @param[in] *pBuffer    Data buffer
 * @param[in] uLen        Number of bytes to display
 * @param[in] uBaseAdr    Base address for row counters
 * @date  10.03.2022
 ******************************************************************************/
static void vPrintHexDump(const uint8_t* pBuffer, unsigned uLen, unsigned uBaseAdr)
{
  for (unsigned uRow = 0; uRow < uLen / HEXDUMP_ROW_ITEMS; ++uRow)
  {
    /* Address or Offset                                  */
    unsigned uRowAddr = uRow * HEXDUMP_ROW_ITEMS;
    printf("%08x  ", uRowAddr + uBaseAdr);

    /* Byte columns                                       */
    for (unsigned uCol = 0; uCol < HEXDUMP_ROW_ITEMS; ++uCol)
    {
      unsigned char ucData = pBuffer[uRowAddr + uCol];
      printf("%02x ", ucData);
      if (uCol == (HEXDUMP_ROW_ITEMS / 2 - 1)) putchar(' ');
    }

    /* ASCII text representation                          */
    putchar(' ');
    for (unsigned uCol = 0; uCol < HEXDUMP_ROW_ITEMS; ++uCol)
    {
      unsigned char ucData = pBuffer[uRowAddr + uCol];
      putchar(isprint(ucData) ? ucData : '.');
    }
    printf("\r\n");
  }
}

/*!****************************************************************************
 * @brief
 * Print User Sel. and Vendor Config. Words
 *
 * @date  10.03.2022
 * @date  21.03.2023  Amended for CH32V003
 ******************************************************************************/
static void vPrintInfoBlockWords(void)
{
  const void* pUserSelWord = (const void*)0x1FFFF800UL;
  const void* pVendConfWord = (const void*)0x1FFFF7C0UL;

  /* Hexdump printout                                     */
  printf("User selection word:\r\n");
  vPrintHexDump(pUserSelWord, 64, (unsigned)pUserSelWord);
  printf("Vendor configuration word:\r\n");
  vPrintHexDump(pVendConfWord, 64, (unsigned)pVendConfWord);
}

/*!****************************************************************************
 * @brief
 * Serial input processing
 *
 * @date  23.02.2022
 * @date  24.02.2022  Changed PFIC naming convention
 * @date  24.02.2022  Added analog inputs readout command; modified help text
 * @date  03.03.2022  Modified to use printf(), putchar(), getchar()
 * @date  04.03.2022  Added EEPROM readout demo
 * @date  10.03.2022  Added information block readout command
 * @date  21.03.2023  Removed analog, EEPROM for ch32v003
 * @date  23.03.2023  Added system timer value readout
 ******************************************************************************/
static void vPollSerial(void)
{
  /* Early exit, if no data is available                  */
  if (!bIsDbgSerAvailable()) return;

  /* Fetch character and print remote echo                */
  char c = getchar();
  printf("%c\r\n", c);

  /* Process command                                      */
  switch (c)
  {
    case '?':
      /* Show available commands                          */
      printf(
        "Available Commands:\r\n"
        "  ?    Show this help\r\n"
        "  i    Read information block\r\n"
        "  r    Reboot system\r\n"
        "  t    Print system time\r\n"
      );
      break;

    case 'i':
      /* Read information block                           */
      vPrintInfoBlockWords();
      break;

    case 'r':
      /* Reboot command                                   */
      PFIC_SystemReset();
      break;

    case 't':
      /* Print system time                                */
      printf("System time: %lu ms\r\n", ulHW_STKGetSystemTime());
      break;

    default:
      fprintf(stderr, "Unknown command. Press \"?\" to show available commands.\r\n");
  }

  /* Input prompt                                         */
  putchar('>');
  fflush(stdout);
}

/*!****************************************************************************
 * @brief
 * Main program entry point
 *
 * @date  11.02.2022
 * @date  14.02.2022  Added core information printout
 * @date  17.02.2022  Added clocks, ESig information printout
 * @date  17.02.2022  Added LED animation
 * @date  23.02.2022  Added serial input processing
 * @date  24.02.2022  Added help prompt
 * @date  03.03.2022  Modified to use printf()
 * @date  03.03.2022  Moved escape sequence into dbgser macro
 * @date  04.03.2022  Added EEPROM programming
 * @date  21.03.2023  Adapted for hello-ch32v003; Removed LED, Analog, EEPROM
 * @date  02.10.2023  Added LED demo
 ******************************************************************************/
int main(void)
{
  vInitHW();

  /* Init syscalls retargeting                            */
  vInitSyscalls();

  /* Init demos                                           */
  vInitLed();

  /* Print system info                                    */
  printf(
    VT100_CLEAR_TERM
    "--------------------------------------------------\r\n"
    "        ##                                        \r\n"
    "\r\n"
    "      ##    ######                                \r\n"
    "     ##  ##                                       \r\n"
    "    ##  ##                                        \r\n"
    "   ##    ######  ######                  @islandc_\r\n"
    "--------------------------------------------------\r\n"
    " MCU:  WCH CH32V003F4P6                           \r\n"
    " Core: RISC-V2A (RV32EC)                          \r\n"
    "--------------------------------------------------\r\n"
    "\r\n"
  );
  vPrintCoreInfo();
  printf("\r\n");
  vPrintSysCoreClk();
  printf("\r\n");
  vPrintEsigInfo();
  printf("\r\nPress \"?\" to show available commands.\r\n>");
  fflush(stdout);

  /* Main program loop                                    */
  while (1)
  {
    vPollSerial();
    vPollLed();
  }
}
