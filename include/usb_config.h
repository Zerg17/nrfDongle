#pragma once

#include <stdint.h>

const uint8_t USB_DEVICE_DESC[] = {
    /*Device Descriptors*/
    0x12, /* bLength */
    0x01, /* bDescriptorType */
    0x00, /* bcdUSB */
    0x02, /* bcdUSB */
    0xFF, /* bDeviceClass */
    0x00, /* bDeviceSubClass */
    0x00, /* bDeviceProtocol */
    0x40, /* bMaxPacketSize0 */
    0xDA, /* idVendor */
    0X0B, /* idVendor */
    0x38, /* idProduct LO: */
    0x28, /* idProduct HI: */
    0x00, /* bcdDevice LO: */
    0x00, /* bcdDevice HI: */
    0x01, /* iManufacturer */
    0x02, /* iProduct */
    0x03, /* iSerialNumbert */
    0x01  /* bNumConfigurations */
};

const uint8_t USBD_CDC_CFG_DESCRIPTOR[] = {
    /*Configuration Descriptor*/
    0x09, /* bLength: Configuration Descriptor size */
    0x02, /* bDescriptorType: Configuration */
    0x20, /* wTotalLength LO: */
    0x00, /* wTotalLength HI: */
    0x01, /* bNumInterfaces: 1 interface */
    0x01, /* bConfigurationValue: Configuration value */
    0x00, /* iConfiguration: Index of string descriptor */
    0x80, /* bmAttributes - Bus powered */
    0x32, /* MaxPower 100 mA */

    /*Interface Descriptor */
    0x09, /* bLength: Interface Descriptor size */
    0x04, /* bDescriptorType: Interface */
    0x01, /* bInterfaceNumber: Number of Interface */
    0x00, /* bAlternateSetting: Alternate setting */
    0x02, /* bNumEndpoints: One endpoints used */
    0xff, /* bInterfaceClass: Communication Interface Class */
    0x00, /* bInterfaceSubClass: Abstract Control Model */
    0x00, /* bInterfaceProtocol: Common AT commands */
    0x00, /* iInterface: */

    /*Endpoint 1 Descriptor*/
    0x07, /* bLength: Endpoint Descriptor size */
    0x05, /* bDescriptorType: Endpoint */
    0x01, /* bEndpointAddress 1 */
    0x02, /* bmAttributes: Bulk */
    0x40, /* wMaxPacketSize LO: */
    0x00, /* wMaxPacketSize HI: */
    0x01, /* bInterval: */

    /*Endpoint 2 Descriptor*/
    0x07, /* bLength: Endpoint Descriptor size */
    0x05, /* bDescriptorType: Endpoint */
    0x82, /* bEndpointAddress 2 */
    0x02, /* bmAttributes: Bulk */
    0x40, /* wMaxPacketSize LO: */
    0x00, /* wMaxPacketSize HI: */
    0x01, /* bInterval: ignore for Bulk transfer */
};

const uint8_t USB_STRING_DESCRIPTOR[] = {
    0x04, /* bLength: Endpoint Descriptor size */
    0x03, /* bDescriptorType: Endpoint */
    0x09, /* wLANGID LO: */
    0x04, /* wLANGID HI: */
};

static const char *usb_strings[] = {
    "nrfNET",
    "nrfDongle",
    "0.0.1",
};