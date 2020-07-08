#include "system.h"

void rccInit(){
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN | RCC_APB1ENR_TIM14EN;
}

void gpioInit(){
    // PA4  - DEBUG_LED     - GPIO_OUT
    // PA3  - DEBUG_RX      - USART2_RX
    // PA2  - DEBUG_TX      - USART2_TX

    SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA11_PA12_RMP;
    
    GPIOA->MODER |= GPIO_MODER_MODER4_1 | GPIO_MODER_MODER3_1 | GPIO_MODER_MODER2_1;
    GPIOA->AFR[0]|= 0x00041100;
}

void uartWrite(uint8_t d){
    while(!(USART2->ISR & USART_ISR_TXE));
    USART2->TDR=d;
}

void uartInit(){
    USART2->BRR = (F_CPU+BOAD/2)/BOAD;
    USART2->CR1 = USART_CR1_TE;
    USART2->CR1 |= USART_CR1_UE;
}

void tim14Init(){
    TIM14->CCMR1 = (0x07 << TIM_CCMR1_OC1M_Pos);
    TIM14->CCER = TIM_CCER_CC1E;
    TIM14->CR1 = TIM_CR1_ARPE;
    TIM14->PSC = 0;
    TIM14->ARR = 1000;
    TIM14->CR1 |= TIM_CR1_CEN;
}

void sysInit(){
    xdev_out(uartWrite);
    rccInit();
    gpioInit();
    tim14Init();
    SysTick_Config(F_CPU/100);
}

