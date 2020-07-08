#include "system.h"

int main(void){
    sysInit();
    while(1){
       LED_ON;
       for(volatile uint32_t i=0; i<1000000; i++);
       LED_OFF;
       for(volatile uint32_t i=0; i<100000; i++);
    }
}
