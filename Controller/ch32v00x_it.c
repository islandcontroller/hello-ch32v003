/*!****************************************************************************
 * @file
 * ch32v00x_it.c
 *
 * @brief
 * Application-defined interrupt handler definitions
 *
 * @date  20.03.2023
 * @date  23.03.2023  Added SysTick interrupt demo
 * @date  02.10.2023  Moved system time to hw_stk
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"


/*!****************************************************************************
 * @brief
 * Hard fault handler
 *
 * @date  20.03.2023
 * @date  23.03.2023  Added debugger signal
 ******************************************************************************/
RV_INTERRUPT void HardFault_Handler(void)
{
  /* Signal to debugger                                   */
  __EBREAK();

  /* Endless loop                                         */
  while (1);
}

/*!****************************************************************************
 * @brief
 * SysTick interrupt handler
 *
 * @date  20.03.2023
 * @date  23.03.2023  Added SysTick interrupt demo
 * @date  02.10.2023  SystemTime in hw_stk
 ******************************************************************************/
RV_INTERRUPT void SysTick_Handler(void)
{
  /* Increment system timer counter in hw_stk             */
  extern volatile uint32_t ulHW_STKSystemTime;
  ++ulHW_STKSystemTime;

  /* Reset SysTick compare interrupt flag                 */
  SysTick_ClearITPendingBit();
}
