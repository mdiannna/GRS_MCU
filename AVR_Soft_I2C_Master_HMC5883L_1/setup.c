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
void SoftI2cMasterInit(void){
	DDRB |= (1<<TWI_SDA_PIN);
	PORTB |= (1<<TWI_SDA_PIN);
	DDRB |= (1<<TWI_SCL_PIN);
	PORTB |= (1<<TWI_SCL_PIN);
}

// De-initialize SCL/SDA pins and set the bus low
void SoftI2cMasterDeInit(void) {
	PORTB &= ~(1<<TWI_SDA_PIN);
	DDRB &= ~(1<<TWI_SDA_PIN);
	PORTB &= ~(1<<TWI_SCL_PIN);
	DDRB &= ~(1<<TWI_SCL_PIN);
}

// Read a byte from I2C and send Ack if more reads follow else Nak to terminate read
uint8_t SoftI2cMasterRead(uint8_t last) {
	uint8_t b = 0;
	// Make sure pull-up enabled
	PORTB |= (1<<TWI_SDA_PIN);
	DDRB &= ~(1<<TWI_SDA_PIN);
	// Read byte
	for (uint8_t i = 0; i < 8; i++) {
		// Don't change this loop unless you verify the change with a scope
		b <<= 1;
		_delay_us(I2C_DELAY_USEC);
		PORTB |= (1<<TWI_SCL_PIN);
		if (bit_is_set(PINB, TWI_SDA_PIN)) b |= 1;
		PORTB &= ~(1<<TWI_SCL_PIN);
	}
	// Send Ack or Nak
	DDRB |= (1<<TWI_SDA_PIN);
	if (last) { 
		PORTB |= (1<<TWI_SDA_PIN); 
	}
	else { 
		PORTB &= ~(1<<TWI_SDA_PIN);
	}  
	PORTB |= (1<<TWI_SCL_PIN);
	_delay_us(I2C_DELAY_USEC);
	PORTB &= ~(1<<TWI_SCL_PIN);
	PORTB &= ~(1<<TWI_SDA_PIN);
	return b;
}

// Write a byte to I2C
bool SoftI2cMasterWrite(uint8_t data) {
	// Write byte
	for (uint8_t m = 0x80; m != 0; m >>= 1) {
		// Don't change this loop unless you verify the change with a scope
		if (m & data) { 
			PORTB |= (1<<TWI_SDA_PIN); 
		}
		else { 
			PORTB &= ~(1<<TWI_SDA_PIN); 
		}
		PORTB |= (1<<TWI_SCL_PIN);
		_delay_us(I2C_DELAY_USEC);
		PORTB &= ~(1<<TWI_SCL_PIN);
	}
	// get Ack or Nak
	DDRB &= ~(1<<TWI_SDA_PIN);
	// Enable pullup
	PORTB |= (1<<TWI_SDA_PIN);
	PORTB |= (1<<TWI_SCL_PIN);
	uint8_t rtn = bit_is_set(PINB, TWI_SDA_PIN);
	PORTB &= ~(1<<TWI_SCL_PIN);
	DDRB |= (1<<TWI_SDA_PIN);
	PORTB &= ~(1<<TWI_SDA_PIN);
	return rtn == 0;
}

// Issue a start condition
bool SoftI2cMasterStart(uint8_t addressRW) {
	PORTB &= ~(1<<TWI_SDA_PIN);
	_delay_us(I2C_DELAY_USEC);
	PORTB &= ~(1<<TWI_SCL_PIN);
	return SoftI2cMasterWrite(addressRW);
}

// Issue a restart condition
bool SoftI2cMasterRestart(uint8_t addressRW) {
	PORTB |= (1<<TWI_SDA_PIN);
	PORTB |= (1<<TWI_SCL_PIN);
	_delay_us(I2C_DELAY_USEC);
	return SoftI2cMasterStart(addressRW);
}

// Issue a stop condition
void SoftI2cMasterStop(void) {
	PORTB &= ~(1<<TWI_SDA_PIN);
	_delay_us(I2C_DELAY_USEC);
	PORTB |= (1<<TWI_SCL_PIN);
	_delay_us(I2C_DELAY_USEC);
	PORTB |= (1<<TWI_SDA_PIN);
	_delay_us(I2C_DELAY_USEC);
}

// Read 1 byte from the EEPROM device and return it
uint8_t soft_i2c_eeprom_read_byte(uint8_t deviceAddr, uint16_t readAddress) {
	uint8_t byteRead = 0;
	

	// Issue a start condition, send device address and write direction bit
	if (!SoftI2cMasterStart((deviceAddr<<1) | I2C_WRITE)) return false;

	// Send the address to read, 8 bit or 16 bit
	if (readAddress > 255) {
		if (!SoftI2cMasterWrite((readAddress >> 8))) return false; // MSB
		if (!SoftI2cMasterWrite((readAddress & 0xFF))) return false; // LSB
	}
	else {
		if (!SoftI2cMasterWrite(readAddress)) return false; // 8 bit
	}

	// Issue a repeated start condition, send device address and read direction bit
	if (!SoftI2cMasterRestart((deviceAddr<<1) | I2C_READ)) return false;
	
	// Read the byte
	byteRead = SoftI2cMasterRead(1);

	// Issue a stop condition
	SoftI2cMasterStop();
	
	return byteRead;
}

// Write 1 byte to the EEPROM
bool soft_i2c_eeprom_write_byte(uint8_t deviceAddr, uint16_t writeAddress, byte writeByte) {
	
	// Issue a start condition, send device address and write direction bit
	if (!SoftI2cMasterStart((deviceAddr<<1) | I2C_WRITE)) return false;

	// Send the address to write, 8 bit or 16 bit
	if ( writeAddress > 255) {
		if (!SoftI2cMasterWrite((writeAddress >> 8))) return false; // MSB
		if (!SoftI2cMasterWrite((writeAddress & 0xFF))) return false; // LSB
	}
	else {
		if (!SoftI2cMasterWrite(writeAddress)) return false; // 8 bit
	}

	// Write the byte
	if (!SoftI2cMasterWrite(writeByte)) return false;

	// Issue a stop condition
	SoftI2cMasterStop();
	
	// Delay 10ms for the write to complete, depends on the EEPROM you use
	_delay_ms(10);
	
	return true;
}

// Read more than 1 byte from a device
// (Optional)
bool I2cReadBytes(uint8_t deviceAddr, uint8_t readAddress, int16_t *mxraw, int16_t *myraw, int16_t *mzraw) {
	uint8_t i = 0;
	uint8_t buff[6];

	// Issue a start condition, send device address and write direction bit
	if (!SoftI2cMasterStart((deviceAddr<<1) | I2C_WRITE)) return false;

	// Send the address to read
	if (!SoftI2cMasterWrite(readAddress)) return false;

	SoftI2cMasterStop();

	// Issue a repeated start condition, send device address and read direction bit
	if (!SoftI2cMasterRestart((deviceAddr<<1) | I2C_READ)) return false;

	// Read data from the device
	for (i = 0; i < 6; i++) {
		// Send Ack until last byte then send Ack
		buff[i] = SoftI2cMasterRead(i == (6-1));
	}

	// Issue a stop condition
	SoftI2cMasterStop();

	*mxraw = (int16_t)((buff[0] << 8) | buff[1]);
	*mzraw = (int16_t)((buff[2] << 8) | buff[3]);
	*myraw = (int16_t)((buff[4] << 8) | buff[5]);
	
	return true;
}
