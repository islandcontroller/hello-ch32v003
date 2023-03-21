/*!****************************************************************************
 * @file
 * hw_stk.c
 *
 * @brief
 * Low-level SysTick configuration
 *
 * @date  21.03.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"


/*!****************************************************************************
 * @brief
 * Enable SysTick-Timer
 *
 * @date  21.03.2023
 ******************************************************************************/
void vInitHW_STK(void)
{
  SysTick_InitTypeDef sInit = {
    .SysTick_ClockPrescaler = SYSTICK_HCLK_Div8,
    .SysTick_CompareReload = ENABLE,
    .SysTick_CompareValue = -1UL,
    .SysTick_CounterPreload = 0
  };
  SysTick_Init(&sInit);
  SysTick_Cmd(ENABLE);
}
