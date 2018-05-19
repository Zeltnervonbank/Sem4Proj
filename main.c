/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Assignment 2, main module. No main.h file.
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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "status_led.h"


/*****************************    Defines    *******************************/
#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define IDLE_PRIO 0
#define LOW_PRIO  1
#define MED_PRIO  2
#define HIGH_PRIO 3


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

void float_task( void *pvParameter);
void init_shit(void);

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
    init_shit();


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

    //Setup Queues.
    //-----------------

    //Setup Semaphores.
    //-----------------

    // Start the tasks.
    // ----------------
    return_value &= xTaskCreate( float_task, "Float_LED", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
    return_value &= xTaskCreate( status_led_task, "Status_led", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );

    if (return_value != pdTRUE)
    {
      GPIO_PORTD_DATA_R &= 0xBF;  // Turn on status LED.
      while(1);  // could not create one or more tasks.
    }
    // Start the scheduler.
    // --------------------
    vTaskStartScheduler();

    // Will only get here, if there was insufficient memory.
    // -----------------------------------------------------
    return 1;
}

void float_task(void *pvParameters)
{
    float tal1 = 0.512;
    tal1 += 0.0003;

    while(1)
    {
        if(tal1 == 0.5123)
        {
            GPIO_PORTF_DATA_R ^= 0x02;
            tal1 = tal1 + 0.5123;
        }
        vTaskDelay(20);
        if(tal1 == 1.0246)
        {
            GPIO_PORTF_DATA_R ^= 0x04;
            tal1 = tal1-0.5123;
        }
        vTaskDelay(20);
    }

}

void init_shit(void)
{
    // Enable the GPIO port that is used for the on-board LED.
    SYSCTL_RCGC2_R  =  SYSCTL_RCGC2_GPIOA |SYSCTL_RCGC2_GPIOC | SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOE |SYSCTL_RCGC2_GPIOF;
    SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;

    // Do a dummy read to insert a few cycles after enabling the peripheral.
    dummy = SYSCTL_RCGC2_R;

    // Set the direction as output (PF1, PF2 and PF3).
    GPIO_PORTA_DIR_R = 0x1C;
    GPIO_PORTC_DIR_R = 0xF0;
    GPIO_PORTD_DIR_R = 0x4C;
    GPIO_PORTF_DIR_R = 0x0E;

    // Enable the GPIO pins for digital function (PF0, PF1, PF2, PF3, PF4).
    GPIO_PORTA_DEN_R = 0x1C;
    GPIO_PORTC_DEN_R = 0xF0;
    GPIO_PORTD_DEN_R = 0x4C;
    GPIO_PORTE_DEN_R = 0x0F;
    GPIO_PORTF_DEN_R = 0x1F;

    // Enable internal pull-up (PF0 and PF4).
    GPIO_PORTF_PUR_R = 0x11;
}
/****************************** End Of Module *******************************/
