/***************************** Include files *******************************/
#include <stdint.h>
#include "glob_def.h"
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "portmacro.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "device.h"
#include "lcd.h"

/*****************************    Defines    *******************************/
#define MAX_DEVICES  8

typedef struct
{
  BOOLEAN (*put)(INT8U);   // Pointer to device put function
  BOOLEAN (*get)(INT8U*);  // Pointer to device get function
} fcb;  //device control block

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
fcb pof[MAX_DEVICES];	            // Pool of foles

/*****************************   Functions   *******************************/

BOOLEAN put_file( DEVICE device, INT8U ch )
{
  if( pof[(int)device].put )
    pof[(int)device].put( ch );
}

BOOLEAN get_file( DEVICE device, INT8U *pch )
{
  BOOLEAN result = FALSE;

  if( pof[(int)device].get )
    result = pof[(int)device].get( pch );
  return( result );
}


void init_files()
/*****************************************************************************
*   Function : See module specification (.h-device).
*****************************************************************************/
{
  INT8U i;

  for( i = 0; i < MAX_DEVICES; i++ )
  {
	  pof[i].put = NULL;
	  pof[i].get = NULL;
  }
  pof[COM2].put = wr_ch_LCD;

}

/****************************** End Of Module *******************************/











