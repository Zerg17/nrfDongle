#pragma once

#include "stm32f0xx.h"
#include "xprintf.h"

#define BOAD 500000

#define LED_ON  GPIOA->BSRR = GPIO_BSRR_BR_4
#define LED_OFF GPIOA->BSRR = GPIO_BSRR_BS_4

void sysInit();