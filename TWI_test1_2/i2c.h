/*
 * I2c.h
 *
 *  Created on: 25 џэт. 2015 у.
 *      Author: DDDD
 */

#ifndef I2C_H_
#define I2C_H_

void iic_masterinit(void);
void iic_start(void);
void iic_addop(unsigned char addop);
unsigned char iic_read(void);
void iic_stop(void);
unsigned char I2C_GetStatus(void);

#endif /* I2C_H_ */
