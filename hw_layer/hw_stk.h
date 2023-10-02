/*!****************************************************************************
 * @file
 * hw_stk.h
 *
 * @brief
 * Low-level SysTick configuration
 *
 * @date  21.03.2023
 * @date  02.10.2023  Added system time getter
 ******************************************************************************/

#ifndef HW_STK_H_
#define HW_STK_H_

/*- Exported functions -------------------------------------------------------*/
void vInitHW_STK(void);
uint32_t ulHW_STKGetSystemTime(void);

#endif /* HW_STK_H_ */
