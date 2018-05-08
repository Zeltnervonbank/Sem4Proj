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
#include "digiswitch.h"
/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
void init_digiswitch(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    INT8U dummy;

    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;

    dummy = SYSCTL_RCGC2_R;

    GPIO_PORTA_DEN_R |= 0xE0;
}

INT8U button_pushed()
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    return ( !(GPIO_PORTA_DATA_R & 0x80));
}

INT8U get_position()
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    return ( GPIO_PORTA_DATA_R & 0x60);
}


void digiswitch_task(void *pvParameters)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    init_digiswitch();

    INT8U position = get_position();
    INT8U new_position;
    INT8U event;
    INT8U yy;

    while(1)
    {

        new_position = get_position();

        if( button_pushed())
        {
            event = RESET;
            xQueueSend(digi_queue, &event, 10);
            vTaskDelay(10);

        }

        if( position != new_position )
        {
            yy = position ^ new_position;

            switch(new_position)
            {
            case 0x00:
                if(yy == 0x20)
                {
                    event = C_CLOCKWISE;
                }
                if(yy == 0x40)
                {
                    event = CLOCKWISE;
                }
                break;
            case 0x60:
                if(yy == 0x20)
                {
                    event = C_CLOCKWISE;
                }
                if(yy == 0x40)
                {
                    event = CLOCKWISE;
                }
                break;
            case 0x20:
                if(yy == 0x20)
                {
                    event = CLOCKWISE;
                }
                if(yy == 0x40)
                {
                    event = C_CLOCKWISE;
                }
                break;
            case 0x40:
                if(yy == 0x20)
                {
                    event = CLOCKWISE;
                }
                if(yy == 0x40)
                {
                    event = C_CLOCKWISE;
                }
                break;
            default:
                break;
            }
            xQueueSend(digi_queue, &event, 10);

            position = new_position;

        }
        vTaskDelay(1);
    }
}


/****************************** End Of Module *******************************/
