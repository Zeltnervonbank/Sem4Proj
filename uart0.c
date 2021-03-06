#include "emp_type.h"
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "uart0.h"


void task_uart_rx(void* vparameter ){
    while(1){
        if(rx_rdy){
            INT8U data =  read_Char_Blocking();
            xQueueSend(q_uart_rx, &data, 0);
        }else{
            taskYield();
        }
    }
}

void task_uart_tx(void* vparameter ){
    INT8U ch;
    while(1){
        if(xQueueReceive(q_uart_tx, &ch, 0)){
            //INT8U data =  read_Char_Blocking();
            printChar(ch);
        }else{
            //taskYield();
        }
    }
}


void printChar(INT8U c)
{
    //909
    while((UART0_FR_R & (1<<5)) != 0);
    UART0_DR_R = c;
}
void printLong(INT16U l)
{
    INT8U upper = l >> 8;
    INT8U lower = (INT8U) l;
    printChar(upper);
    printChar(lower);
}

void printString(INT8U * string)
{
    while(*string)
    {
        printChar(*(string++));
    }
}

INT8U rx_rdy(){
    return (UART0_FR_R & (1<<4)) == 0; //Checks if the UART
}

INT8U read_Char_Blocking()
{
    INT8U c;
    while((UART0_FR_R & (1<<4)) != 0); //Waits until there is data in the UART data register
    c = UART0_DR_R; //Returns the data in the UART data register
    return c;
}
INT8U read_Char()
{
    INT8U c;
    if((UART0_FR_R & (1<<4)) == 0) //Checks if there is data in the UART data register
    {
        c = UART0_DR_R;
        return c;
    }
    return 0x00;
}

extern void uart0_init(INT32U baud_rate)
{
  INT32U BRD;

  #ifndef E_PORTA
  #define E_PORTA
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // Enable clock for Port A
  #endif

  #ifndef E_UART0
  #define E_UART0
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // Enable clock for UART 0
  #endif

  GPIO_PORTA_AFSEL_R |= 0x00000003;     // set PA0 og PA1 to alternative function (uart0)
  GPIO_PORTA_DIR_R   |= 0x00000002;     // set PA1 (uart0 tx) to output
  GPIO_PORTA_DIR_R   &= 0xFFFFFFFE;     // set PA0 (uart0 rx) to input
  GPIO_PORTA_DEN_R   |= 0x00000003;     // enable digital operation of PA0 and PA1

  BRD = 64000000 / baud_rate;           // X-sys*64/(16*baudrate) = 16M*4/baudrate
  UART0_IBRD_R = BRD / 64;
  UART0_FBRD_R = BRD & 0x0000003F;

  UART0_LCRH_R  = (0x3<<5);             //8-Bit data size

  UART0_LCRH_R  &= 0xFFFFFFEF;

  UART0_CTL_R  |= (UART_CTL_UARTEN | UART_CTL_TXE );  // Enable UART
}
