#include "stm32f10x.h"

void USART1_TX_Char(uint8_t _data); // getter
uint16_t USART1_RX_Char(void); // setter
static void Delay(volatile unsigned long _time);

int main (void) {
    RCC -> APB2ENR |= 0x00004000; // USART1EN new
    RCC -> APB2ENR |= 0x00000004; // IOPAEN

    GPIOA -> CRH = 0x000004B0; //TX_Pin_9, RX_Pin_10
    GPIOA -> CRL = 0x00300000; //LED

    USART1 -> BRR |= 0x0045; // 115200, baud rate
    USART1 -> CR2 |= 0x0000;
    USART1 -> CR3 |= 0x0000;
    USART1 -> CR1 |= 0x200C;

    while(1){
        USART1_TX_Char('m');
        Delay(1000000);

        if(USART1_RX_Char( == 'm')){
            GPIOA -> ODR ^= GPIO_Pin_5; // GPIO_Pin_5 ((u16)0x0020)  /* Pin 5 selected */
        }
    }
	return 0;
}

void USART1_TX_Char(uint8_t _data){
    USART1 -> DR = _data;
    while(!((USART1 -> SR & 0x0080) == 0x0080));
}

uint16_t USART1_RX_Char(void){
    while(!((USART1 -> SR & 0x0020) == 0x0020));
    return (USART1 -> DR & 0x01FF;
}

static void Delay(volatile unsigned long _time){
    for(; _time > 0; _time--);
}

