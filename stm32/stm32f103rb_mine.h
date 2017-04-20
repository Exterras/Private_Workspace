#define ADDR_BASE      ((uint32_t)0x40000000
#define APB1_BASE       ADDR_BASE
#define APB2_BASE      (ADDR_BASE + 0x10000)
#define AHB_BASE       (ADDR_BASE + 0x20000)

#define GPIO_PIN_5     ((uint16_t)0x0020
#define GPIO_PIN_13     ((uint16_t)0x2000

typedef struct{
  _IO uint32_t CR;
  _IO uint32_t CFGR;
  _IO uint32_t CIR;
  _IO uint32_t APB2RSTR;
  _IO uint32_t APB1RSTR;
  _IO uint32_t AHBENR;
  _IO uint32_t APB2ENR;
  _IO uint32_t APB1ENR;
  _IO uint32_t BDCR;
  _IO uint32_t CSR;
} RCC_TypeDef;

#define RCC_BASE        (AHB_BASE + 0x1000)
#define RCC             ((RCC_TypeDef*)RCC_BASE)

typedef struct{
  _IO uint32_t CRL;
  _IO uint32_t CRH;
  _IO uint32_t IDR;
  _IO uint32_t ODR;
  _IO uint32_t BSRR;
  _IO uint32_t BRR;
  _IO uint32_t LCKR;
} GPIO_TypeDef;

#define GPIOA_BASE      (APB2_BASE + 0x800)
#define GPIOC_BASE      (APB2_BASE + 0x1000)

#define GPIOA           ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOC           ((GPIO_TypeDef*)GPIOC_BASE)