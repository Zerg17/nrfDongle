#include "system.h"

void rccInit(){
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
}

void gpioInit(){
    // PA4  - DEBUG_LED     - GPIO_OUT
    // PA3  - DEBUG_RX      - USART2_RX
    // PA2  - DEBUG_TX      - USART2_TX
    
    GPIOA->MODER |= GPIO_MODER_MODER4_0 | GPIO_MODER_MODER3_1 | GPIO_MODER_MODER2_1;
    GPIOA->AFR[0]|= 0x00001100;
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

void sysInit(){
    xdev_out(uartWrite);
    rccInit();
    gpioInit();
}

