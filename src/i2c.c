/*
 * i2c.c
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */



#include "i2c.h"
#include "i2c_minimal.h"

void i2c_init()
{
	i2cInit();
}

void i2c_transfer_write(uint8_t* data,uint8_t dl)
{
	uint8_t i;
	i2cSendStart();
	i2cWaitForComplete();
	for(i=0; i < dl; i++)
	{
		i2cSendByte(data[i]);
		i2cWaitForComplete();
	}
	i2cSendStop();
}

void i2c_transfer_read_with_cmd(uint8_t wcmd,uint8_t* data,uint8_t dl)
{
	uint8_t i;
	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte(wcmd);
	i2cWaitForComplete();

	for(i=0; i < dl; i++)
	{
		i2cReceiveByte(TRUE);
		i2cWaitForComplete();
		data[i] = i2cGetReceivedByte();
		i2cWaitForComplete();
	}

	i2cSendStop();
	i2cWaitForComplete();
}

void i2c_transfer_read_burst(uint8_t wadr,uint8_t radr,uint8_t reg_nr,uint8_t* data,uint8_t dl)
{
	uint8_t i;
	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte(wadr);
	i2cWaitForComplete();

	i2cSendByte(reg_nr);
	i2cWaitForComplete();

	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte(radr);
	i2cWaitForComplete();


	for(i=0;i<dl;i++)
	{
		if(i == dl-1)
		{
			// send NACk for the last byte
			i2cReceiveByte(FALSE);
		}
		else
		{
			i2cReceiveByte(TRUE);
		}

		i2cWaitForComplete();
		data[i] = i2cGetReceivedByte();
		i2cWaitForComplete();
	}

	i2cSendStop();
	i2cWaitForComplete();

}
