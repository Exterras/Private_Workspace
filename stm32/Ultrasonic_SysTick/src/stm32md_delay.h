// =============================================================
//
//	STM32F10x MD Devices Delay Fuctions : stm32md_delay.h
//
//								2014.  1.  5.	by GroundZero
//
// =============================================================

#pragma once
//#ifndef	_STM32MD_DELAY_H_
//#define	_STM32MD_DELAY_H_
//#endif

#if SYSCLK == 36	// -----------------------------------------

void delay_us(unsigned int us)
{
	while(us--)
	{
		asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
		asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
		asm("nop\n");asm("nop\n");
	}
}

void delay_ms(unsigned int ms)
{
	unsigned int i;

	while(ms--)
	{
		for(i=0;i<999;i++)
		{
			asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
			asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
			asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
		}
	}
}

#elif SYSCLK == 72	// -----------------------------------------

void delay_us(unsigned int us)
{
	while(us-->1)
	{
		asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
		asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
		asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
		asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
		asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
		asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
		asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
		asm("nop\n");asm("nop\n");asm("nop\n");
	}
}

void delay_ms(unsigned int ms)
{
	unsigned int i;

	while(ms--)
	{
		for(i=0;i<999;i++)
		{
			asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
			asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
			asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
			asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
			asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
			asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
			asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
			asm("nop\n");asm("nop\n");asm("nop\n");
		}
	}
}

#endif			// -----------------------------------------
