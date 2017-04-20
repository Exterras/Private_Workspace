/**********************************************************************
 *  File:     main.c
 *  Purpose:  Blink LD2 on NUCLEO-103RB ( Internal 36MHz System Clock )
 *  Date:     31 December 2014
 *  Info:     Replace code to non-use SPL Code
 ***********************************************************************/

#define SYSCLK 36

#include "stm32md_reg.h"
#include "stm32md_init.h"
#include "stm32md_delay.h"

#ifndef __NO_SYSTEM_INIT

void SystemInit()
{

}

#endif

void GPIO_init(void)
{

}

int main(void)
{

    while(1)
    {

    }
}
