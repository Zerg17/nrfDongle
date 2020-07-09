#include "usb.h"
#include "system.h"

void usbInit(){
    NVIC_EnableIRQ(USB_IRQn);
    USB->CNTR |= USB_CNTR_CTRM | USB_CNTR_RESETM;
    USB->CNTR &= ~USB_CNTR_PDWN;
    for(volatile uint8_t i = 0; i<255; i++);
    USB->CNTR &= ~USB_CNTR_FRES;
}

void USB_IRQHandler(void){
    xprintf("USB\n");
}