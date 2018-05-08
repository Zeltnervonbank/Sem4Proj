/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Assignment 8, main module. No main.h file.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "systick_frt.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "status_led.h"
#include "digiswitch.h"
#include "gpio.h"
#include "led.h"
#include "lcd.h"
#include "device.h"
#include "string.h"
#include "display.h"

/*****************************    Defines    *******************************/
#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define IDLE_PRIO 0
#define LOW_PRIO  1
#define MED_PRIO  2
#define HIGH_PRIO 3


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

xQueueHandle digi_queue;
xQueueHandle lcd_queue;
xSemaphoreHandle display_signal;
/*****************************   Functions   *******************************/


int putChar()
/*****************************************************************************
*   Input    :  -
*   Output   :  Result
*   Function :  putChar for FreeRTOS debug functionality.
*****************************************************************************/
{
  return(0);
}

static void setupHardware(void)
/*****************************************************************************
*   Input    :  -
*   Output   :  -
*   Function :
*****************************************************************************/
{
  // TODO: Put hardware configuration and initialisation in here

  // Warning: If you do not initialize the hardware clock, the timings will be inaccurate
  init_systick();
  init_gpio();
  status_led_init();
  init_lcd();
  init_files();
}



int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
    portBASE_TYPE return_value = pdTRUE;

    setupHardware();

    digi_queue = xQueueCreate(10, sizeof(INT8U));
    lcd_queue = xQueueCreate(1000, sizeof(INT8U));

    vSemaphoreCreateBinary(display_signal);


    if(lcd_queue == NULL)
    {
        GPIO_PORTF_DATA_R |= 0x02;
        while(1);
    }

    // Start the tasks.
    // ----------------
    return_value &= xTaskCreate( status_led_task, ( signed portCHAR * ) "Status_led", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
    return_value &= xTaskCreate( digiswitch_task, ( signed portCHAR * ) "Digiswitch", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
    //return_value &= xTaskCreate(led_task, ( signed portCHAR * ) "LED", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
    return_value &= xTaskCreate(lcd_task, (signed portCHAR * ) "LCD", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);
    return_value &= xTaskCreate(angle_task, (signed portCHAR * ) "Angle", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);
    return_value &= xTaskCreate(display_task, (signed portCHAR * ) "Display", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);

    if (return_value != pdTRUE)
    {
      GPIO_PORTD_DATA_R &= 0xBF;  // Turn on status LED.
      while(1);  // cold not create one or more tasks.
    }


  // Start the scheduler.
  // --------------------
  vTaskStartScheduler();

  // Will only get here, if there was insufficient memory.
  // -----------------------------------------------------
  return 1;
}

/****************************** End Of Module *******************************/
