/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.h
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
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _DISPLAY_H
  #define _DISPLAY_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/********************** External declaration of Variables ******************/
extern xQueueHandle digi_queue;
extern xSemaphoreHandle display_signal;

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

void angle_task(void *vParameters);
void display_task(void *pvParameters);

/****************************** End Of Module *******************************/
#endif
