/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"
#include "emp_type.h"
#include "lcd.h"
#include "device.h"
#include "string.h"
#include "display.h"

/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
INT16S counter = 0;
INT16S angle = 0;

/*****************************   Functions   *******************************/


void display_task(void * vParameters)
{
    while(1)
    {
        if(xSemaphoreTake(display_signal, 10))
        {
             gfprintf(COM2, "%c%c Angle: %04d%c", ESC, '@', angle, 0xDF);
        }
    }
}
