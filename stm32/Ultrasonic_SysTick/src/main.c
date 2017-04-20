#include <stdio.h>
#include <delay.h>

// ======= GPIO Port B set on "_start_stm32f10x.c" ====================================
//Port B Configuration Register high : GPIOB_CRH ADD offset(0x04) RST Value(0x4444 4444)
//
// *(volatile unsigned long *) 0x40010C04 = 0x33333333;
//
// PB_H 8bit : 0011 0011 0011 0011 0011 0011 0011 0011
// PB08-PB15 All Set Output(Push Pull/High Spped-50Mhz)
//
// It has to change PB11 as input!!! - HC-SR04 echo pin connected
//========================================================================================

#define PB_CRH *(volatile unsigned long *)0x40010C04
#define PB_ODR *(volatile unsigned long *)0x40010c0c
#define PB_IDR *(volatile unsigned long *)0x40010c08
#define STK_RELOAD *(volatile unsigned long *)0xe000e014
#define STK_CURVAL *(volatile unsigned long *)0xe000e018
#define STK_CTRL *(volatile unsigned long *)0xe000e010

volatile unsigned long t_cnt = 0;
// need time base interrupt every 1us.
// T_clk = 72Mhz, 72000000 count/s = 72000 count/ms = 72 count/us

void Init_SysTick(void)
{
    STK_RELOAD = 72-1;
    STK_CURVAL = 0;
    STK_CTRL = 6; // CLKSRC=1 INT=1 EN=0( It means STK does not start. It starts when EN=1 )
}

void SysTick_Handler(void)
{
    t_cnt++;
}

void trig_pulse(void) // output trigger pulse to HC-SR04 trig pin at least 10us
{
    PB_ODR |= (1<<10); // |= 0000 0100 0000 0000
    delay_us(11); // delay little over than 10us
    PB_ODR &= ~(1<<10); // &= 1111 1011 1111 1111
    delay_us(11); // delay little over than 10us
}

unsigned long echo_time(void)
{
    unsigned long echo;
    trig_pulse(); // give trig pulse to u_sonic sensor
    while((PB_IDR & 0x00000800) != 0x0000800); // wait echo pin status turns HIGH
// != 0000 1000 0000 0000 (wait until bit11=1 )
    STK_CTRL |= (1<<0); // start systick timer
    while((PB_IDR & 0x00000800) == 0x0000800); // wait echo pin status turns LOW
// == 0000 1000 0000 0000 (wait until bit11=0 )
    echo = t_cnt;
    STK_CTRL &= ~(1<<0); // stop systick timer
    t_cnt = 0; // clear t_cnt
    return echo;
}

int main(void)
{
    unsigned long echo = 0;
    Init_SysTick();
// Except PB10(input), PB08-PB15 All Set Output(Push Pull/High Spped-50Mhz)
    PB_CRH = 0x33338333; // PB_H 8bit : 0011 0011 0011 0011 1000 0011 0011 0011
    printf("\n\n HC-SR04 Test... \n\n");
    while(1)
    {
       echo = echo_time();
       printf("distance = %5d.%d mm\n",17*echo/100,(17*echo)%100);
// echo = time(us) (It is time for ultra sonic wave go and back)
// Velocity = Distance/Time, 340m/s = 2×Distance/echo(us), 340m/1,000,000us = 2×Distance/echo
// 340,000mm/1000,000us = 2×Distance/echo , 34mm/100 = 2×Distance/echo, 17mm/100us = Distance/echo
// Distance = 17 × echo / 100 mm
       delay_ms(500);
    }
}
