/*
 * SPI.h
 *
 *  Created on: 12. maj 2018
 *      Author: aszel
 */

#ifndef SPI_H_
#define SPI_H_

void init_SPI();
void write_SPI(INT16U data);
INT16U read_SPI();
INT16U read_Write_SPI(INT16U data);

INT16U read_Write_Reg(INT8U RW, INT8U address, INT16U data);
INT16U read_Reg(INT8U address);
void write_Reg(INT8U address, INT16U data);

#endif /* SPI_H_ */
