/*
 * gyro.h
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */

#ifndef GYRO_H_
#define GYRO_H_

#include <stdint.h>

#define GYRO_READ 0xD1
#define GYRO_WRITE 0xD0

typedef enum
{
	GYRO_LP_256Hz = 0,
	GYRO_LP_188Hz = 1,
	GYRO_LP_98Hz = 2,
	GYRO_LP_42HZ = 3,
	GYRO_LP_20Hz = 4,
	GYRO_LP_10Hz = 5,
	GYRO_LP_5Hz = 6
}gyro_lp_filter_t;


void gyro_init(uint8_t sample_rate_div,gyro_lp_filter_t low_pass);
void gyro_get_result();
void gyro_calibrate();


#endif /* GYRO_H_ */
