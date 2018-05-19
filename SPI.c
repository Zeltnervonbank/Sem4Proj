/*
* SPI.C
*
*  Created on: 12. maj 2018
*      Author: aszel
*/

#include "emp_type.h"
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "uart0.h"

void init_SPI()
{
    //Enable the SSI module using the RCGCSSI register (see page 345).
    SYSCTL_RCGCSSI_R = (1<<2);

    //Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 339).
    //To find out which GPIO port to enable, refer to Table 23-5 on page 1346.
    SYSCTL_RCGCGPIO_R = (1<<1);

    //Set the GPIO AFSEL bits for the appropriate pins (see page 669). To determine which GPIOs to
    //configure, see Table 23-4 on page 1339.
    //Enables alternate functions on GPIO pins.
    GPIO_PORTB_AFSEL_R |= (1<<4)|(1<<6)|(1<<7)|(1<<5);

    //Page 686, Port control register
    //Sets mux control on pins 4-7
    GPIO_PORTB_PCTL_R |= (2<<16)|(2<<20)|(2<<24)|(2<<28);

    //Page 680, GPIO Digital Enable
    //Enables digital function on pins 4-7
    GPIO_PORTB_DEN_R   |= (1<<4)|(1<<5)|(1<<6)|(1<<7);

    //Page 968, SSI Control Register 1
    //Sets bit 1 - Synchronous Serial Port Enable - actually not sure what's happening here
    SSI2_CR1_R  &= ~(1<<1);

    //Clears register
    SSI2_CR1_R  = 0x00000000;

    //Page 981, SSI Clock control register
    //Clears register - defaults to system clock
    SSI2_CC_R = 0x00;

    //Page 973, SSI Clock Prescaler register
    //Sets factor 10 divisor
    SSI2_CPSR_R = 30;

    //Page 966, SSI Control Register 0
    //Sets data size to 16 bit
    SSI2_CR0_R = (0xF<<0);

    //Sets stuff
    SSI2_CR1_R |= (1<<1);
}

void write_SPI(INT16U data)
{
    SSI2_DR_R = data; //Write data to data register
    while( (SSI2_SR_R & (1<<0)) == 0); //Wait until transmit FIFO empty
}
INT16U read_SPI()
{
    while( (SSI2_SR_R & (1<<2)) == 0); //Wait until receive FIFO not empty
    return SSI2_DR_R; //Return contents of data register
}
INT16U read_Write_Reg(INT8U RW, INT8U address, INT16U data)
{
    if(address < 8)
    {
        //Set R/W, Address and Data
        INT16U SPI_Data = RW << 15 | address << 12 | (0xFFF & data);
        write_SPI(SPI_Data); //Write data
        return read_SPI(); //Read data
    }
    return 0xEEEE;
}

INT16U read_Reg(INT8U address)
{
    return read_Write_Reg(0, address, 0x0000);
}
void write_Reg(INT8U address, INT16U data)
{
    read_Write_Reg(1, address, data);
    return;
}

