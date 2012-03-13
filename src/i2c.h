/*
 * i2c.h
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */

#ifndef I2C_H_
#define I2C_H_
#include <stdint.h>
typedef struct
{
	uint8_t address;
	uint8_t reg_nr;
	uint8_t data;

}i2c_dev_register_t;

void i2c_init();
void i2c_transfer_read_with_cmd(uint8_t wcmd,uint8_t* data,uint8_t dl);
void i2c_transfer_write(uint8_t* data,uint8_t dl);

void i2c_transfer_read_burst(uint8_t wadr,uint8_t radr,uint8_t reg_nr,uint8_t* data,uint8_t dl);

#endif /* I2C_H_ */
