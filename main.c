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
#include "hmc5883l4s.h"
#include "hmc5883l.h"
#include "i2cmaster.h"
#include "Sensor.h"
#include "calibration.h"

static int PutChar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(Tx_Char, NULL, _FDEV_SETUP_WRITE);

//BS - Base Sensor
char dataH, dataL;
//magnetometer data
unsigned int xm, ym, zm;
//accelerometer data
unsigned int xa = -1, ya = -1, za = -1;
double mx1, my1, mz1;
double mx2, my2, mz2;
double mx3, my3, mz3;
double mx4, my4, mz4;
double mx5, my5, mz5;
//Sensor 1, 2, 3, 4, 5
int16_t mxraw1 = 1;
int16_t myraw1 = 1;
int16_t mzraw1 = 1;
int16_t mxraw2 = 1;
int16_t myraw2 = 1;
int16_t mzraw2 = 1;
int16_t mxraw3 = 1;
int16_t myraw3 = 1;
int16_t mzraw3 = 1;
int16_t mxraw4 = 1;
int16_t myraw4 = 1;
int16_t mzraw4 = 1;
int16_t mxraw5 = 1;
int16_t myraw5 = 1;
int16_t mzraw5 = 1;

void Init(void) {
	USART_Init();
	printf("USART init done. Initializing I2C...\n\r");
	i2c_init();
	printf("I2C init done. Initializing Soft I2C Master...\n\r");
	SoftI2cMasterInit();
	printf("SoftI2CMaster init done. Initializing BS...\n\r");
	_delay_ms(100);
	EcompassInit();
	printf("BS init done. Initializing S1...");
	hmc5883l_init();
	printf("S1 init done. Initializing S2, S3, S4, S5...\n\r");
	hmc5883l_init_4s();
	printf("S2, S3, S4, S5 Sensors init done. Sensors ready\n\r");
}

void getDataForCalibration() {
	//Receive magnetometer data from BS
	dataL = Geti2cSensorData(SENSOR1_ADDR, OUT_X_L_M);
	dataH = Geti2cSensorData(SENSOR1_ADDR, OUT_X_H_M);
	xm = (int) (dataH << 8) | dataL;
	dataL = Geti2cSensorData(SENSOR1_ADDR, OUT_Y_L_M);
	dataH = Geti2cSensorData(SENSOR1_ADDR, OUT_Y_H_M);
	ym = (int) (dataH << 8) + dataL;
	dataL = Geti2cSensorData(SENSOR1_ADDR, OUT_Z_L_M);
	dataH = Geti2cSensorData(SENSOR1_ADDR, OUT_Z_H_M);
	zm = (int) (dataH << 8) + dataL;

	hmc5883l_getrawdata(&mxraw1, &myraw1, &mzraw1);
	hmc5883l_getrawdata_4s(&mxraw2, &myraw2, &mzraw2, &mxraw3, &myraw3, &mzraw3,
			&mxraw4, &myraw4, &mzraw4, &mxraw5, &myraw5, &mzraw5);
	printf(
			"s%d %d %d;%d %d %d;%d %d %d;%d %d %d;%d %d %d;%d %d %d;%d %d %d;f\n\r",
			xa, ya, za, xm, ym, zm, mxraw1, myraw1, mzraw1, mxraw2, myraw2,
			mzraw2, mxraw3, myraw3, mzraw3, mxraw4, myraw4, mzraw4, mxraw5,
			myraw5, mzraw5);

}

void sendData() {

	//Receive magnetometer data from BS
	dataL = Geti2cSensorData(SENSOR1_ADDR, OUT_X_L_M);
	dataH = Geti2cSensorData(SENSOR1_ADDR, OUT_X_H_M);
	xm = (int) (dataH << 8) | dataL;
	dataL = Geti2cSensorData(SENSOR1_ADDR, OUT_Y_L_M);
	dataH = Geti2cSensorData(SENSOR1_ADDR, OUT_Y_H_M);
	ym = (int) (dataH << 8) + dataL;
	dataL = Geti2cSensorData(SENSOR1_ADDR, OUT_Z_L_M);
	dataH = Geti2cSensorData(SENSOR1_ADDR, OUT_Z_H_M);
	zm = (int) (dataH << 8) + dataL;

	//Receive accelerometer data from BS
	dataL = Geti2cSensorData(SENSOR1_ADDR, OUT_X_L_A);
	dataH = Geti2cSensorData(SENSOR1_ADDR, OUT_X_H_A);
	xa = (int) (dataH << 8) | dataL;
	dataL = Geti2cSensorData(SENSOR1_ADDR, OUT_Y_L_A);
	dataH = Geti2cSensorData(SENSOR1_ADDR, OUT_Y_H_A);
	ya = (int) (dataH << 8) + dataL;
	dataL = Geti2cSensorData(SENSOR1_ADDR, OUT_Z_L_A);
	dataH = Geti2cSensorData(SENSOR1_ADDR, OUT_Z_H_A);
	za = (int) (dataH << 8) + dataL;

	hmc5883l_getdata(&mx1, &my1, &mz1);
	mxraw1 = (int) mx1;
	myraw1 = (int) my1;
	mzraw1 = (int) mz1;

	hmc5883l_getdata_4s(&mx2, &my2, &mz2, &mx3, &my3, &mz3,
			&mx4, &my4, &mz4, &mx5, &my5, &mz5);

	mxraw2 = (int) mx2;
	myraw2 = (int) my2;
	mzraw2 = (int) mz2;
	mxraw3 = (int) mx3;
	myraw3 = (int) my3;
	mzraw3 = (int) mz3;
	mxraw4 = (int) mx4;
	myraw4 = (int) my4;
	mzraw4 = (int) mz4;
	mxraw5 = (int) mx5;
	myraw5 = (int) my5;
	mzraw5 = (int) mz5;
	printf(
			"s%d %d %d;%d %d %d;%d %d %d;%d %d %d;%d %d %d;%d %d %d;%d %d %d;f\n\r",
			xa, ya, za, xm, ym, zm, mxraw1, myraw1, mzraw1, mxraw2, myraw2,
			mzraw2, mxraw3, myraw3, mzraw3, mxraw4, myraw4, mzraw4, mxraw5,
			myraw5, mzraw5);
}

int main(void) {
	//sei();
	// Turn on interrupts
	DDRB = 0xff;
	//Power supply
	DDRA = 0xff;
	PORTA = 0xff;
	int flagC = 0;

	stdout = &mystdout;

	Init();

	while (1) {

		char tmp = uart_getc();

		//command to get calibration data
		if (tmp == 'C') {
			printf("\n\r#Calibrating sensor:\n\r");
			Calibrate();
			flagC = 0;
		}
		//command to get raw data for calibration
		if (tmp == 'G') {
			printf("\n\r#Getting data for calibration:\n\r");
			flagC = 1;
		}
		//Stop getting raw data for calibration
		if (tmp == 'S')
			flagC = 0;

		printf("\n\r#flag=%d\n\r", flagC);
		if (flagC)
			getDataForCalibration();
		else
			sendData();

	}

	SoftI2cMasterDeInit();
	return 0;
}

