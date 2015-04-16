/*
 hmc5883l lib 0x01

 copyright (c) Davide Gironi, 2012

 Released under GPLv3.
 Please refer to LICENSE file for licensing information.
 */

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "hmc5883l4s.h"
#include "setup.h"
#include "calibration.h"

static double hmc5883l_scale = 0;
uint8_t b1 = 0;
uint8_t b2 = 0;
uint8_t b3 = 0;
uint8_t b4 = 0;

/*
 * init the hmc5883l
 */
void hmc5883l_init_4s() {
//!!!!!!!!!!1
	SoftI2cMasterInit();
	_delay_us(10);

	//set scale
	hmc5883l_scale = 0;
	uint8_t regValue = 0x00;
#if HMC5883L_SCALE == HMC5883L_SCALE088
	regValue = 0x00;
	hmc5883l_scale = 0.73;
#elif HMC5883L_SCALE == HMC5883L_SCALE13
	regValue = 0x01;
	hmc5883l_scale = 0.92;
#elif HMC5883L_SCALE == HMC5883L_SCALE19
	regValue = 0x02;
	hmc5883l_scale = 1.22;
#elif HMC5883L_SCALE == HMC5883L_SCALE25
	regValue = 0x03;
	hmc5883l_scale = 1.52;
#elif HMC5883L_SCALE == HMC5883L_SCALE40
	regValue = 0x04;
	hmc5883l_scale = 2.27;
#elif HMC5883L_SCALE == HMC5883L_SCALE47
	regValue = 0x05;
	hmc5883l_scale = 2.56;
#elif HMC5883L_SCALE == HMC5883L_SCALE56
	regValue = 0x06;
	hmc5883l_scale = 3.03;
#elif HMC5883L_SCALE == HMC5883L_SCALE81
	regValue = 0x07;
	hmc5883l_scale = 4.35;
#endif

	regValue = regValue << 5;
	SoftI2cMasterStart(HMC5883L_ADDR | I2C_WRITE);
	SoftI2cMasterWrite(HMC5883L_CONFREGB);
	SoftI2cMasterWrite(regValue);
	SoftI2cMasterStop();

	//set measurement mode
	//   SoftI2cMasterStart(HMC5883L_ADDR | I2C_WRITE);
	SoftI2cMasterRestart(HMC5883L_ADDR | I2C_WRITE);
	SoftI2cMasterWrite(HMC5883L_MODEREG);
	SoftI2cMasterWrite(HMC5883L_MEASUREMODE);
	SoftI2cMasterStop();
}

/*
 * get raw data
 */
void hmc5883l_getrawdata_4s(int16_t *mxraw1, int16_t *myraw1, int16_t *mzraw1,
		int16_t *mxraw2, int16_t *myraw2, int16_t *mzraw2, int16_t *mxraw3,
		int16_t *myraw3, int16_t *mzraw3, int16_t *mxraw4, int16_t *myraw4,
		int16_t *mzraw4) {

	uint8_t i = 0;
	uint8_t buffS1[6];
	uint8_t buffS2[6];
	uint8_t buffS3[6];
	uint8_t buffS4[6];

	SoftI2cMasterStart(HMC5883L_ADDR | I2C_WRITE);
	SoftI2cMasterWrite(HMC5883L_DATAREGBEGIN);
	SoftI2cMasterStop();
	SoftI2cMasterRestart(HMC5883L_ADDR | I2C_READ);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!
	for (i = 0; i < 6; i++) {
		SoftI2cMasterRead(&b1, &b2, &b3, &b4, i == 6 - 1);
		buffS1[i] = b1;
		buffS2[i] = b2;
		buffS3[i] = b3;
		buffS4[i] = b4;
		_delay_ms(50);
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!
	SoftI2cMasterStop();

	*mxraw1 = (int16_t) ((buffS1[0] << 8) | buffS1[1]);
	*mzraw1 = (int16_t) ((buffS1[2] << 8) | buffS1[3]);
	*myraw1 = (int16_t) ((buffS1[4] << 8) | buffS1[5]);

	*mxraw2 = (int16_t) ((buffS2[0] << 8) | buffS2[1]);
	*mzraw2 = (int16_t) ((buffS2[2] << 8) | buffS2[3]);
	*myraw2 = (int16_t) ((buffS2[4] << 8) | buffS2[5]);

	*mxraw3 = (int16_t) ((buffS3[0] << 8) | buffS3[1]);
	*mzraw3 = (int16_t) ((buffS3[2] << 8) | buffS3[3]);
	*myraw3 = (int16_t) ((buffS3[4] << 8) | buffS3[5]);

	*mxraw4 = (int16_t) ((buffS4[0] << 8) | buffS4[1]);
	*mzraw4 = (int16_t) ((buffS4[2] << 8) | buffS4[3]);
	*myraw4 = (int16_t) ((buffS4[4] << 8) | buffS4[5]);
}

void hmc5883l_getdata_4s(double *mx2, double *my2, double *mz2, double *mx3,
		double *my3, double *mz3, double *mx4, double *my4, double *mz4,
		double *mx5, double *my5, double *mz5) {
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

	hmc5883l_getrawdata_4s(&mxraw2, &myraw2, &mzraw2, &mxraw3, &myraw3, &mzraw3,
			&mxraw4, &myraw4, &mzraw4, &mxraw5, &myraw5, &mzraw5);

#if HMC5883L_CALIBRATED == 1
	float mxt2 = mxraw2 - biasX_s[2];
	float myt2 = myraw2 - biasY_s[2];
	float mzt2 = mzraw2 - biasZ_s[2];
	float mxt3 = mxraw3 - biasX_s[3];
	float myt3 = myraw3 - biasY_s[3];
	float mzt3 = mzraw3 - biasZ_s[3];
	float mxt4 = mxraw4 - biasX_s[4];
	float myt4 = myraw4 - biasY_s[4];
	float mzt4 = mzraw4 - biasZ_s[4];
	float mxt5 = mxraw5 - biasX_s[5];
	float myt5 = myraw5 - biasY_s[5];
	float mzt5 = mzraw5 - biasZ_s[5];
	*mx2 = gainX1_s[2] * mxt2 + gainX2_s[2] * myt2 + gainX3_s[2] * mzt2;
	*my2 = gainY1_s[2] * mxt2 + gainY2_s[2] * myt2 + gainY3_s[2] * mzt2;
	*mz2 = gainZ1_s[2] * mxt2 + gainZ2_s[2] * myt2 + gainZ3_s[2] * mzt2;
	*mx3 = gainX1_s[3] * mxt3 + gainX2_s[3] * myt3 + gainX3_s[3] * mzt3;
	*my3 = gainY1_s[3] * mxt3 + gainY2_s[3] * myt3 + gainY3_s[3] * mzt3;
	*mz3 = gainZ1_s[3] * mxt3 + gainZ2_s[3] * myt3 + gainZ3_s[3] * mzt3;
	*mx4 = gainX1_s[4] * mxt4 + gainX2_s[4] * myt4 + gainX3_s[4] * mzt4;
	*my4 = gainY1_s[4] * mxt4 + gainY2_s[4] * myt4 + gainY3_s[4] * mzt4;
	*mz4 = gainZ1_s[4] * mxt4 + gainZ2_s[4] * myt4 + gainZ3_s[4] * mzt4;
	*mx5 = gainX1_s[5] * mxt5 + gainX2_s[5] * myt5 + gainX3_s[5] * mzt5;
	*my5 = gainY1_s[5] * mxt5 + gainY2_s[5] * myt5 + gainY3_s[5] * mzt5;
	*mz5 = gainZ1_s[5] * mxt5 + gainZ2_s[5] * myt5 + gainZ3_s[5] * mzt5;
#else
	*mx2 = mxraw2 * hmc5883l_scale;
	*my2 = myraw2 * hmc5883l_scale;
	*mz2 = mzraw2 * hmc5883l_scale;
	*mx3 = mxraw3 * hmc5883l_scale;
	*my3 = myraw3 * hmc5883l_scale;
	*mz3 = mzraw3 * hmc5883l_scale;
	*mx4 = mxraw4 * hmc5883l_scale;
	*my4 = myraw4 * hmc5883l_scale;
	*mz4 = mzraw4 * hmc5883l_scale;
	*mx5 = mxraw5 * hmc5883l_scale;
	*my5 = myraw5 * hmc5883l_scale;
	*mz5 = mzraw5 * hmc5883l_scale;
#endif

}

