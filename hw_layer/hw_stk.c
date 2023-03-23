/*!****************************************************************************
 * @file
 * hw_stk.c
 *
 * @brief
 * Low-level SysTick configuration
 *
 * @date  21.03.2023
 * @date  23.03.2023  Added compare value macro (1ms period)
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"


/*- Macros -------------------------------------------------------------------*/
/*! @brief SysTick compare value for 1ms period                               */
#define SYSTICK_CMP_VALUE             (HSI_VALUE / 8U / 1000U)


/*!****************************************************************************
 * @brief
 * Enable SysTick-Timer
 *
 * @date  21.03.2023
 * @date  23.03.2023  Added CMP value macro; Added interrupt configuration
 ******************************************************************************/
void vInitHW_STK(void)
{
  SysTick_InitTypeDef sInit = {
    .SysTick_ClockPrescaler = SYSTICK_HCLK_Div8,
    .SysTick_CompareReload = ENABLE,
    .SysTick_CompareValue = SYSTICK_CMP_VALUE,
    .SysTick_CounterPreload = 0
  };
  SysTick_Init(&sInit);

  /* Enable SysTick interrupts                            */
  SysTick_ITConfig(ENABLE);
  PFIC_EnableIRQ(SysTicK_IRQn);

  SysTick_Cmd(ENABLE);

}
