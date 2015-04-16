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

#ifndef TWI_SDA_PIN_S1
#define TWI_SDA_PIN_S1 PB0
#endif
#ifndef TWI_SCL_PIN_S1
#define TWI_SCL_PIN_S1 PB1
#endif

#ifndef TWI_SDA_PIN_S2
#define TWI_SDA_PIN_S2 PB2
#endif
#ifndef TWI_SCL_PIN_S2
#define TWI_SCL_PIN_S2 PB3
#endif

#ifndef TWI_SDA_PIN_S3
#define TWI_SDA_PIN_S3 PB4
#endif
#ifndef TWI_SCL_PIN_S3
#define TWI_SCL_PIN_S3 PB5
#endif

#ifndef TWI_SDA_PIN_S4
#define TWI_SDA_PIN_S4 PB6
#endif
#ifndef TWI_SCL_PIN_S4
#define TWI_SCL_PIN_S4 PB7
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
void SoftI2cMasterRead(uint8_t *b1, uint8_t *b2, uint8_t *b3, uint8_t *b4, uint8_t last);
bool SoftI2cMasterWrite(uint8_t data);
bool SoftI2cMasterStart(uint8_t addressRW);
bool SoftI2cMasterRestart(uint8_t addressRW);
void SoftI2cMasterStop(void);

#endif /* SETUP_H_ */
