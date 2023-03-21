/*!****************************************************************************
 * @file
 * dbgser.h
 *
 * @brief
 * Serial output for debugging (debugger serial port)
 *
 * @date  11.02.2022
 * @date  23.02.2022  Added single-char write and blocking read
 * @date  03.03.2022  Added escape sequence macros
 ******************************************************************************/

#ifndef DBGSER_H_
#define DBGSER_H_

/*- Header files -------------------------------------------------------------*/
#include <stdbool.h>


/*- Macros -------------------------------------------------------------------*/
/*! Escape code to clear terminal output                                      */
#define VT100_CLEAR_TERM              "\x1b[2J"

/*! Escape code to change foreground color to bright red                      */
#define VT100_COLOR_FGRED             "\x1b[0;31m"

/*! Escape code to reset color options                                        */
#define VT100_COLOR_RESET             "\x1b[m"


/*- Exported functions -------------------------------------------------------*/
void vWriteDbgSer(const unsigned char* pucData, unsigned uLen);
void vPrintDbgSer(const char* pszStr);
void vPutCharDbgSer(char cData);
bool bIsDbgSerAvailable(void);
char cGetCharDbgSer(void);

#endif /* DBGSER_H_ */
