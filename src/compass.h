/*
 * compass.h
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */

#ifndef COMPASS_H_
#define COMPASS_H_

#include <stdint.h>

#define COMPASS_I2C_ADDRESS 0x3C
#define COMPASS_CONFIGA_REG 0x00
#define COMPASS_CONFIGB_REG 0x01
#define COMPASS_MODE_REG 0x02
#define COMPASS_READ_DATA_CMD 0x3D


typedef enum {COMPASS_CONFIG_AVERAGE1=0,
				COMPASS_CONFIG_AVERAGE2=1,
				COMPASS_CONFIG_AVERAGE4=2,
				COMPASS_CONFIG_AVERAGE8=3
}compass_config_average_t;

typedef enum {
	COMPASS_CONFIG_RATE_0_75 = 0,
	COMPASS_CONFIG_RATE_1_5 = 1,
	COMPASS_CONFIG_RATE_3 = 2,
	COMPASS_CONFIG_RATE_7_5 = 3,
	COMPASS_CONFIG_RATE_15 = 4,
	COMPASS_CONFIG_RATE_30 = 5,
	COMPASS_CONFIG_RATE_75 = 6
}compass_config_rate_t;

typedef enum
{
	COMPASS_CONFIG_MEAS_NORMAL = 0,
	COMPASS_CONFIG_MEAS_PBIAS = 1,
	COMPASS_CONFIG_MEAS_NBIAS = 2,
}compass_config_meas_t;

typedef enum
{
	COMPASS_CONFIG_GAIN_0_88 = 0,
	COMPASS_CONFIG_GAIN_1_3 = 1,
	COMPASS_CONFIG_GAIN_1_9 = 2,
	COMPASS_CONFIG_GAIN_2_5 = 3,
	COMPASS_CONFIG_GAIN_4_0 = 4,
	COMPASS_CONFIG_GAIN_4_7 = 5,
	COMPASS_CONFIG_GAIN_5_6 = 6,
	COMPASS_CONFIG_GAIN_8_1 = 7

}compass_config_gain_t;

typedef enum
{
	COMPASS_MODE_CONTINUOUSLY = 0,
	COMPASS_MODE_SINGLE = 1,
	COMPASS_MODE_IDLE = 2
}compass_mode_t;

void compass_init(
		compass_config_average_t avg,
		compass_config_rate_t rate,
		compass_config_meas_t type,
		compass_config_gain_t gain,
		compass_mode_t mode);

uint8_t compass_get_result(int16_t* x,int16_t* y, int16_t* z);

void compass_calibrate();

#endif /* COMPASS_H_ */
