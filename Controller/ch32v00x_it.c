/*!****************************************************************************
 * @file
 * ch32v00x_it.c
 *
 * @brief
 * Application-defined interrupt handler definitions
 *
 * @date  20.03.2023
 * @date  23.03.2023  Added SysTick interrupt demo
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"


/*- Global variables ---------------------------------------------------------*/
/*! System timer counter (1ms per tick)                                       */
extern volatile uint32_t ulSystemTime;


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
 ******************************************************************************/
RV_INTERRUPT void SysTick_Handler(void)
{
  /* Increment system timer counter                       */
  ++ulSystemTime;

  /* Reset SysTick compare interrupt flag                 */
  SysTick_ClearITPendingBit();
}
