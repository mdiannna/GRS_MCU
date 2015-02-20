/*
 AVR Soft I2C Master - Example for I2C EEPROMs
 Version: 1.0
 Author: Alex from insideGadgets (www.insidegadgets.com)
 Created: 12/02/2012
 Last Modified: 12/02/2012
 
 A software implementation of I2C/TWI Master using code from http://forums.adafruit.com/viewtopic.php?f=25&t=13722
 
 Modifications:
 - Made to work directly with AVR (De-Arduino existing code)
 - Changed from C++ to C
 - Added soft_i2c_eeprom_read_byte and soft_i2c_eeprom_write_byte
 
 */

//                  +-\/-+
// Ain0 (D 5) PB5  1|o   |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "math.h"
#include "usart.h"
#include "setup.h"
#include "hmc5883l.h"


//#define ledPin (1<<PB2)


static int PutChar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(Tx_Char, NULL, _FDEV_SETUP_WRITE);

int main(void) {
	//sei();
	// Turn on interrupts
	DDRB = 0xff;
	//Power supply
	DDRA = 0xff;
	PORTA = 0xff;
	int16_t mxraw = 100;
	int16_t myraw = 100;
	int16_t mzraw = 20;
	double mx = 0;
	double my = 0;
	double mz = 0;
	bool fail = 0;

	stdout = &mystdout;

	//init uart
	USART_Init();
	printf("USART init");

	SoftI2cMasterInit();
	printf("SoftI2CMaster init");
	_delay_us(10);

	hmc5883l_init();
	printf("Sensor init");

	/*	// Write 1 byte to the EEPROM
	 soft_i2c_eeprom_write_byte(EEPROM_ADDR, address, writeByte);

	 // Read 1 byte from the EEPROM
	 readByte = soft_i2c_eeprom_read_byte(EEPROM_ADDR, address);
*/
	while (1) {

			hmc5883l_getrawdata(&mxraw, &myraw, &mzraw);
			hmc5883l_getdata(&mx, &my, &mz);

			printf("s%d %d %d; 0; 0; 0;0 0 0;0 0 0;0 0 0;0 0 0f\n\r", mxraw, myraw, mzraw );
		//printf("\n\r mx: %hd my:%hd mz: %hd", mx, my, mz);
		_delay_ms(500);
	}

	SoftI2cMasterDeInit();
	return 0;
}

