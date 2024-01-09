/*!****************************************************************************
 * @file
 * hw_i2c1.c
 *
 * @brief
 * Low-level initialisation for I2C2 (24C64 EEPROM)
 *
 * @date  09.01.2024
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"
#include "hw_i2c1.h"


/*!****************************************************************************
 * @brief
 * Activate and configure I2C1 peripheral in master mode
 *
 * @date  09.01.2024
 ******************************************************************************/
void vInitHW_I2C1(void)
{
  /* Enable peripheral clock                              */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

  /* Reset peripheral                                     */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);

  /* Configure I2C peripheral                             */
  I2C_InitTypeDef sInit = {
    .I2C_ClockSpeed = 100000,
    .I2C_Mode = I2C_Mode_I2C,
    .I2C_DutyCycle = I2C_DutyCycle_2,
    .I2C_Ack = I2C_Ack_Enable,
    .I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit
  };
  I2C_Init(I2C1, &sInit);
  I2C_Cmd(I2C1, ENABLE);
}