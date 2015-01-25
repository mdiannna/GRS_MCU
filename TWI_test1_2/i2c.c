/*
 * i2c.c
 *
 *  Created on: 25 янв. 2015 г.
 *      Author: DDDD
 */

#include <avr/io.h>
#include "i2c.h"

void iic_masterinit(){
	TWSR = 0x00;
	TWBR = 0x47;
	TWCR = (1<<TWEN);
}

void iic_start(){
	TWCR = (1<<TWEN)|(1<<TWINT);
	TWCR |= (1<<TWSTA);
	while(!(TWCR&(1<<TWINT)));
}

void iic_addop(unsigned char addop){
	TWDR = (addop|(1<<0));
	TWCR = (1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
}

unsigned char iic_read(){
	TWCR = (1<<TWEN)|(1<<TWINT);
	TWCR &=~(1<<TWEA);
	while(!(TWCR&(1<<TWINT)));
	return(TWDR);
}


void iic_stop(){
	TWCR = (1<<TWEN)|(1<<TWINT);
	TWCR = (1<<TWSTO);
}

unsigned char I2C_GetStatus(void)
{
	unsigned char status;//переменная хранения
	status = TWSR & 0xF8;//маска
	return status;
}


