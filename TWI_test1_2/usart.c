/*
 * usart.c
 *
 *  Created on: 24 џэт. 2015 у.
 *      Author: DDDD
 */

#include "usart.h"

void USART_Init(){
	// Load lower 8-bits into the low byte of the UBRR register
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
	UCSRB = (1<<RXEN)|(1<<TXEN);
}

void Tx_Char( char data ){
	//Wait for empty transmit buffer
	while ( !( UCSRA & (1<<UDRE)) )
	;
	//Put data into buffer, send the data
	UDR = data;
}

void Tx_String(char *str){
	while(*str){
		Tx_Char(*str++);
	}
}

