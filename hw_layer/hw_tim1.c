/*!***************************************************************************
 * @file
 * hw_tim1.c
 *
 * @brief
 * Timer 1 Hardware Layer access
 *
 * @date  02.10.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"
#include "hw_tim1.h"


/*!****************************************************************************
 * @brief
 * Initialise Timer 1
 * 
 * @date  02.10.2023
 ******************************************************************************/
void vInitHW_TIM1(void)
{
  /* Enable TIM1 peripheral clock                         */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  /* Configure base timer for 1kHz PWM with pulse width be-
   * tween 0 and 100 counts.                              */
  TIM_TimeBaseInitTypeDef sInitBase = {
    .TIM_ClockDivision = 240, /* 24 MHz PCLK1             */
    .TIM_CounterMode = TIM_CounterMode_Up,
    .TIM_Period = 100
  };
  TIM_TimeBaseInit(TIM1, &sInitBase);

  /* Configure Channel 3 for PWM output on PC3            */
  TIM_OCInitTypeDef sInitCh3 = {
    .TIM_OCMode = TIM_OCMode_PWM1,
    .TIM_OutputState = ENABLE,
    .TIM_OCPolarity = TIM_OCPolarity_Low,
    .TIM_Pulse = 0
  };
  TIM_OC3Init(TIM1, &sInitCh3);

  /* Enable main PWM outputs                              */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);

  /* Apply Capture register writes on PWM period match    */
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Disable);

  /* Enable automatic preload from ARR                    */
  TIM_ARRPreloadConfig(TIM1, ENABLE);

  /* Start timer                                          */
  TIM_Cmd(TIM1, ENABLE);
}

/*!****************************************************************************
 * @brief
 * Set PWM compare value
 * 
 * @param[in] ucValue     Compare value in range [0 ... 100]
 * @date  02.10.2023
 ******************************************************************************/
void vHW_TIM1SetPwmCompare(uint8_t ucValue)
{
  TIM_SetCompare3(TIM1, ucValue);
}