#include "stm32f10x.h"

void USART2_TX_Char(uint8_t _data); // getter
uint16_t USART2_RX_Char(void); // setter
static void Delay(volatile unsigned long _time);

int main (void) {
    RCC_DeInit(); // RCC Register Clear

    RCC -> APB1ENR |= 0x00020000; // USART2EN new
    RCC -> APB2ENR |= 0x00000004; // IOPAEN

    GPIOA -> CRL = 0x00304B00; // TX_Pin_2, RX_Pin_3
    GPIOA -> CRH = 0x00400000; // Switch

    USART1 -> BRR |= 0x0045; // 115200, baud rate
    USART1 -> CR2 |= 0x0000;
    USART1 -> CR3 |= 0x0000;
    USART1 -> CR1 |= 0x200C;

    while(1){
        USART2_TX_Char('a');
        Delay(1000000);
    }
	return 0;
}

void USART2_TX_Char(uint8_t _data){
    USART2 -> DR = _data;
    while(!((USART2 -> SR & 0x0080) == 0x0080));
}

uint16_t USART2_RX_Char(void){
    while(!((USART2 -> SR & 0x0020) == 0x0020));
    return (USART2 -> DR & 0x01FF);
}

static void Delay(volatile unsigned long _time){
    for(; _time > 0; _time--);
}
