/*
 * usart.h
 *
 *  Created on: 24 џэт. 2015 у.
 *      Author: DDDD
 */

#ifndef USART_H_
#define USART_H_

#include <avr/io.h>


#define F_CPU 8000000UL

#define USART_BAUDRATE 19200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

void USART_Init(void);
void Tx_Char(char data);
void Tx_String(char *str);
unsigned char uart_getc(void);

#endif /* USART_H_ */
