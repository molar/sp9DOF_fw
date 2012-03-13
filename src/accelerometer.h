/*
 * accelerometer.h
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_
#include <stdint.h>
void accelerometer_init();
void accelerometer_get_result(int16_t* x,int16_t* y, int16_t* z);
void accelerometer_calibrate();

#endif /* ACCELEROMETER_H_ */
