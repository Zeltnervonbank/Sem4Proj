/*
 * device.h
 *
 *  Created on: 26/12/2011
 *      Author: Morten
 */



#ifndef DEVICE_H_
#define DEVICE_H_

#include "emp_type.h"

typedef INT8U* DEVICE;

#define COM1  0      // UART
#define COM2  1      // LCD
#define COM3  2      // Keyboard

BOOLEAN put_device( DEVICE, INT8U );
void init_files();

#endif /* DEVICE_H_ */
