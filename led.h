/*!****************************************************************************
 * @file
 * led.h
 *
 * @brief
 * Breathing animation using PWM on TIM1 Channel 3
 *
 * @date  02.10.2023
 ******************************************************************************/

#ifndef LED_H_
#define LED_H_

/*- Exported functions -------------------------------------------------------*/
void vInitLed(void);
void vPollLed(void);

#endif /* LED_H_ */