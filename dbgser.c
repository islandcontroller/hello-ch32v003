/*!****************************************************************************
 * @file
 * dbgser.c
 *
 * @brief
 * Serial output for debugging (debugger serial port)
 *
 * @date  11.02.2022
 * @date  23.02.2022  Added single-char write and blocking read
 * @date  21.03.2023  Adapted from hello-ch32v103 for hello-ch32v003
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"
#include "dbgser.h"


/*!****************************************************************************
 * @brief
 * Write data to serial debug output
 *
 * @param[in] *pucData    Data buffer
 * @param[in] uLen        Data length in bytes
 * @date  12.02.2022
 * @date  23.02.2022  Modified to use local function for single-char output
 ******************************************************************************/
void vWriteDbgSer(const unsigned char* pucData, unsigned uLen)
{
  for (unsigned i = 0; i < uLen; ++i) vPutCharDbgSer(pucData[i]);
}

/*!****************************************************************************
 * @brief
 * Print null-terminated string to serial debug output
 *
 * @param[in] *pszStr     Null-terminated string
 * @date  12.02.2022
 * @date  23.02.2022  Modified to use local function for single-char output
 ******************************************************************************/
void vPrintDbgSer(const char* pszStr)
{
  while (*pszStr != '\0') vPutCharDbgSer(*pszStr++);
}

/*!****************************************************************************
 * @brief
 * Write single character to serial debug output
 *
 * @param[in] cData       Output character
 * @date  23.02.2022
 ******************************************************************************/
void vPutCharDbgSer(char cData)
{
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
  USART_SendData(USART1, cData);
}

/*!****************************************************************************
 * @brief
 * Check if there is data in the RX buffer
 *
 * @return  (bool)      true, if data is present
 * @date  23.02.2022
 ******************************************************************************/
bool bIsDbgSerAvailable(void)
{
  return USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET;
}

/*!****************************************************************************
 * @brief
 * Blocking read single character from serial debug input
 *
 * @return  (char)      Received character (ASCII)
 * @date  23.02.2022
 ******************************************************************************/
char cGetCharDbgSer(void)
{
  while (!bIsDbgSerAvailable());
  return USART_ReceiveData(USART1);
}
