/*!****************************************************************************
 * @file
 * hw_init.c
 *
 * @brief
 * Top-Level hardware Init module
 *
 * @date  21.03.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include <string.h>
#include "ch32v00x.h"
#include "hw_stk.h"
#include "hw_gpio.h"
#include "hw_usart1.h"


/*!****************************************************************************
 * @brief
 * Top-level call to initialise all used hardware modules
 *
 * @date  21.03.2023
 ******************************************************************************/
void vInitHW(void)
{
  vInitHW_STK();
  vInitHW_GPIO();
  vInitHW_USART1();

  SystemCoreClockUpdate();
}
