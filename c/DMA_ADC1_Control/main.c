#include <stdio.h>
#include <stdlib.h>

#include "stm32f10x.h"
// RCC, SysTick(Delay), USART2_Header
#include "stm32f10x_MyFunction.h" // user header files

#define ADC1_DR_ADDRESS ((uint32_t)0x4001244C)
_IO uint16_t ADC1_DMA1_Value;

uint8_t Buff_str[100];
uint16_t ADC_Calibration;

void ADC1_Init(void);
void ADC1_DMA1_Init(void);

int main(){
    uint16_t ADC_Data;
    float ADCF_Voltage;

    SysClock_init();
    SysTick_init();
    ADC1_DMA1_Init();
    ADC1_Init();
    USART2_Init();

    while(1){
        ADC_Data = ADC1_DMA1_Value + ADC_Calibration;
        ADC_Voltage = (float)ADC_data * (3.3 / (float)4095);
        sprintf(Buff_str, "DMA!_Data : %5d / ADC_Data : %5d / Voltage : %3.2f\r\n",
                ADC1_DMA1_value, ADC_Data, ADC_Voltage);
        USART2_TX_Str(Buff_Str);
        Delay(100);
    }
}

void ADC1_Init(void){
    // Bit9 ADC1EN, Bit4 IOPCEN
    RCC-> APB2ENR |= 0x00000210;

    // Bit[23:20] PC5(ADC_IN15) Analog Mode
    GPIOC -> CRL = 0x00000000;

    // Bit20 EXTTRIG, Bit[19:17] EXTSEL = 0b111, SWSTART, Bit1 CONT
    ADC1 -> CR2 |= 0x001E0002;
    // Bit[17:15] SMP15 = 0b101, 55.5cycle
    ADC1 -> SMPR1 |= 0x00028000;
    // Bit[23:20] L = 0b0000, 1 conversion
    ADC1 -> SQR1 |= 0x00000000;
    // Bit[4:0] SQ1 = 0b0E, ADC1_IN15
    ADC1 -> SQR3 |= 0x0000000F;

    // Bit0 ADON
    ADC1 -> CR2 |= 0x00000001;
    // Bit1 DMA enable
    ADC1 -> CR2 |= 0x00000100;

    // Bit3 RSTCAL
    ADC1 -> CR2 |= 0x00000008;
    // Bit2 A/D Calibration
    ADC1 -> CR2 |= 0x00000100;
    Delay(100);
    ADC_Calibration = ADC1 -> DRl

    // Bit22 SWSTART
    ADC1 -> CR2 |= 0x00400000;
}

void ADC1_DMA1_Init(void){
    // Bit1 DMA enable
    RCC -> AHBENR |= 0x00000001;

    // Prepheral address
    DMA1 Channel1 -> CPAR = ADC1 DR ADDRESS;


}
