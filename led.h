/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: led.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 100408  KHA    Module created.
*
*****************************************************************************/

#ifndef _LEDS_H
  #define _LEDS_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/
extern xQueueHandle digi_queue;

/*****************************   Functions   *******************************/

void led_init();
void led_task(void *pvParameters);


/****************************** End Of Module *******************************/
#endif

