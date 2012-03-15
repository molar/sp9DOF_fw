/*
 * main.c
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */

#include <stdint.h>


#include <avr/io.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "uart.h"
#include "compass.h"
#include "gyro.h"
#include "accelerometer.h"

// static content *SPIMU,,,,,,*XX\cr\lf = 17 + dynamic content
// max dynamic = 6 * 6
// total = 53
#define MAX_BUF_LENGTH 53

struct imu_data
{
	int16_t acc_x;
	int16_t acc_y;
	int16_t acc_z;
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
};

struct compass_data
{
	int16_t x;
	int16_t y;
	int16_t z;
};

char str_imu_buf[MAX_BUF_LENGTH];
char str_cmp_buf[MAX_BUF_LENGTH];

//atmega328p
typedef enum {NORMAL,CALIBRATION} state_t;

volatile uint32_t ticks = 0;

#define TICKS_PER_S 100

void configure_timer(uint16_t cnt_val)
{
	// CTC operation clear when reaching OCR1A value
	TCCR1A = 0;

	TIMSK1 = (1 << OCIE1A);


	OCR1A = cnt_val;

	// enable timer
	TCCR1B = (1 << CS11) | (1 << WGM12);

}

ISR(TIMER1_COMPA_vect)
{
	ticks++;
}

uint8_t calculate_checksum(char* str)
{
	uint8_t chk=0;
	// forward str 1 entries skipping the $
	str++;

	while((*str !='*') && (*str != '\0'))
	{
		chk ^= (uint8_t)*str++;
	}

	return chk;
}

void to_upper(char* buf,uint8_t nr)
{
	uint8_t i = 0;
	for(i=0;i<nr;i++)
	{
		if(buf[i] > 0x60 && buf[i] < 0x67)
		{
			buf[i] -= 0x20;
		}
	}
}

void write_data_with_checksum_to_str(uint8_t* data,uint8_t dl,char* buf)
{
	uint8_t i;
	uint8_t chk=0;
	// typecast imu_data struct into an array of 16bit integers for easy loop access
	int16_t* arr = (int16_t*)data;
	// create local iterator of pointer
	char* buf_iter = buf;

	// skip pre written header
	buf_iter += 6;


	for(i=0;i<dl;i++)
	{
		*buf_iter++ = ',';
		itoa(arr[i],buf_iter,10);
		// forward buf iter to end of written value
		while(*buf_iter != '\0') buf_iter++;

	}

	// end of data
	*buf_iter++ = '*';

	chk = calculate_checksum(buf);

	// write checksum as hex
	utoa(chk,buf_iter,16);

	to_upper(buf_iter,2);

	// forward buffer to end
	while(*buf_iter != '\0') buf_iter++;

	*buf_iter++ = '\r';
	*buf_iter++ = '\n';

	*buf_iter = '\0';
}

int main(void)
{

	ticks = 0;
	str_imu_buf[0] ='$';
	str_imu_buf[1] ='S';
	str_imu_buf[2] ='F';
	str_imu_buf[3] ='I';
	str_imu_buf[4] ='M';
	str_imu_buf[5] ='U';

	str_cmp_buf[0] ='$';
	str_cmp_buf[1] ='S';
	str_cmp_buf[2] ='F';
	str_cmp_buf[3] ='M';
	str_cmp_buf[4] ='A';
	str_cmp_buf[5] ='G';


	uint8_t magnetomenter_timer = 0;
	struct imu_data imu;
	imu.acc_x = imu.acc_y = imu.acc_z = 0;
	imu.gyro_x = imu.gyro_y = imu.gyro_z = 0;

	struct compass_data cmp;

	cmp.x = cmp.y = cmp.z = 0;

	DDRB |= (1 << PB5);
	PORTB &= ~(1 << PB5);

	uart_init(16);

	uart_write_string("Uart initialised!\n");

	i2c_init();

	compass_init(	COMPASS_CONFIG_AVERAGE1,
					COMPASS_CONFIG_RATE_75,
					COMPASS_CONFIG_MEAS_NORMAL,
					COMPASS_CONFIG_GAIN_2_5,
					COMPASS_MODE_CONTINUOUSLY);

	gyro_init(79, GYRO_LP_256Hz);

	accelerometer_init();

	configure_timer(10000);
	// enable interupts;
	sei();

	while(1)
	{
		if(ticks > 0)
		{

			ticks--;
			if(ticks>0)
			{
				// if the loop failed to run in sync skip missed ticks
				ticks=0;
			}

			magnetomenter_timer++;

			PORTB |= (1 << PB5); //debug and running indicator

			accelerometer_get_result(&(imu.acc_x),&(imu.acc_y),&(imu.acc_z));
			gyro_get_result(&(imu.gyro_x),&(imu.gyro_y),&(imu.gyro_z));

			write_data_with_checksum_to_str((uint8_t*)&imu,6,str_imu_buf);

			uart_write_string(str_imu_buf);

			if(magnetomenter_timer >= 6)
			{
				magnetomenter_timer = 0;
				compass_get_result(&(cmp.x),&(cmp.y),&(cmp.z));
				write_data_with_checksum_to_str((uint8_t*)&cmp,3,str_cmp_buf);
				uart_write_string(str_cmp_buf);
			}

			PORTB &= ~(1 << PB5); //debug and running indicator

		}
	}
	return 0;
}


