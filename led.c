/*!****************************************************************************
 * @file
 * led.c
 *
 * @brief
 * Breathing animation using PWM on TIM1 Channel 3
 *
 * @date  02.10.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include "hw_stk.h"
#include "hw_tim1.h"


/*- Macros -------------------------------------------------------------------*/
/*! @brief Brightness update interval in ms                                   */
#define LED_TIME_INTER                10UL


/*- Private variables --------------------------------------------------------*/
/*! Count direction                                                           */
static bool bCountDirUp;

/*! Brightness value                                                          */
static uint8_t ucBrightness;

/*! Last change timestamp                                                     */
static uint32_t ulLastChange;


/*!****************************************************************************
 * @brief
 * Initialise LEd animation
 * 
 * @date  02.10.2023
 ******************************************************************************/
void vInitLed(void)
{
  bCountDirUp = true;
  ucBrightness = 0;
  ulLastChange = ulHW_STKGetSystemTime();
}

/*!****************************************************************************
 * @brief
 * Handle LED animation in background task
 * 
 * @date  02.10.2023
 ******************************************************************************/
void vPollLed(void)
{
  /* Early exit until minimum interval is reached         */
  uint32_t ulNow = ulHW_STKGetSystemTime();
  if (ulNow - ulLastChange < LED_TIME_INTER) return;

  /* Update brightness value                              */
  if (bCountDirUp)
  {
    if (ucBrightness < 100) 
    {
      ++ucBrightness;
    }
    else
    {
      bCountDirUp = false;
    }
  }
  else
  {
    if (ucBrightness > 0)
    {
      --ucBrightness;
    }
    else
    {
      bCountDirUp = true;
    }
  }

  /* Update output and last change timestamp              */
  vHW_TIM1SetPwmCompare(ucBrightness);
  ulLastChange = ulNow;
}