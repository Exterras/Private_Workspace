
#include "stm32f10x.h"

uint32_t  Delay_Count;
uint8_t SW_Flag;

void SysTick_Handler(void); // ??
void EXTI15_10_IRQHandler(void);
void Delay(uint32_t _count);

void RCC_Init(void);
void PORT_Init(void);

int main(void){

    RCC_Init();
    PORT_Init();

    EXTI -> IMR |=0x00002000; // Bit13 MR13
    EXTI -> RTSR |=0x00000000; // Rising Trigger Disable
    EXTI -> FTSR |=0x00002000; // Falling Trigger Enable

    NVIC -> ISER[1] |= 0x00000100; // EXTI15_10_IRQHandler

    while(1) {
        if(SW_Flag){
            GPIOA -> ODA ^= GPIO_Pin_5;
            SW_Flag = 0;
        }
    }
}

void RCC_Init(void){
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

    SysTick -> LOAD = 71999; // 1ms
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000007;
}

void PORT_Init(void){
    RCC -> APB2ENR |= 0x00000005; // Bit2 IOPAEN, Bit0 AFIOEN

    GPIOA -> CRL = 0x00300000; // PA5, LED, Output(50MHz)
    GPIOA -> CRH = 0x00400000; // PC13, SW, Floating

    AFIO -> EXTICR[3] = 0x00000020; // EXTI13, PC13 = 0010
}

void Delay(uint32_t _count){
    Delay_Count = _count;
    while(Delay_Count != 0);
}

// Handler Function
void EXTI15_10_IRQHandler(void){
    if(EXTI -> PR & 0x00002000){
        SW_Flag = 1;
    }
    EXTI -> PR |= 0x00002000; // Write "ISR Clear Bit"
}
