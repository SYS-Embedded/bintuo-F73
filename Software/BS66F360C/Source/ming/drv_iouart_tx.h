/**
 * @file drv_iouart.h
 * @brief IO模拟UART发送模块头文件
 */

#ifndef DRV_IOUART_H
#define DRV_IOUART_H

#include <stdint.h>
#include "hal_board.h"

/* 配置参数 */
#define IOUART_BUFFER_SIZE    24      /* 发送缓冲区大小 */
#define IOUART_BAUDRATE       9600    /* 波特�?*/

/* 状态定�?*/
typedef enum {
    IOUART_IDLE = 0,          /* 空闲状�?*/
    IOUART_BUSY = 1           /* 忙状�?*/
} IOUART_StatusTypeDef;

typedef enum {
    TX_STATE_IDLE = 0,        /* 空闲状�?*/
    TX_STATE_START_BIT,       /* 发送起始位 */
    TX_STATE_DATA_BITS,       /* 发送数据位 */
    TX_STATE_STOP_BIT         /* 发送停止位 */
} IOUART_TxStateTypeDef;

/**
 * @brief 初始化IO模拟UART
 * @param None
 * @return None
 */
void IOUART_Init(void);

/**
 * @brief 发送单个字�?
 * @param data 要发送的数据
 * @return 1:成功加入缓冲�?0:缓冲区已�?
 */
uint8_t IOUART_SendByte(uint8_t data);

/**
 * @brief 发送字符串
 * @param str 要发送的字符�?
 * @return 成功加入缓冲区的字节�?
 */
uint16_t IOUART_SendString(const char *str);

/**
 * @brief 发送数据缓冲区
 * @param data 数据缓冲�?
 * @param len 数据长度
 * @return 成功加入缓冲区的字节�?
 */
uint16_t IOUART_SendBuffer(const uint8_t *data, uint16_t len);

/**
 * @brief 获取UART发送状�?
 * @param None
 * @return IOUART_StatusTypeDef
 */
IOUART_StatusTypeDef IOUART_GetStatus(void);

/**
 * @brief 定时器中断处理函数，需要在定时器中断中调用
 * @param None
 * @return None
 */
void IOUART_TimerIRQHandler(void);

/**
 * @brief 硬件初始化函数，需要根据具体MCU实现
 * @param None
 * @return None
 */
void IOUART_HardwareInit(void);

/**
 * @brief 设置TX引脚电平，需要根据具体MCU实现
 * @param level 0:低电�?1:高电�?
 * @return None
 */
void IOUART_SetTxPin(uint8_t level);

void iouart_startscan(void);

extern uint8_t tx_busy;                    /* 发送忙标志 */
extern IOUART_TxStateTypeDef tx_state;  /* 发送状态机状�?*/
extern uint8_t tx_data;                    /* 当前发送的字节 */
extern uint8_t tx_bit_index;               /* 当前发送的位索�?*/


#define IOUART_TIMER_IRQ_HANDLER()          \
    do {                                    \
        /* 如果不在发送状态，直接返回 */     \
        if (!tx_busy) {                     \
            break;                          \
        }                                   \
                                            \
        /* 根据状态机状态处�?*/             \
        switch (tx_state)                   \
        {                                   \
            case TX_STATE_IDLE:             \
                /* 检查缓冲区是否有数�?*/   \
                tx_busy = 0;            \
                break;                      \
                                            \
            case TX_STATE_START_BIT:        \
                /* 发送起始位（低电平�?*/   \
                HAL_GPIO_TX_SET(0);         \
                tx_bit_index = 0;           \
                tx_state = TX_STATE_DATA_BITS;\
                break;                      \
                                            \
            case TX_STATE_DATA_BITS:        \
                /* 发送数据位（LSB优先�?*/  \
                HAL_GPIO_TX_SET((tx_data >> tx_bit_index) & 0x01); \
                tx_bit_index++;             \
                                            \
                /* 检查是否发送完8位数�?*/  \
                if (tx_bit_index >= 8) {    \
                    tx_state = TX_STATE_STOP_BIT;\
                }                           \
                break;                      \
                                            \
            case TX_STATE_STOP_BIT:         \
                /* 发送停止位（高电平�?*/   \
                HAL_GPIO_TX_SET(1);         \
                                            \
                /* 检查缓冲区是否有更多数�?*/\
                tx_state = TX_STATE_IDLE;\
                break;                      \
                                            \
            default:                        \
                tx_state = TX_STATE_IDLE;   \
                break;                      \
        }                                   \
    } while(0)


#endif /* DRV_IOUART_H */