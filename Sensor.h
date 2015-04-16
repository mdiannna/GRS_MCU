/*
 * Sensor.h
 *
 *  Created on: 28 џэт. 2015 у.
 *      Author: DDDD
 */

#ifndef SENSOR_H_
#define SENSOR_H_


#define I2C_WRITE 0
#define I2C_READ 1

//7-bit address and R/W(1/0) - the 1st bit
#define SENSOR1_ADDR 0b00111010
//7-bit address and 0/1- the most significant bit (multiple/single reading)
#define READ_SINGLE_BYTE 0x00
#define READ_MULTIPLE_BYTES 0b10000000

#define TEMP_OUT_L 0b00000101
#define TEMP_OUT_H 0b00000110
#define STATUS_M 0b00000111
#define OUT_X_L_M 0b00001000
#define OUT_X_H_M 0b00001001
#define OUT_Y_L_M 0b00001010
#define OUT_Y_H_M 0b00001011
#define OUT_Z_L_M 0b00001100
#define OUT_Z_H_M 0b00001101
#define WHO_AM_I 0b00001111
#define INT_CTRL_M 0b00010010
#define INT_SRC_M 0b00b0010011
#define INT_THS_L_M 0b00010100
#define INT_THS_H_M 0b00010101
#define OFFSET_X_L_M 0b00010110
#define OFFSET_X_H_M 0b00010111
#define OFFSET_Y_L_M 0b000101000
#define OFFSET_Y_H_M 0b000101001
#define OFFSET_Z_L_M 0b000101010
#define OFFSET_Z_H_M 0b000101011

//#define REFERENCE_X 001 01100
//#define REFERENCE_Y 001 01101
//#define REFERENCE_Z 001 01110

#define CTRL0 0b00011111
#define CTRL1 0b00100000
#define CTRL2 0b00100001
#define CTRL3 0b00100010
#define CTRL4 0b00100011
#define CTRL5 0b00100100
#define CTRL6 0b00100000 //0b00100101 //0b00100000//
#define CTRL7 0b00100110

#define STATUS_A 0b00100111
#define OUT_X_L_A 0b00101000
#define OUT_X_H_A 0b00101001
#define OUT_Y_L_A 0b00101010
#define OUT_Y_H_A 0b00101011
#define OUT_Z_L_A 0b00101100
#define OUT_Z_H_A 0b00101101
#define FIFO_CTRL 0b00101110
#define FIFO_SRC 0b00101111
#define IG_CFG1 0b00110000
#define IG_SRC1 0b00110001
#define IG_THS1 0b00110010
#define IG_DUR1 0b00110011
#define IG_CFG2 0b00110100
#define IG_SRC2 0b00110101
#define IG_THS2 0b00110110
#define IG_DUR2 0b00110111
#define CLICK_CFG 0b00111000
#define CLICK_SRC 0b00111001
#define CLICK_THS 0b00111010
#define TIME_LIMIT 0b00111011
#define TIME _LATENCY 0b00111100
#define TIME_WINDOW 0b00111101
#define ACT_THS 0b00111110
#define ACT_DUR 0b0111111

void EcompassInit(void);
char Geti2cSensorData(char s_address, char r_address);

#endif /* SENSOR_H_ */
