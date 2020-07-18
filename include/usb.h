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

void usbInit();