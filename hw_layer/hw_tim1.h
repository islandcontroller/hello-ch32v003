/*!****************************************************************************
 * @file
 * hw_tim1.h
 *
 * @brief
 * Timer 1 Hardware Layer access
 *
 * @date  02.10.2023
 ******************************************************************************/

#ifndef HW_TIM1_H_
#define HW_TIM1_H_

/*- Header files -------------------------------------------------------------*/
#include <stdint.h>


/*- Exported functions -------------------------------------------------------*/
void vInitHW_TIM1(void);
void vHW_TIM1SetPwmCompare(uint8_t ucValue);

#endif /* HW_TIM1_H_ */