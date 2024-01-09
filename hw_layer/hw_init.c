/*!****************************************************************************
 * @file
 * hw_init.c
 *
 * @brief
 * Top-Level hardware Init module
 *
 * @date  21.03.2023
 * @date  02.10.2023  Added Timer 1 module
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include <string.h>
#include "ch32v00x.h"
#include "hw_stk.h"
#include "hw_gpio.h"
#include "hw_usart1.h"
#include "hw_tim1.h"
#include "hw_i2c1.h"


/*!****************************************************************************
 * @brief
 * Top-level call to initialise all used hardware modules
 *
 * @date  21.03.2023
 * @date  02.10.2023  Added Timer 1 module
 ******************************************************************************/
void vInitHW(void)
{
  vInitHW_STK();
  vInitHW_GPIO();
  vInitHW_USART1();
  vInitHW_TIM1();
  vInitHW_I2C1();

  SystemCoreClockUpdate();
}
