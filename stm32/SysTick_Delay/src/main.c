
#include "stm32f10x.h"

uint32_t  Delay_Count;

void SysTick_Handler(void);
void RCC_Config(void);
void Delay(uint32_t _count);

int main(void){
    RCC_Config();

    RCC -> APB1ENR |= 0x00000004; // USART2EN new
    GPIOA -> CRL |= 0x00300000; // IOPAEN

    while(1) {
        GPIOA -> ODR ^= GPIO_Pin_5;
        Delay(1000);
    }
}

void RCC_Config(void){
    RCC_DeInit();

    // Two Wait States
    FLASH -> ACR |= 0x00000002;

    // Bit19 CSSON = 1, Bit18 HSEBYP = 1
    RCC -> CR |= 0x000C0000;

    // Bit[20:18] PLLMUL = 0111, Bit16 PLLSRC = 1
    RCC -> CFGR |= 0x001D0000;

    // Bit16 HSERDY = 1, Bit15 HSEON = 1
    RCC -> CR |= 0x00010000;
    while(!(RCC -> CR & 0x00020000));

    // Bit25 PLLRDY = 1, Bit24 PLLON = 1
    RCC -> CR |= 0x01000000;
    while(!(RCC -> CR & 0x02000000));

    // Bit[1:0] SW = 10, Bit[3:2] SWS = 10
    RCC -> CFGR |= 0x00000002;
    while(!(RCC -> CFGR & 0x00000008));

    SysTick -> LOAD = 71999;
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000007;
}

void Delay(uint32_t _count){
    Delay_Count = _count;
    while(Delay_Count != 0);
}

void SysTick_Handler(void){
    if(Delay_Count){
        Delay_Count--;
    }
}

