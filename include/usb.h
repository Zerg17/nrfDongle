#pragma once

#include "system.h"

#define  BLSIZE       (1 << 15)
#define  NUM_BLOCK_4  (1 << 14)
#define  NUM_BLOCK_3  (1 << 13)
#define  NUM_BLOCK_2  (1 << 12)
#define  NUM_BLOCK_1  (1 << 11)
#define  NUM_BLOCK_0  (1 << 10)
#define  COUNT_RX_msk (0x01FF << 0)

typedef struct {
    uint16_t ADDR_TX;
    uint16_t COUNT_TX;
    uint16_t ADDR_RX;
    uint16_t COUNT_RX;
} USB_TABLE_t;

#define USB_TABLE ((USB_TABLE_t *) USB_PMAADDR)

#define DISABLE  0x0
#define STALL    0x1
#define NAK      0x2
#define VALID    0x3

#define USB_REQUEST_GET_STATUS  0
#define USB_REQUEST_CLEAR_FEATURE 1
#define USB_REQUEST_SET_FEATURE 3
#define USB_REQUEST_SET_ADDRESS 5
#define USB_REQUEST_GET_DESCRIPTOR 6
#define USB_REQUEST_SET_DESCRIPTOR 7
#define USB_REQUEST_GET_CONFIGURATION 8
#define USB_REQUEST_SET_CONFIGURATION 9
#define USB_REQUEST_GET_INTERFACE 10
#define USB_REQUEST_SET_INTERFACE 11
#define USB_REQUEST_SYNC_FRAME 12

typedef struct {
    uint8_t Recipient : 5;
    uint8_t Type : 2;
    uint8_t Dir : 1;
    uint8_t bRequest;
    uint8_t wValueL;
    uint8_t wValueH;
    uint8_t wIndexL;
    uint8_t wIndexH;
    uint8_t wLength;
} setupPacket_t;

#define setupPacket ((setupPacket_t *) (USB_PMAADDR + 0x80))

/* USB Descriptor Types */
#define USB_DEVICE_DESC_TYPE 1
#define USB_CFG_DESC_TYPE 2
#define USB_STR_DESC_TYPE 3
#define USB_IFACE_DESC_TYPE 4
#define USB_EP_DESC_TYPE 5
#define USB_DEVICE_QR_DESC_TYPE 6
#define USB_OSPEED_CFG_DESC_TYPE 7
#define USB_IFACE_PWR_DESC_TYPE 8

void usbInit();