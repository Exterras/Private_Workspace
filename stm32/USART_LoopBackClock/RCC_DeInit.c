void RCC_DeInit(void){
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;

    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
    #ifndef STM32F10X_CL
    RCC->CFGR &= (uint32_t)0xF8FF0000;
    #else
    RCC->CFGR &= (uint32_t)0xF0FF0000;
    #endif /* STM32F10X_CL */

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
    RCC->CFGR &= (uint32_t)0xFF80FFFF;

    #ifdef STM32F10X_CL
    /* Reset PLL2ON and PLL3ON bits */
    RCC->CR &= (uint32_t)0xEBFFFFFF;

    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x00FF0000;

    /* Reset CFGR2 register */
    RCC->CFGR2 = 0x00000000;
    #elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;

    /* Reset CFGR2 register */
    RCC->CFGR2 = 0x00000000;
    #else
    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;
    #endif /* STM32F10X_CL */
}
