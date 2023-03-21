/*!****************************************************************************
 * @file
 * hw_iodefs.h
 *
 * @brief
 * I/O Pinout definitions
 *
 * @date  21.03.2023
 ******************************************************************************/

#ifndef HW_IODEFS_H_
#define HW_IODEFS_H_

/*- Header files -------------------------------------------------------------*/
#include "ch32v00x.h"


/*- Macros -------------------------------------------------------------------*/
/*! @brief Used GPIO peripherals bitmask                                      */
#define GPIO_USED_PERIPH              RCC_APB2Periph_GPIOD

/*! @brief PA9/10: USART1 RX/TX to debugger serial port
 *  @{                                                                        */
#define USART1RTX_GPIO_Port           GPIOD
#define USART1TX_GPIO_Pin             GPIO_Pin_5
#define USART1RX_GPIO_Pin             GPIO_Pin_6
#define USART1TX_GPIO_Mode            GPIO_Mode_AF_PP
#define USART1RX_GPIO_Mode            GPIO_Mode_IPU
/*! @}                                                                        */

#endif /* HW_IODEFS_H_ */
