/*
 * uart0.h
 *
 *  Created on: 11. maj 2018
 *      Author: aszel
 */

#ifndef UART0_H_
#define UART0_H_

void init_UART();
void printChar(INT8U c);
void printLong(INT16U l);
void printString(INT8U * string);

INT8U rx_rdy();
INT8U read_Char();
INT8U read_Char_Blocking();
void uart0_init( INT32U baud_rate);


#endif /* UART0_H_ */
