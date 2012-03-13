/*
 * uart.c
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */

#include "uart.h"
#include <avr/io.h>



void uart_init(unsigned int ubrr)
{
	int ubrr_new;
	// set baud rate
	ubrr_new = ubrr;
	UBRR0H = ubrr_new>>8;
	UBRR0L = ubrr_new;

	// Enable receiver and transmitter
	UCSR0A = (1<<U2X0); //double the speed
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	// Set frame format: 8 bit, no parity, 1 stop bit,
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}

uint8_t uart_has_byte()
{
	return (UCSR0A & (1<<RXC0));
}

uint8_t uart_get_byte()
{
	return UDR0;
}

void uart_put_byte(uint8_t byte)
{
	//wait until uart ready
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = byte;


}

int uart_putchar(char c, FILE *stream)
{
    if (c == '\n') uart_putchar('\r', stream);

    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;

    return 0;
}

void uart_write_string(char* str)
{
	while(*str != '\0')
	{
		uart_put_byte(*str);
		str++;
	}
}

