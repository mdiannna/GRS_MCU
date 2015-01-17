/*
 * main.c
 *
 *  Created on: 17 џэт. 2015 у.
 *      Author: DDDD
 */

#define F_CPU 8000000UL
#define USART_BAUDRATE 19200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <avr/io.h>
#include <avr/delay.h>

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
void main(void){
	USART_Init();
	while(1){
		Tx_Char('F');
		Tx_String(" ABCDEF ");
	}
}

