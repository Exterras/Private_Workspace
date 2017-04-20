
#include "stm32f10x.h"
#include <stdio.h>

uint8_t Buff_Str[50];
uint32_t Delay_Count;

void SysTick_Handler(void);

void SysClock_Init(void);
void USART2_Init(void);
void PORT_Init(void);

void Delay(uint32_t _count);
void USART2_TX_Char(uint8_t _data);
void USART2_TX_Str(uint8_t *_str);

int main(void){

    uint16_t ADC_Data;
    uint16_t ADC_Calibration;
    float ADC_Voltage;

    SysClock_Init();
    PORT_Init();
    USART2_Init();

    ADC1 -> CR2 |= 0x001E0000; // Bit20 EXTTRIG, Bit[19:17] EXTSEL = 0b111, SWSTART
    ADC1 -> SMPR1 |= 0x00028000; // Bit[17:15] SMP15 = 0b101, 55.5 cycles
    ADC1 -> SQR1 |= 0x00000000; // Bit[23:20] L = 0b0000, 1 conversion
    ADC1 -> SQR3 |= 0x0000000F; // Bit[4:0] SQ1 = 0b0E, ADC1_IN15

    ADC1 -> CR2 |= 0x00000001; // Bit0 ADON
    ADC1 -> CR2 |= 0x00000008; // Bit3 RSTCAL
    ADC1 -> CR2 |= 0x00000004; // Bit2 CAL
    Delay(10);

    ADC_Calibration = ADC1 -> DR;

    while(1){
        ADC1 -> CR2 |= 0x00400000; // Bit22 SWSTART
        while(!(ADC1->SR & 0x00000010));
        ADC1 -> SR &= ~(0x00000010);
        ADC_Data = ADC1 -> DR + ADC_Calibration;
        ADC_Voltage = ADC_Data * (3.3 / 4095);

        sprintf(Buff_Str, "ADC : %4d / Voltage : %1.2f\n", ADC_Data, ADC_Calibration);
        USART2_TX_Str(Buff_Str);
        Delay(100);
    }

    void SysClock_Init(void){
        RCC_DeInit();

        // Two Wait States
        FLASH -> ACR |= 0x00000002;

        // Bit19 CSSON = 1, Bit18 HSEBYP = 1
        RCC -> CR |= 0x000C0000;

        // Bit[20:18] PLLMUL = 0111, Bit16 PLLSRC = 1
        // Bit[15:14] ADDPRE, PCLK2 divided by 6 = 0b10, 12MHz
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
        RCC -> APB2ENR |= 0x00000215; // Bit9 ADC1EN, Bit4 IOPCEN, Bit2 IOPAEN, Bit0 AFIOEN

        SysTick -> LOAD = 71999;
        SysTick -> VAL = 0;
        SysTick -> CTRL = 0x00000007;
    }

    void USART2_Init(void){
        USART2 -> BRR |= 0x0271; // Baud Rate = 57600
        USART2 -> CR2 |= 0x0000;
        USART2 -> CR3 |= 0x0000;
        USART2 -> CR1 |= 0x200C;
    }

    void PORT_Init(void){
        GPIOA -> CRL = 0x00004B00; // Bit[11:8] Tx_Pin_2(50MHz), Bit[15:12] Rx_Pin_3(Floating)
        GPIOC -> CRL = 0x00000000; // Bit[23:20] PC5(ADC_IN15) Analog Mode
    }

    void USART2_TX_Char(uint8_t _data){
        USART2 -> DR = _data;
        while(!(USART2->SR & 0x0080));
    }

    void USART2_TX_Str(uint8_t *_str){
        while(*_str)USART2_TX_Char(*_str++);
    }

    void Delay(uint32_t _count){
        Delay_Count = _count;
        while(Delay_Count != 0);
    }

    void SysTick_Handler(void){
        if(Delay_Count) Delay_Count++;
    }
}
