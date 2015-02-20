/*
 * setup.h
 *
 *  Created on: 19 февр. 2015 г.
 *      Author: DDDD
 */
#include <avr/io.h>
#include <stdio.h>

#ifndef SETUP_H_
#define SETUP_H_

#ifndef TWI_SDA_PIN
#define TWI_SDA_PIN PB2
#endif
#ifndef TWI_SCL_PIN
#define TWI_SCL_PIN PB3
#endif

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#ifndef boolean
	typedef uint8_t boolean;
#endif
#ifndef bool
	typedef uint8_t bool;
#endif
#ifndef byte
	typedef uint8_t byte;
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define LOW 0
#define HIGH 1
#define false 0
#define true 1

#define I2C_DELAY_USEC 4
#define I2C_READ 1
#define I2C_WRITE 0


void SoftI2cMasterInit(void);
void SoftI2cMasterDeInit(void);
uint8_t SoftI2cMasterRead(uint8_t last);
bool SoftI2cMasterWrite(uint8_t data);
bool SoftI2cMasterStart(uint8_t addressRW);
bool SoftI2cMasterRestart(uint8_t addressRW);
void SoftI2cMasterStop(void);
uint8_t soft_i2c_eeprom_read_byte(uint8_t deviceAddr, uint16_t readAddress);
bool soft_i2c_eeprom_write_byte(uint8_t deviceAddr, uint16_t writeAddress, byte writeByte) ;
bool I2cReadBytes(uint8_t deviceAddr, uint8_t readAddress, int16_t *mxraw, int16_t *myraw, int16_t *mzraw);

#endif /* SETUP_H_ */
