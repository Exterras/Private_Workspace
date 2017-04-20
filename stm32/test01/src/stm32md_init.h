// =============================================================
//
//	STM32F10x MD Devices Initialize Functions : stm32md_init.h
//
//								2014.  1.  5.	by GroundZero
//
// =============================================================

#pragma once
//#ifndef _STM32MD_INIT_H_
//#define _STM32MD_INIT_H_
//#endif

#include "stm32md_reg.h"

#if SYSCLK == 36	// ----------------------------------------------------------------------											//(PCLK1 has to be <= 36MHz)

void flash_latency(void)
{
	FLASH_ACR |=  1 << PRFTBE;	// xxxx xxxx xxxx xxxx xxxx xxxx xxx1 xxxx bit4 PRFTBE=1 Set.
	FLASH_ACR &= ~7;			// bit2,1,0 Clear
	FLASH_ACR |=  1;			// bit2,1,0 = 0,0,1
}

void set_clk(void)
{
	RCC_CR |=    1 << HSION;
	while( ( RCC_CR & ( 1 << HSIRDY ) ) == 0 );

	RCC_CFGR &= ~(  1 << PLLSRC );
	RCC_CFGR |=  (  7 << PLLMUL );
	RCC_CR   |=  (  1 << PLLON );
	while( ( RCC_CR & ( 1 << PLLRDY ) ) == 0 );

	RCC_CFGR |=  2;
	while( ( RCC_CFGR & 12 ) != 8 );

	RCC_CFGR &= ~( 15 << PPRE2 );
	RCC_CFGR &= ~(  7 << PPRE2 );
	RCC_CFGR &= ~(  7 << PPRE1 );
}

////// USART1 configuration

	// USART1 configured as follow:
	//  - BaudRate = 115,200 baud
	//  - Word Length = 8 Bits
	//  - One Stop Bit
	//  - No parity
	//  - Hardware flow control disabled (RTS and CTS signals)
	//  - Receive and transmit enabled

	// UART1 Base Address   : 0x4001 3800

void init_uart1(void)
{
	RCC_APB2ENR  |= (  1 << USART1EN );
	GPIOA_CRH    |= (  4 << MODE10 | 11 << MODE9 );

    //	When use internal Clock
	USART1_BRR  = 19 << 4 | 8;	// 115,200 bps (PCLK1 36Mhz) : DIV_Mantisa=19, DIV_Fraction=8

	// Control Register1    : USART_CR1 ADD offset(0x0C) RST Value(0x0000 0000)
	USART1_CR1  = 0x200C;		// ADD Mask WakeUP,1 Start bit, 8 Data bit, Tx Enable, Rx Enable

	// Control Register2    : USART_CR2 ADD offset(0x10) RST Value(0x0000 0000)
	USART1_CR2  = 0x0;			// 1 Stop Bit

	// Control Register3    : USART_CR3 ADD offset(0x14) RST Value(0x0000 0000)
	USART1_CR3  = 0x0;			// Hardware flow control disabled

	USART1_CR1 |= 0x2000;       // SET ADD Mask WakeUP
}

void init_uart2(void)
{
	RCC_APB1ENR  |=  (  1 << USART2EN );
	GPIOA_CRL    &= ~( 15 << MODE3 );
	GPIOA_CRL    &= ~( 15 << MODE2 );
	GPIOA_CRL    |=  (  4 << MODE3 | 11 << MODE2 ); // 0100 1011

	USART2_BRR  = 19 << 4 | 8;	// 115,200 bps (PCLK1 36Mhz) : DIV_Mantisa=19, DIV_Fraction=8

	// Control Register1    : USART_CR1 ADD offset(0x0C) RST Value(0x0000 0000)
	USART2_CR1  = 0x200C;		// ADD Mask WakeUP,1 Start bit, 8 Data bit, Tx Enable, Rx Enable

	// Control Register2    : USART_CR2 ADD offset(0x10) RST Value(0x0000 0000)
	USART2_CR2  = 0x0;			// 1 Stop Bit

	// Control Register3    : USART_CR3 ADD offset(0x14) RST Value(0x0000 0000)
	USART2_CR3  = 0x0;			// Hardware flow control disabled

	USART2_CR1 |= 0x2000;       // SET ADD Mask WakeUP
}

#elif SYSCLK == 72	// ----------------------------------------------------------------------

void flash_latency(void)
{
	FLASH_ACR |=  1 << PRFTBE;	// xxxx xxxx xxxx xxxx xxxx xxxx xxx1 xxxx bit4 PRFTBE=1 Set.
	FLASH_ACR &= ~7;			// bit2,1,0 Clear
	FLASH_ACR |=  2;			// bit2,1,0 = 0,1,0
}

 void set_clk(void)
{
	RCC_CR |=    1 << HSEON;
	while( ( RCC_CR & ( 1 << HSERDY ) ) == 0 );

	RCC_CFGR |=  (  1 << PLLSRC );
	RCC_CFGR |=  (  7 << PLLMUL );
	RCC_CR   |=  (  1 << PLLON  );
	while( ( RCC_CR & ( 1 << PLLRDY ) ) == 0 );

	RCC_CFGR |=  2;
	while( ( RCC_CFGR & 12 ) != 8 );

	RCC_CFGR &= ~( 15 << HPRE  );
	RCC_CFGR &= ~(  7 << PPRE2 );
	RCC_CFGR |=  (  4 << PPRE1 );
}

////// USART1 configuration

	// USART1 configured as follow:
	//  - BaudRate = 115,200 baud
	//  - Word Length = 8 Bits
	//  - One Stop Bit
	//  - No parity
	//  - Hardware flow control disabled (RTS and CTS signals)
	//  - Receive and transmit enabled

	// UART1 Base Address   : 0x4001 3800

void init_uart1(void)
{
	RCC_APB2ENR  |= (  1 << USART1EN );
	GPIOA_CRH    |= (  4 << MODE10 | 11 << MODE9 );
//	When use External Clock
	USART1_BRR  = 39 << 4 | 1;	// 115,200 bps (HCLK 72Mhz) : DIV_Mantisa=39, DIV_Fraction=1
//	When use internal Clock
//	USART1_BRR  = 19 << 4 | 8;	// 115,200 bps (HCLK 36Mhz) : DIV_Mantisa=19, DIV_Fraction=8

	// Control Register1    : USART_CR1 ADD offset(0x0C) RST Value(0x0000 0000)
	USART1_CR1  = 0x200C;		// ADD Mask WakeUP,1 Start bit, 8 Data bit, Tx Enable, Rx Enable

	// Control Register2    : USART_CR2 ADD offset(0x10) RST Value(0x0000 0000)
	USART1_CR2  = 0x0;			// 1 Stop Bit

	// Control Register3    : USART_CR3 ADD offset(0x14) RST Value(0x0000 0000)
	USART1_CR3  = 0x0;			// Hardware flow control disabled

	USART1_CR1 |= 0x2000;       // SET ADD Mask WakeUP
}

void init_uart2(void)
{
	RCC_APB1ENR  |=  (  1 << USART2EN );
	GPIOA_CRL    &= ~( 15 << MODE3 );
	GPIOA_CRL    &= ~( 15 << MODE2 );
	GPIOA_CRL    |=  (  4 << MODE3 | 11 << MODE2 ); // 0100 1011

	USART2_BRR  = 19 << 4 | 8;	// 115,200 bps (PCLK1 36Mhz) : DIV_Mantisa=19, DIV_Fraction=8
	// Control Register1    : USART_CR1 ADD offset(0x0C) RST Value(0x0000 0000)
	USART2_CR1  = 0x200C;		// ADD Mask WakeUP,1 Start bit, 8 Data bit, Tx Enable, Rx Enable
	// Control Register2    : USART_CR2 ADD offset(0x10) RST Value(0x0000 0000)
	USART2_CR2  = 0x0;			// 1 Stop Bit
	// Control Register3    : USART_CR3 ADD offset(0x14) RST Value(0x0000 0000)
	USART2_CR3  = 0x0;			// Hardware flow control disabled

	USART2_CR1 |= 0x2000;       // SET ADD Mask WakeUP Why?????
}

#endif				// ----------------------------------------------------------------------
