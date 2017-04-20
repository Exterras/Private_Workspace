#include "stm32f10x.h"

int main (void) {

    RCC_DeInit(); // RCC Register Clear

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

    RCC -> APB2ENR |= 0x00000004; // IOPAEN
    GPIOA -> CRL = 0x00300000;

    while(1){
        GPIOA -> ODR ^= GPIO_Pin_5; // GPIO_Pin_5 ((u16)0x0020)  /* Pin 5 selected */
    }
	return 0;
}
