/*!****************************************************************************
 * @file
 * hw_usart1.h
 *
 * @brief
 * Low-level initialisation for USART1 (debugger serial port)
 *
 * @date  21.03.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"
#include "hw_usart1.h"


/*!****************************************************************************
 * @brief
 * Activate clock supply and initialise USART1 for 115200 Baud, 8n1.
 *
 * @date  21.03.2023
 ******************************************************************************/
void vInitHW_USART1(void)
{
  /* Enable peripheral clock supply                       */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  /* Configure peripheral                                 */
  USART_InitTypeDef sInit = {
    .USART_BaudRate = USART1_BAUD_RATE,
    .USART_WordLength = USART_WordLength_8b,
    .USART_Parity = USART_Parity_No,
    .USART_StopBits = USART_StopBits_1,
    .USART_Mode = USART_Mode_Tx | USART_Mode_Rx
  };
  USART_Init(USART1, &sInit);

  /* Start the peripheral                                 */
  USART_Cmd(USART1, ENABLE);
}
