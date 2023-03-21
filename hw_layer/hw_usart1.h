/*!****************************************************************************
 * @file
 * hw_usart1.h
 *
 * @brief
 * Low-level initialisation for USART1 (debugger serial port)
 *
 * @date  21.03.2023
 ******************************************************************************/

#ifndef HW_USART1_H_
#define HW_USART1_H_

/*- Macros -------------------------------------------------------------------*/
/*! @brief Serial Baudrate                                                    */
#define USART1_BAUD_RATE              115200


/*- Exported functions -------------------------------------------------------*/
void vInitHW_USART1(void);

#endif /* HW_UART1_H_ */
