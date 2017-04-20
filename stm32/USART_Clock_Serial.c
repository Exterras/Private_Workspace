#include "stm32f10x.h"

uint32_t Delay_Count;
void SysTick_Handler(void);
void RCC_Init(void);
void USART2_TX_Char(uint8_t _data);
void USART2_TX_Str(uint8_t *_str);
uint16_t USART2_RX_Char(void);
void Delay(uint32_t _count);

int main (void) {
	RCC_Init();

    RCC -> APB1ENR |= 0x00020000; // USART2EN new
    RCC -> APB2ENR |= 0x00000004; // IOPAEN

    GPIOA -> CRL = 0x00304B00; // TX_Pin_2, RX_Pin_3
    GPIOA -> CRH = 0x00400000; // Switch

    USART1 -> BRR |= 0x0271; // 0x0271(36MHz), 0x0045(8MHz)
    USART1 -> CR2 |= 0x0000;
    USART1 -> CR3 |= 0x0000;
    USART1 -> CR1 |= 0x200C;

    while(1){
        USART2_TX_Str("Hello World!\n");
        Delay(1000);

        if(USART2 -> SR & 0x0020){
            if(USART2_RX_Char()== 'm'){
                USART2_TX_Str("I`m STM32\n");
            } else {
                USART2_TX_Str("?\n");
            }
        }
    }
	return 0;
}

void RCC_Init(void){
    RCC_DeInit();

    // Two Wait States
    FLASH -> ACR |= 0x00000002;

    // Bit19 CSSON = 1, Bit18 HSEBYP = 1
    RCC -> CR |= 0x000C0000;

    // Bit[20:18] PLLMUL = 0111, Bit16 PLLSRC = 1
    // Bit[15:14] ADCPRE, PCLK2 divided by 6 = 0b10, 12MHz
    // Bit[10:8] PPRE1, HCLK divided by 2 = 0b100, 36MHz
    RCC -> CFGR |= 0x001D8400;

    // Bit16 HSERDY = 1, Bit15 HSEON = 1
    RCC -> CR |= 0x00010000;
    while(!(RCC -> CR & 0x00020000));

    // Bit25 PLLRDY = 1, Bit24 PLLON = 1
    RCC -> CR |= 0x01000000;
    while(!(RCC -> CR & 0x02000000));

    // Bit[1:0] SW = 10, Bit[3:2] SWS = 10
    RCC -> CFGR |= 0x00000002;
    while(!(RCC -> CFGR & 0x00000008));

    RCC -> APB1ENR |= 0x00020000; // Bit17 USART2EN
    RCC -> APB2ENR |= 0x00000001; // Bit0 AFIOEN

    SysTick -> LOAD = 71999;
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000007;
}

void USART2_TX_Char(uint8_t _data){
    USART2 -> DR = _data;
    while(!(USART2 -> SR & 0x0080));
}

void USART2_TX_Str(uint8_t *_str){
    while(*_str)USART2_TX_Char(*str++);
}

uint16_t USART2_RX_Char(void){
    return (USART2 -> DR & 0x01FF);
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
