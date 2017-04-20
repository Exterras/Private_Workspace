#include "stm32f103rb_mine.h"

int main(void){
  RCC->APB2NER |= 0x14;
  
  GPIOA -> CRL = 0x0;
  GPIOA -> CRL |= 0x100000;
  GPIOA -> CRH = 0x0;
  GPIOA -> CRH |= 0x400000;
  
  while(){
    if((GPIOC -> IDR & GPIO_PIN_13) == 0x0){
      GPIOA -> ODR |= GPIO_PIN_5;
    } else {
      GPIOA -> ODR &= ~(GPIO_PIN_5);
    }
  }
}