/*!****************************************************************************
 * @file
 * hw_iodefs.h
 *
 * @brief
 * I/O Pinout definitions
 *
 * @date  21.03.2023
 * @date  02.10.2023  Added Timer 1 Channel 3 mapping
 ******************************************************************************/

#ifndef HW_IODEFS_H_
#define HW_IODEFS_H_

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"


/*- Macros -------------------------------------------------------------------*/
/*! @brief Swap RX/TX pins for SOIC8 part. Otherwise, SWIO pin will be blocked*/
//#define USE_SOIC8_UART_REMAP

/*! @brief Used GPIO peripherals bitmask                                      */
#define GPIO_USED_PERIPH              ( RCC_APB2Periph_GPIOC | \
                                        RCC_APB2Periph_GPIOD | 0UL )


/*! @brief PC3: Timer 1 Channel 3 PWM Output to LED
 *  @{                                                                        */
#define TIM1CH3_GPIO_Port             GPIOC
#define TIM1CH3_GPIO_Pin              GPIO_Pin_3
#define TIM1CH3_GPIO_Mode             GPIO_Mode_AF_PP
/*! @}                                                                        */

/*! @brief PA9/10: USART1 RX/TX to debugger serial port
 *  @{                                                                        */
#define USART1RTX_GPIO_Port           GPIOD
#ifdef USE_SOIC8_UART_REMAP
#define USART1RTX_GPIO_Remap          GPIO_PartialRemap2_USART1
#define USART1TX_GPIO_Pin             GPIO_Pin_6
#define USART1RX_GPIO_Pin             GPIO_Pin_5
#else
#define USART1TX_GPIO_Pin             GPIO_Pin_5
#define USART1RX_GPIO_Pin             GPIO_Pin_6
#endif /* USE_SOIC8_UART_REMAP */
#define USART1TX_GPIO_Mode            GPIO_Mode_AF_PP
#define USART1RX_GPIO_Mode            GPIO_Mode_IPU
/*! @}                                                                        */

#endif /* HW_IODEFS_H_ */
