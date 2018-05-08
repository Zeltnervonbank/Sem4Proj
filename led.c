/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: leds.c
*
* PROJECT....: ECP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
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
#include "digiswitch.h"
#include "led.h"
//#include "glob_def.h"
//#include "status_led.h"


/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
void led_task(void *vParameters)
{
    INT8U event = 0;

    while(1)
    {
        if(xQueueReceive(digi_queue, &event, 1))
        {
            switch(event)
            {
            case CLOCKWISE:
                GPIO_PORTF_DATA_R &= ~(0xFF);
                GPIO_PORTF_DATA_R |= 0x08;
                break;
            case C_CLOCKWISE:
                GPIO_PORTF_DATA_R &= ~(0xFF);
                GPIO_PORTF_DATA_R |= 0x04;
            }
        }
        vTaskDelay(10);
    }
}
