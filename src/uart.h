/*
 * uart.h
 *
 *  Created on: Mar 7, 2012
 *      Author: molar
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void uart_init(unsigned int ubrr);
uint8_t uart_has_byte();
uint8_t uart_get_byte();
void uart_put_byte(uint8_t byte);
int uart_putchar(char c, FILE *stream);
void uart_write_string(char* str);
#endif /* UART_H_ */
