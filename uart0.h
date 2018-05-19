/*
 * uart0.h
 *
 *  Created on: 11. maj 2018
 *      Author: aszel
 */

#ifndef UART0_H_
#define UART0_H_

extern xQueueHandle q_uart_tx;
extern xQueueHandle q_uart_rx;

//void init_UART();
void printChar(INT8U c);
void printLong(INT16U l);
void printString(INT8U * string);

INT8U rx_rdy();
INT8U read_Char();
INT8U read_Char_Blocking();
void uart0_init( INT32U baud_rate);

void task_uart_rx(void*);
void task_uart_tx(void*);

#endif /* UART0_H_ */
