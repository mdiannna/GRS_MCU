/* main.c
 **  Created on: 17 ian 2015
 *      Author: DDDD
 */



#include <avr/io.h>
#include <avr/delay.h>
#include "usart.h"
#include "i2c.h"

void main(){
	USART_Init();
		Tx_String("AAA");
		unsigned char data;
		while(1){
			Tx_Char('S');

				iic_masterinit();
				iic_start();
				iic_addop(0b00111010);
				//data = iic_read();
				//Tx_Char(data);

				if(I2C_GetStatus() == 0x80)
				data = TWDR;

				TWCR|=(1<<TWEN);
				Tx_Char(data);

				iic_stop();
				Tx_String("X");
				_delay_ms(4000);
		}

}




