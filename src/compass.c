/*
 * compass.c
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */

#include "compass.h"
#include "i2c.h"

void compass_init(
		compass_config_average_t avg,
		compass_config_rate_t rate,
		compass_config_meas_t type,
		compass_config_gain_t gain,
		compass_mode_t mode)
{
	i2c_dev_register_t cmd;
	cmd.address = COMPASS_I2C_ADDRESS;
	cmd.reg_nr = COMPASS_CONFIGA_REG;
	cmd.data = (avg << 5) | (rate << 2) | (type);

	i2c_transfer_write((uint8_t*)&cmd,sizeof(cmd));

	cmd.reg_nr = COMPASS_CONFIGB_REG;
	cmd.data = (gain << 5);

	i2c_transfer_write((uint8_t*)&cmd,sizeof(cmd));

	cmd.reg_nr = COMPASS_MODE_REG;
	cmd.data = mode;

	i2c_transfer_write((uint8_t*)&cmd,sizeof(cmd));
}



uint8_t compass_get_result(int16_t* x,int16_t* y, int16_t* z)
{
	int16_t xzy[3];
	uint8_t cmd[2];

	//reset read pointer'
	cmd[0] = 0x3C;
	cmd[1] = 0x03;
	i2c_transfer_write(cmd,sizeof(cmd));

	i2c_transfer_read_with_cmd(COMPASS_READ_DATA_CMD,(uint8_t*)&xzy,sizeof(xzy));

	*x = xzy[0];
	*y = xzy[2];
	*z = xzy[1];



	return 1;

}

void compass_calibrate()
{

}


