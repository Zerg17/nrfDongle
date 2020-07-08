#pragma once

#include "stm32f0xx.h"
#include "xprintf.h"

#define BOAD 500000

#define LED_ON  TIM14->CCR1 = 1000
#define LED_OFF TIM14->CCR1 = 0
#define LED(a)  TIM14->CCR1 = a

void sysInit();