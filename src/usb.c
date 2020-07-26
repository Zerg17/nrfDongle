#include "usb.h"
#include "usb_config.h"

#define USB_EPR ((volatile uint32_t *)USB_BASE)

#define EPR_RWBITS (USB_EPADDR_FIELD | USB_EP_KIND | USB_EP_TYPE_MASK)
#define EPR_RWCBITS (USB_EP_CTR_RX | USB_EP_CTR_TX)

static uint32_t set_stat_rx_bits(uint32_t epr, uint32_t bits){
    return ((epr & (EPR_RWBITS | USB_EPRX_STAT)) ^ bits) | EPR_RWCBITS;
}

static uint32_t set_stat_tx_bits(uint32_t epr, uint32_t bits){
    return ((epr & (EPR_RWBITS | USB_EPTX_STAT)) ^ bits) | EPR_RWCBITS;
}

uint8_t rx_bulk_buf[64];
uint8_t deviceAddress = 0;

void usbWrite(uint8_t epN, uint16_t *buf, uint16_t len){
    USB_TABLE[epN].COUNT_TX = len;
    uint16_t* epAdr = (uint16_t*)(USB_TABLE[epN].ADDR_TX + 0x40006000);
    for(uint16_t i=0; i<len/2; i++)
        epAdr[i]=buf[i];
    USB_EPR[epN] = set_stat_tx_bits(USB_EPR[epN], USB_EP_TX_VALID);
}

static inline void getDescriptor() {
    switch (setupPacket->wValueH) {
        case USB_DEVICE_DESC_TYPE:
            //xprintf("DEVICE\n");
            usbWrite(0, (uint16_t *)&USB_DEVICE_DESC, sizeof(USB_DEVICE_DESC));
            break;

        case USB_CFG_DESC_TYPE:
            //xprintf("CFG\n");
            usbWrite(0, (uint16_t *)&USBD_CDC_CFG_DESCRIPTOR, sizeof(USBD_CDC_CFG_DESCRIPTOR));
            break;

        case USB_STR_DESC_TYPE:
            //xprintf("STR\n");
            if (!setupPacket->wValueL)
                usbWrite(0, (uint16_t *)&USB_STRING_DESCRIPTOR, sizeof(USB_STRING_DESCRIPTOR));
            else {
                uint8_t buf[128];
                char c = 0xff;
                uint8_t i = 0;
                while (1) {
                    c = usb_strings[setupPacket->wValueL - 1][i];
                    if (!c) break;
                    buf[i + 1] = c;
                    i++;
                }
                buf[0] = (i * 2 + 2) | (0x03 << 8);
                usbWrite(0, (uint16_t *)buf, buf[0] & 0xFF);
            }
            break;

        case USB_DEVICE_QR_DESC_TYPE:
            USB_EPR[0] = set_stat_tx_bits(USB_EPR[0], USB_EP_TX_STALL);
            break;
    }
}

static inline void usbEPHandler(uint16_t epN) { 
    //xprintf("EP\n");
    if (USB_EPR[epN] & USB_EP_CTR_RX) {    
        //xprintf("RX\n");
        if (epN == 0) {
            switch (setupPacket->bRequest) {
                case USB_REQUEST_SET_ADDRESS:
                    USB_TABLE[0].COUNT_TX = 0;
                    USB_EPR[epN] = set_stat_tx_bits(USB_EPR[epN], USB_EP_TX_VALID);
                    deviceAddress = setupPacket->wValueL;
                    break;

                case USB_REQUEST_GET_DESCRIPTOR:
                    //xprintf("DESCRIPTOR\n");
                    getDescriptor();
                    break;

                case USB_REQUEST_SET_CONFIGURATION:
                    //xprintf("CONFIGURATION\n");
                    USB_TABLE[0].COUNT_TX = 0;
                    USB_EPR[epN] = set_stat_tx_bits(USB_EPR[epN], USB_EP_TX_VALID);
                    break;
            }
        }
        USB_EPR[epN]&=0x78f;
        USB_EPR[epN] = set_stat_rx_bits(USB_EPR[epN], USB_EP_RX_VALID);
    }

    if (USB_EPR[epN] & USB_EP_CTR_TX) {
        //xprintf("TX\n");
        if (deviceAddress) {
            USB->DADDR = USB_DADDR_EF | deviceAddress;
            deviceAddress = 0;
        }
        USB_EPR[epN]&=0x870f;
    }
}

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

static inline void usbReset(){
    //xprintf("RESET\n");
    USB_TABLE[0].ADDR_TX = 0x0040;
    USB_TABLE[0].COUNT_TX = 0x0000;
    USB_TABLE[0].ADDR_RX = 0x0080;
    USB_TABLE[0].COUNT_RX = BLSIZE | NUM_BLOCK_0;
    USB->EP0R = USB_EP_CONTROL | USB_EP_RX_VALID | USB_EP_TX_NAK;

    USB->DADDR = USB_DADDR_EF;
}

void USB_IRQHandler(void){
    if(USB->ISTR & USB_ISTR_RESET){
        usbReset();
        USB->ISTR &= USB_CLR_RESET;
    }
    if(USB->ISTR & USB_ISTR_CTR){
        usbEPHandler(USB->ISTR & USB_ISTR_EP_ID);
        USB->ISTR &= USB_CLR_CTR;
    }
}