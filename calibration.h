/*
 * calibration.h
 *
 *  Created on: 15 апр. 2015 г.
 *      Author: DDDD
 */



#ifndef CALIBRATION_H_
#define CALIBRATION_H_

extern float biasX_s[];
extern float biasY_s[];
extern float biasZ_s[];
extern float gainX1_s[];
extern float gainX2_s[];
extern float gainX3_s[];
extern float gainY1_s[];
extern float gainY2_s[];
extern float gainY3_s[];
extern float gainZ1_s[];
extern float gainZ2_s[];
extern float gainZ3_s[];

//void getDataForCalibration();
void Calibrate();
//function just for testing!!!!!
void Calibrate1();


#endif /* CALIBRATION_H_ */
