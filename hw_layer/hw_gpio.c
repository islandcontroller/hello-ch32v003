/*!***************************************************************************
 * @file
 * hw_gpio.c
 *
 * @brief
 * Low-level GPIO setup
 *
 * @date  21.03.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"
#include "hw_iodefs.h"
#include "hw_gpio.h"


/*!****************************************************************************
 * @brief
 * Activate clocks and initialise GPIO pins
 *
 * @date  21.03.2023
 ******************************************************************************/
void vInitHW_GPIO(void)
{
  /* Enable peripheral clock supplies for used GPIO       */
  RCC_APB2PeriphClockCmd(GPIO_USED_PERIPH, ENABLE);

  /* USART1 Rx/Tx                                         */
  GPIO_InitTypeDef sInitUSART1TX = {
    .GPIO_Pin = USART1TX_GPIO_Pin,
    .GPIO_Mode = USART1TX_GPIO_Mode,
    .GPIO_Speed = GPIO_Speed_2MHz
  };
  GPIO_InitTypeDef sInitUSART1RX = {
    .GPIO_Pin = USART1RX_GPIO_Pin,
    .GPIO_Mode = USART1RX_GPIO_Mode
  };
  GPIO_Init(USART1RTX_GPIO_Port, &sInitUSART1TX);
  GPIO_Init(USART1RTX_GPIO_Port, &sInitUSART1RX);
}
