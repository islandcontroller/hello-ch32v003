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
 * @date  09.01.2024  Added UART TX/RX swap for SOIC8-part
 * @date  09.01.2024  Added I2C1 SDA/SCL mappings
 ******************************************************************************/
void vInitHW_GPIO(void)
{
  /* Enable peripheral clock supplies for used GPIO       */
  RCC_APB2PeriphClockCmd(GPIO_USED_PERIPH, ENABLE);

  #ifdef USART1RTX_GPIO_Remap
  /* Remapping for SOIC8-part                             */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(USART1RTX_GPIO_Remap, ENABLE);
  #endif

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

  /* TIM1 Channel 3                                       */
  GPIO_InitTypeDef sInitTIM1CH3 = {
    .GPIO_Pin = TIM1CH3_GPIO_Pin,
    .GPIO_Mode = TIM1CH3_GPIO_Mode,
    .GPIO_Speed = GPIO_Speed_2MHz
  };
  GPIO_Init(TIM1CH3_GPIO_Port, &sInitTIM1CH3);
  
  /* I2C2 SCL/SDA                                          */
  GPIO_InitTypeDef sInitI2C1 = {
    .GPIO_Pin = I2C1SCL_GPIO_Pin | I2C1SDA_GPIO_Pin,
    .GPIO_Mode = I2C1_GPIO_Mode,
    .GPIO_Speed = GPIO_Speed_2MHz
  };
  GPIO_Init(I2C1_GPIO_Port, &sInitI2C1);
}
