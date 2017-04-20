// =============================================================
//
//	STM32F10x MD Devices Register Define : stm32md_reg.h
//
//								2014.  1.  5.	by GroundZero
//
// =============================================================

#pragma once
//#ifndef	_STM32MD_REG_H_
//#define	_STM32MD_REG_H_
//#endif

//-------------------------- RCC_CR -----------------------------

#define PLLRDY		25
#define PLLON		24
#define HSERDY		17
#define HSEON		16
#define HSIRDY		 1
#define HSION		 0

//-------------------------- RCC_CFGR ---------------------------

#define USBPRE		22
#define PLLMUL		18	// [21:18] 4bit
#define PLLXTPRE	17
#define PLLSRC		16
#define ADCPRE		14	// [15:14] 2bit
#define PPRE2		11	// [13:11] 3bit
#define PPRE1		 8	// [10: 8] 3bit
#define HPRE		 4	// [ 7: 4] 4bit
#define SWS			 2	// [ 3: 2] 2bit
#define SW			 0	// [ 1: 0] 2bit

//-------------------------- RCC_AHBENR -------------------------

#define CRCEN		 6
#define	DMA2EN		 1
#define	DMA1EN		 0

//-------------------------- RCC_APB2ENR ------------------------

#define	USART1EN	14
#define	SPI1EN		12
#define	TIM1EN		11
#define	ADC2EN		10
#define	ADC1EN		 9
#define IOPCEN		 4
#define	IOPBEN		 3
#define	IOPAEN		 2
#define	AFIOEN		 0

//-------------------------- RCC_APB1ENR ------------------------

#define	DACEN		29
#define	CANEN		25
#define	USBEN		23
#define	I2C2EN		22
#define	I2C1EN		21
#define	USART3EN	18
#define	USART2EN	17
#define	SPI2EN		14
#define	TIM4EN		 2
#define	TIM3EN		 1
#define	TIM2EN		 0

//-------------------------- FLASH_ACR ---------------------------

#define	PRFTBE		 4
#define	LATENCY		 0	// [ 2: 0]

//-------------------------- GPIOx_CRL --------------------------

#define	CNF7		30
#define	MODE7		28
#define	CNF6		26
#define	MODE6		24
#define	CNF5		22
#define	MODE5		20
#define	CNF4		18
#define	MODE4		16
#define	CNF3		14
#define	MODE3		12
#define	CNF2		10
#define	MODE2		 8
#define	CNF1		 6
#define	MODE1		 4
#define	CNF0		 2
#define	MODE0		 0

//-------------------------- GPIOx_CRH --------------------------

#define	CNF15		30
#define	MODE15		28
#define	CNF14		26
#define	MODE14		24
#define	CNF13		22
#define	MODE13		20
#define	CNF12		18
#define	MODE12		16
#define	CNF11		14
#define	MODE11		12
#define	CNF10		10
#define	MODE10		 8
#define	CNF9		 6
#define	MODE9		 4
#define	CNF8		 2
#define	MODE8		 0

//-------------------------- GPIOx_IODR -------------------------

#define	B15			15
#define	B14			14
#define	B13			13
#define	B12			12
#define	B11			11
#define	B10			10
#define	B09			 9
#define	B08			 8
#define	B07			 7
#define	B06			 6
#define	B05			 5
#define	B04			 4
#define	B03			 3
#define	B02			 2
#define	B01			 1
#define	B00			 0

//-------------------------- AFIO_MAPR -------------------------

#define	SWJ_CFG		24		// [26:24]
#define	TIM4_REMAP	12
#define	TIM3_REMAP	10		// [10:11]
#define	TIM2_REMAP	 8		// [ 9: 8]
#define	TIM1_REMAP	 6		// [ 7: 6]
#define	USART3_REMAP 4		// [ 5: 4]
#define	USART2_REMAP 3
#define	USART1_REMAP 2
#define	I2C1_REMAP	 1
#define	SPI1_REMAP	 0

//-------------------------------------------------------------


// SYSTICK	( System Tick Timer : Cortex-M Core Device )
#define	STK_RELOAD	*(volatile unsigned long *) 0xe000e014
#define	STK_CURVAL	*(volatile unsigned long *) 0xe000e018
#define	STK_CTRL	*(volatile unsigned long *) 0xe000e010

// RCC		(Reset and Clock Control)
#define	RCC_CR		*(volatile unsigned long *)	0x40021000
#define	RCC_CFGR	*(volatile unsigned long *) 0x40021004
#define	RCC_AHBENR	*(volatile unsigned long *) 0x40021014
#define	RCC_APB2ENR	*(volatile unsigned long *) 0x40021018
#define	RCC_APB1ENR	*(volatile unsigned long *) 0x4002101c

// Flash memory latency
#define	FLASH_ACR	*(volatile unsigned long *) 0x40022000

// GPIO		(General Pulpose I/Os)
#define	GPIOA_CRL	*(volatile unsigned long *) 0x40010800
#define	GPIOA_CRH	*(volatile unsigned long *) 0x40010804
#define	GPIOA_IDR	*(volatile unsigned long *) 0x40010808
#define	GPIOA_ODR	*(volatile unsigned long *) 0x4001080c
#define	GPIOB_CRL	*(volatile unsigned long *) 0x40010c00
#define	GPIOB_CRH	*(volatile unsigned long *) 0x40010c04
#define	GPIOB_IDR	*(volatile unsigned long *) 0x40010c08
#define	GPIOB_ODR	*(volatile unsigned long *) 0x40010c0c
#define	GPIOC_CRL	*(volatile unsigned long *) 0x40011000
#define	GPIOC_CRH	*(volatile unsigned long *) 0x40011004
#define	GPIOC_IDR	*(volatile unsigned long *) 0x40011008
#define	GPIOC_ODR	*(volatile unsigned long *) 0x4001100c

// AFIO		(Alternate-Function I/Os)
#define	AFIO_MAPR	*(volatile unsigned long *) 0x40010004	// JTAG/SWD Remap 
															// bit26,25,24 = 1,0,0 : all free
// I2C1		(Inter-integrated Circuit 1)
#define	I2C1_CR1	*(volatile unsigned long *) 0x40005400
#define I2C1_CR2	*(volatile unsigned long *) 0x40005404
#define I2C1_OAR1	*(volatile unsigned long *) 0x40005408
#define I2C1_OAR2	*(volatile unsigned long *) 0x4000540c
#define I2C1_DR		*(volatile unsigned long *) 0x40005410
#define I2C1_SR1	*(volatile unsigned long *) 0x40005414
#define I2C1_SR2	*(volatile unsigned long *) 0x40005418
#define I2C1_CCR	*(volatile unsigned long *) 0x4000541c
#define I2C1_TRISE	*(volatile unsigned long *) 0x40005420

// I2C2		(Inter-integrated Circuit 2)
#define	I2C2_CR1	*(volatile unsigned long *) 0x40005800
#define I2C2_CR2	*(volatile unsigned long *) 0x40005804
#define I2C2_OAR1	*(volatile unsigned long *) 0x40005808
#define I2C2_OAR2	*(volatile unsigned long *) 0x4000580c
#define I2C2_DR		*(volatile unsigned long *) 0x40005810
#define I2C2_SR1	*(volatile unsigned long *) 0x40005814
#define I2C2_SR2	*(volatile unsigned long *) 0x40005818
#define I2C2_CCR	*(volatile unsigned long *) 0x4000581c
#define I2C2_TRISE	*(volatile unsigned long *) 0x40005820

// USART1	(Universial Syncronous Asyncronous Receiver Transmitter 1)
#define	USART1_SR	*(volatile unsigned long *) 0x40013800
#define	USART1_DR	*(volatile unsigned long *) 0x40013804
#define	USART1_BRR	*(volatile unsigned long *) 0x40013808
#define	USART1_CR1	*(volatile unsigned long *) 0x4001380C
#define	USART1_CR2	*(volatile unsigned long *) 0x40013810
#define	USART1_CR3	*(volatile unsigned long *) 0x40013814

// USART2	(Universial Syncronous Asyncronous Receiver Transmitter 2)
#define	USART2_SR	*(volatile unsigned long *) 0x40004400
#define	USART2_DR	*(volatile unsigned long *) 0x40004404
#define	USART2_BRR	*(volatile unsigned long *) 0x40004408
#define	USART2_CR1	*(volatile unsigned long *) 0x4000440C
#define	USART2_CR2	*(volatile unsigned long *) 0x40004410
#define	USART2_CR3	*(volatile unsigned long *) 0x40004414


// ADC1
#define	ADC1_SR		*(volatile unsigned long *) 0x40012400
#define	ADC1_CR1	*(volatile unsigned long *) 0x40012404
#define	ADC1_CR2	*(volatile unsigned long *) 0x40012408
#define	ADC1_SMPR1	*(volatile unsigned long *) 0x4001240c
#define	ADC1_SMPR2	*(volatile unsigned long *) 0x40012410
#define	ADC1_SQR1	*(volatile unsigned long *) 0x4001242c
#define	ADC1_SQR2	*(volatile unsigned long *) 0x40012430
#define	ADC1_SQR3	*(volatile unsigned long *) 0x40012434
#define	ADC1_DR		*(volatile unsigned long *) 0x4001244c


// TIM1


// TIM2


// TIM3


// TIM4









