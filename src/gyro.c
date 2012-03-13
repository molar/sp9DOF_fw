/*
 * gyro.c
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */

#include "gyro.h"
#include "i2c.h"

#define GYRO_SMPLRT_DIV_REG 0x15
#define GYRO_DLPF_FS_REG 0x16
#define GYRO_PWR_MGM_REG 0x3E
#define GYRO_DATA_START_REG 0x1D


// lp 256Hz = 8 Khz sample rate desired output 100Hz = sample_rate_div 79
void gyro_init(uint8_t sample_rate_div,gyro_lp_filter_t low_pass)
{
	i2c_dev_register_t cmd;

	cmd.address = GYRO_WRITE;
	cmd.reg_nr = GYRO_SMPLRT_DIV_REG;
	cmd.data = sample_rate_div;

	i2c_transfer_write((uint8_t*)&cmd,sizeof(cmd));

	cmd.reg_nr = GYRO_DLPF_FS_REG;
	cmd.data = low_pass | (3 <<3);

	i2c_transfer_write((uint8_t*)&cmd,sizeof(cmd));


}

void gyro_get_result(int16_t* x, int16_t* y, int16_t* z)
{
	uint8_t xyz[6];

	i2c_transfer_read_burst(GYRO_WRITE,GYRO_READ,GYRO_DATA_START_REG,(uint8_t*)&xyz,sizeof(xyz));

	*x = xyz[1] | (uint16_t)xyz[0] << 8 ;
	*y = xyz[3] | (uint16_t)xyz[2] << 8;
	*z = xyz[5] | (uint16_t)xyz[4] << 8;

}

void gyro_calibrate()
{

}
