
 // 시스템 클럭 설정과 delay함수들의 동작속도 조정을 위한 상수.
 // ( 36: 내부클럭 36MHz, 72: 외부클럭 72MHz를 사용할 경우.)
 #define SYSCLK  36

 #include "stm32md_reg.h" // 각종 레지스터 번지를 Symbole 문자열로 define 해놓은 헤더파일.
 #include "stm32md_init.h" // 시스템클럭 설정과 플래쉬레이턴시 설정을 정의해놓은 헤더파일.
 #include "stm32md_delay.h" // 마이크로초, 밀리초 단위의 딜레이함수를 정의해놓은 헤더파일.

 #ifndef __NO_SYSTEM_INIT  // 원본과 달리 이 부분에서 문제가 생기므로 사이의 내용은 제거하였다.
 #endif

 // 점멸시켜야할 LD2가 연결된 GPIO 포트에 대한 설정 함수 정의.
 // ( LD2는 포트A의 5번 비트에 연결되어 있다.)
 void init_GPIO(void) {
     RCC_APB2ENR |=    1 << IOPAEN; // APB2 버스에 연결된 GPIO 포트A를 Enable.
     GPIOA_CRL   &= 0x00 << CNF5; // GPIO 포트A의 5번 비트를 push-pull 출력으로 설정
     GPIOA_CRL   |= 0x03 << MODE5; // GPIO 포트A의 5번 비트의 출력속도를 최대 50MHz로 설정
 }

 int main(void) {
     init_GPIO(); // 앞서 정의한 GPIO 설정 함수 호출
     while(1) {
         GPIOA_ODR ^= 1 << B05; // GPIO 포트A 출력데이터 레지스터의 5번 비트에 1을 XOR하여 다시 GPIO 포트A 출력데이터 레지스터에 저장 후, 1초간 대기.
         delay_ms(1000); // 점멸하는 속도 (ms)
     }
 }

 // 출처 : http://m.blog.naver.com/thumbdown/220278608381
