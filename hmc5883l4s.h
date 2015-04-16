/*
hmc5883l lib 0x01

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.

References:
  - HMC5883L Triple Axis Magnetometer Arduino Library
    http://bildr.org/2012/02/hmc5883l_arduino/
*/


#ifndef HMC5883L4s_H_
#define HMC5883L4s_H_

//definitions
#define HMC5883L_ADDR (0x1E<<1) //device address

//i2c settings
#define HMC5883L_I2CFLEURYPATH "../i2chw/i2cmaster.h" //define the path to i2c fleury lib
#define HMC5883L_I2CINIT 1 //init i2c

//registers
#define HMC5883L_CONFREGA 0x00
#define HMC5883L_CONFREGB 0x01
#define HMC5883L_MODEREG 0x02
#define HMC5883L_DATAREGBEGIN 0x03

//setup measurement mode
#define HMC5883L_MEASURECONTINOUS 0x00
#define HMC5883L_MEASURESINGLESHOT 0x01
#define HMC5883L_MEASUREIDLE 0x03
#define HMC5883L_MEASUREMODE HMC5883L_MEASURECONTINOUS

//setup scale
#define HMC5883L_SCALE088 1 //0.88
#define HMC5883L_SCALE13 2 //1.3
#define HMC5883L_SCALE19 3 //1.9
#define HMC5883L_SCALE25 4 //2.5
#define HMC5883L_SCALE40 5 //4.0
#define HMC5883L_SCALE47 6 //4.7
#define HMC5883L_SCALE56 7 //5.6
#define HMC5883L_SCALE81 8 //8.1
#define HMC5883L_SCALE HMC5883L_SCALE13

#define HMC5883L_CALIBRATED 1 //enable this if this magn is calibrated

/*//calibration values A^-1 sensor1
#if HMC5883L_CALIBRATED == 1
#define HMC5883L_OFFSETX -5.84
#define HMC5883L_OFFSETY -120.52
#define HMC5883L_OFFSETZ 28.487787
#define HMC5883L_GAINX1 1.041694
#define HMC5883L_GAINX2 0.028581
#define HMC5883L_GAINX3 0.018317
#define HMC5883L_GAINY1 0.028581
#define HMC5883L_GAINY2 1.058246
#define HMC5883L_GAINY3 0.008017
#define HMC5883L_GAINZ1 0.018317
#define HMC5883L_GAINZ2 0.008017
#define HMC5883L_GAINZ3 1.095559
#endif
*/
/* A sensor1
#if HMC5883L_CALIBRATED == 1
#define HMC5883L_OFFSETX 0.96
#define HMC5883L_OFFSETY -0.025833
#define HMC5883L_OFFSETZ -0.015878
#define HMC5883L_GAINX1 -0.025833
#define HMC5883L_GAINX2 0.0945706
#define HMC5883L_GAINX3 -0.006488
#define HMC5883L_GAINY1 -0.025833
#define HMC5883L_GAINY2 0.945706
#define HMC5883L_GAINY3 -0.006488
#define HMC5883L_GAINZ1 -0.015878
#define HMC5883L_GAINZ2 -0.006488
#define HMC5883L_GAINZ3 0.913089
#endif
*/


//A^-1 sensor2
#if HMC5883L_CALIBRATED == 1
#define HMC5883L_OFFSETX -16.656539
#define HMC5883L_OFFSETY -177.283870
#define HMC5883L_OFFSETZ 77.193884
#define HMC5883L_GAINX1 1.094365
#define HMC5883L_GAINX2 0.024061
#define HMC5883L_GAINX3 0.005204
#define HMC5883L_GAINY1 0.024061
#define HMC5883L_GAINY2 1.067757
#define HMC5883L_GAINY3 0.024715
#define HMC5883L_GAINZ1 0.005204
#define HMC5883L_GAINZ2 0.024715
#define HMC5883L_GAINZ3 1.136209
#endif

/*
//A sensor2
#if HMC5883L_CALIBRATED == 1
#define HMC5883L_OFFSETX -16.656539
#define HMC5883L_OFFSETY -177.283870
#define HMC5883L_OFFSETZ 77.193884
#define HMC5883L_GAINX1 0.914241
#define HMC5883L_GAINX2 -0.020515
#define HMC5883L_GAINX3 -0.003741
#define HMC5883L_GAINY1 -0.020515
#define HMC5883L_GAINY2 0.937475
#define HMC5883L_GAINY3 -0.020298
#define HMC5883L_GAINZ1 -0.003741
#define HMC5883L_GAINZ2 -0.020298
#define HMC5883L_GAINZ3 0.880578
#endif
*/

//functions
void hmc5883l_init_4s();
void hmc5883l_getrawdata_4s(int16_t *mxraw1, int16_t *myraw1, int16_t *mzraw1,
		int16_t *mxraw2, int16_t *myraw2, int16_t *mzraw2,
		int16_t *mxraw3, int16_t *myraw3, int16_t *mzraw3,
		int16_t *mxraw4, int16_t *myraw4, int16_t *mzraw4);
void hmc5883l_getdata_4s(double *mx2, double *my2, double *mz2, double *mx3,
		double *my3, double *mz3, double *mx4, double *my4, double *mz4,
		double *mx5, double *my5, double *mz5);

#endif
