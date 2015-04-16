/*
 * Sensor.c
 *
 *  Created on: 28 џэт. 2015 у.
 *      Author: DDDD
 */
#include "Sensor.h"
#include <avr/io.h>
#include "i2cmaster.h"

void WriteToSensor(char r_address, char r_data){

	//Master|| ST | SAD + W  |  SUB | DATA  |  DATA  |  SP
	//Slave||               SAK    SAK     SAK       SAK

		//Start communication and transmit slave address +write bit
		i2c_start(SENSOR1_ADDR+I2C_WRITE);

		//Write register address
		i2c_write(r_address|(READ_MULTIPLE_BYTES));

		i2c_write(r_data);

		//Stop communication
		i2c_stop();
}

void EcompassInit(void)
{
    // Accelerometer

	/* 362 Hz Acceleration anti-alias filter bandwidth
	 * full-scale selection +- 2g
	*/

	WriteToSensor(CTRL2, 0b10000000);
    /* Acceleration data-rate configuration 3.125 Hz
     * Enable x, z, y axis
     */
	WriteToSensor(CTRL1, 0b00010111);

	//WriteToSensor(CTRL1, 0b01010111);


    /* High-pass filer normal mode
     * AFDS   - 1 (data from interlan filter sent to FIFO output
     * T_ONLY - 0  No temperature (use magnetic sensor )
     * magnetic daca configured from CTRL 5, continous conversion
     */
	WriteToSensor(CTRL7, 0b01100100);

    /*
     *  temp_en -> off
     *  magnetic resolution -> high
     *  50 hz data rate selection / 3.125 Hz
     */
	WriteToSensor(CTRL5, 0b01100000);

	WriteToSensor(CTRL6, 0b00000000);
	//!!!!!!!!!!!#######
////   FIFO_POS = 0;
}




char Geti2cSensorData(char s_address,  char r_address)
{
	char Ack, Nack;

		//Start communication and transmit slave address +write bit
		i2c_start(s_address&0b11111110);

		//Write register address
		i2c_write(r_address|(READ_MULTIPLE_BYTES));

		//Repeated start and transmit slave address +read bit
		while(i2c_rep_start(s_address|0x01));

		//read data
		Ack = (i2c_readNak());   //Ack

		//while(i2c_rep_start(SENSOR_ADDR+I2C_READ));
		Nack = i2c_readNak();

		//Stop communication
		i2c_stop();

		return Ack;

}


