/*
 AVR Soft I2C Master - Example for I2C EEPROMs
 Version: 1.0
 Author: Alex from insideGadgets (www.insidegadgets.com)
 Created: 12/02/2012
 Last Modified: 12/02/2012
 
 Using code from http://forums.adafruit.com/viewtopic.php?f=25&t=13722
 */
#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>
#include "setup.h"

// Initialize SCL/SDA pins and set the bus high
void SoftI2cMasterInit(void) {
	DDRB = 0xff;
	PORTB = 0xff;
}

// De-initialize SCL/SDA pins and set the bus low
void SoftI2cMasterDeInit(void) {
	PORTB = 0x00;
}

// Read a byte from I2C and send Ack if more reads follow else Nak to terminate read
void SoftI2cMasterRead(uint8_t *b1, uint8_t *b2,uint8_t *b3, uint8_t *b4, uint8_t last) {
	//byte for each sensor - S1, S2, S3, S4

	// Make sure pull-up enabled
	PORTB |= (1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4);
	DDRB &= ~((1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4));

	////////////////
	// Read byte
	for (uint8_t i = 0; i < 8; i++) {
		// Don't change this loop unless you verify the change with a scope
		*b1 <<= 1;
		*b2 <<= 1;
		*b3 <<= 1;
		*b4 <<= 1;

		_delay_us(I2C_DELAY_USEC);
		PORTB |= (1 << TWI_SCL_PIN_S1) | (1 << TWI_SCL_PIN_S2)
				| (1 << TWI_SCL_PIN_S3) | (1 << TWI_SCL_PIN_S4);

		if (PINB & (1 << TWI_SDA_PIN_S1))
			*b1 |= 1;
		if (PINB & (1 << TWI_SDA_PIN_S2))
			*b2 |= 1;
		if (PINB & (1 << TWI_SDA_PIN_S3))
			*b3 |= 1;
		if (PINB & (1 << TWI_SDA_PIN_S4))
			*b4 |= 1;

		PORTB &= ~((1 << TWI_SCL_PIN_S1) | (1 << TWI_SCL_PIN_S2)
				| (1 << TWI_SCL_PIN_S3) | (1 << TWI_SCL_PIN_S4));
	}
	/////////////////////////////////

	// Send Ack or Nak
	DDRB |= (1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4);
	if (last) {
		PORTB |= (1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
				| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4);
	} else {
		PORTB &= ~((1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
				| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4));
	}

	PORTB |= (1 << TWI_SCL_PIN_S1) | (1 << TWI_SCL_PIN_S2)
			| (1 << TWI_SCL_PIN_S3) | (1 << TWI_SCL_PIN_S4);
	_delay_us(I2C_DELAY_USEC);

	PORTB &= ~((1 << TWI_SCL_PIN_S1) | (1 << TWI_SCL_PIN_S2)
			| (1 << TWI_SCL_PIN_S3) | (1 << TWI_SCL_PIN_S4));
	PORTB &= ~((1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4));
}

// Write a byte to I2C
bool SoftI2cMasterWrite(uint8_t data) {

	// Write byte
	for (uint8_t m = 0x80; m != 0; m >>= 1) {
		// Don't change this loop unless you verify the change with a scope
		if (m & data) {
			PORTB |= (1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
					| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4);
		} else {
			PORTB &= ~((1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
					| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4));
		}
		PORTB |= (1 << TWI_SCL_PIN_S1) | (1 << TWI_SCL_PIN_S2)
				| (1 << TWI_SCL_PIN_S3) | (1 << TWI_SCL_PIN_S4);
		_delay_us(I2C_DELAY_USEC);
		PORTB &= ~((1 << TWI_SCL_PIN_S1) | (1 << TWI_SCL_PIN_S2)
				| (1 << TWI_SCL_PIN_S3) | (1 << TWI_SCL_PIN_S4));
	}

	// get Ack or Nak
	DDRB &= ~((1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4));
	// Enable pullup
	PORTB |= (1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4);
	PORTB |= (1 << TWI_SCL_PIN_S1) | (1 << TWI_SCL_PIN_S2)
			| (1 << TWI_SCL_PIN_S3) | (1 << TWI_SCL_PIN_S4);

	uint8_t rtn = bit_is_set(PINB, TWI_SDA_PIN_S1);

	PORTB &= ~((1 << TWI_SCL_PIN_S1) | (1 << TWI_SCL_PIN_S2)
			| (1 << TWI_SCL_PIN_S3) | (1 << TWI_SCL_PIN_S4));
	DDRB |= (1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4);
	PORTB &= ~((1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4));
	return rtn == 0;

}

// Issue a start condition
bool SoftI2cMasterStart(uint8_t addressRW) {
	PORTB &= ~((1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4));
	_delay_us(I2C_DELAY_USEC);
	PORTB &= ~((1 << TWI_SCL_PIN_S1) | (1 << TWI_SCL_PIN_S2)
			| (1 << TWI_SCL_PIN_S3) | (1 << TWI_SCL_PIN_S4));
	return SoftI2cMasterWrite(addressRW);
}

// Issue a restart condition
bool SoftI2cMasterRestart(uint8_t addressRW) {
	PORTB = 0xff;
	_delay_us(I2C_DELAY_USEC);
	return SoftI2cMasterStart(addressRW);
}

// Issue a stop condition
void SoftI2cMasterStop(void) {
	PORTB &= ~((1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4));
	_delay_us(I2C_DELAY_USEC);
	PORTB |= (1 << TWI_SCL_PIN_S1) | (1 << TWI_SCL_PIN_S2)
			| (1 << TWI_SCL_PIN_S3) | (1 << TWI_SCL_PIN_S4);
	_delay_us(I2C_DELAY_USEC);
	PORTB |= ((1 << TWI_SDA_PIN_S1) | (1 << TWI_SDA_PIN_S2)
			| (1 << TWI_SDA_PIN_S3) | (1 << TWI_SDA_PIN_S4));
	_delay_us(I2C_DELAY_USEC);
}
