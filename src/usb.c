#include "usb.h"

uint8_t rx_bulk_buf[64];

void usbInit(){
    USB->BCDR |= USB_BCDR_DPPU;
    USB->CNTR |= USB_CNTR_CTRM | USB_CNTR_RESETM;
    USB->CNTR &= ~USB_CNTR_PDWN;
    for(volatile uint8_t i = 0; i<255; i++);
    USB->BTABLE = 0;
    USB->DADDR = 0;
    USB->ISTR = 0;
    USB->CNTR &= ~USB_CNTR_FRES;
    NVIC_EnableIRQ(USB_IRQn);
}

static inline usbReset(){
    xprintf("RESET\n");
    
    USB_TABLE[0].ADDR_TX = 0x0040;
    USB_TABLE[0].COUNT_TX = 0x0000;
    USB_TABLE[0].ADDR_RX = 0x0080;
    USB_TABLE[0].COUNT_RX = BLSIZE | NUM_BLOCK_0;
    USB->EP0R = USB_EP_CONTROL | USB_EP_RX_VALID | USB_EP_TX_NAK;

    USB->DADDR |= USB_DADDR_EF;

    xprintf("%04X\n", *(uint16_t*)(0x40006000));
    xprintf("%04X\n", *(uint16_t*)(0x40006002));
    xprintf("%04X\n", *(uint16_t*)(0x40006004));
    xprintf("%04X\n", *(uint16_t*)(0x40006006));
}

void USB_IRQHandler(void){
    xprintf("IRQ\n");
    if(USB->ISTR & USB_ISTR_RESET){
        USB->ISTR &= USB_CLR_RESET;
        usbReset();
    }
    if(USB->ISTR & USB_ISTR_CTR){
        xprintf("CTR\n");
        USB->ISTR &= USB_CLR_CTR;
        LED_ON;
    }
}