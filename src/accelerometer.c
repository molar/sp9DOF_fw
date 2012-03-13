/*
 * accelerometer.c
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */


#include "accelerometer.h"
#include "i2c.h"

#define ACC_ADR_READ 0xA7
#define ACC_ADR_WRITE 0xA6

#define ACC_PWR_REG 0x2D
#define ACC_DATA_FORMAT_REG 0x31
#define ACC_DATA_START_REG 0x32

void accelerometer_init()
{
	i2c_dev_register_t cmd;

	cmd.address = ACC_ADR_WRITE;
	cmd.reg_nr = ACC_PWR_REG;
	cmd.data = 0x08; // measurement mode

	i2c_transfer_write(&cmd,sizeof(cmd));

	cmd.reg_nr = ACC_DATA_FORMAT_REG;
	cmd.data = (1 << 3) | (1 << 1) | (1 << 0);

	i2c_transfer_write(&cmd,sizeof(cmd));


}

void accelerometer_get_result(int16_t* x,int16_t* y,int16_t* z)
{
	uint8_t xyz[6];

	i2c_transfer_read_burst(ACC_ADR_WRITE,ACC_ADR_READ,ACC_DATA_START_REG,(uint8_t*)&xyz,sizeof(xyz));


	*x = xyz[0] | (uint16_t)xyz[1] << 8;

	*y = xyz[2] | (uint16_t)xyz[3] << 8;

	*z = xyz[4] | (uint16_t)xyz[5] << 8;


}

void accelerometer_calibrate()
{

}
