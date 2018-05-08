/*
 * string.h
 *
 *  Created on: 26/12/2011
 *      Author: Morten
 */
#include "device.h"

void putc1( DEVICE, unsigned char );
const void gfprintf( DEVICE, const char*, ...);
const void gsprintf( INT8U*, const char*, ...);
const void gprintf( const char *, ...);