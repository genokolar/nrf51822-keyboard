#ifndef __UART_DRIVER__
#define __UART_DRIVER__

#include <stdint.h>
#include <stdbool.h>

#ifdef UART_SUPPORT

#define UART_BAUDRATE NRF_UART_BAUDRATE_57600

/**
 * @brief
 * @note 包格式为 Len TYPE DATA[Len-1]
 *       Len: 除Len字节外的包长度
 *       Type: 包类型
 *       Data[]: 实际数据，长度为len-1
 * 
 */

typedef enum {
    // uart rx
    PACKET_PING = 0x00,
    PACKET_LED,
    PACKET_CHARGING,
    PACKET_KEYMAP,
    PACKET_USB_STATUS,
    
    // uart tx
    PACKET_KEYBOARD = 0x80,
    PACKET_SYSTEM,
    PACKET_COMSUMER,
    PACKET_GET_STATE,
    
    // uart other
    PACKET_FAIL = 0xc0,
    PACKET_ACK,
} packet_type;

typedef enum {
    UART_MODE_IDLE,         // USB 未连接
    UART_MODE_CHARGING,     // USB 已连接但尚未连接到主机
    UART_MODE_USB,          // USB 主机已连接
    UART_MODE_BLE_OVERRIDE  // USB 主机已连接但强制使用BLE模式通讯
} uart_mode;
extern uart_mode uart_current_mode;

void uart_init(void);
void uart_sleep_prepare(void);
void uart_send_packet(packet_type type, uint8_t * data, uint8_t len);
void uart_set_evt_handler(void (*evt)(bool));
bool uart_is_using_usb(void);
void uart_switch_mode(void);


#endif

#endif