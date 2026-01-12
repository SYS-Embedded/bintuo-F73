/**
 * @file drv_iouart.c
 * @brief IO模拟UART发送模块实�?
 */


#include "drv_iouart_tx.h"

/* 私有定义 */
#define IOUART_BIT_DURATION   (1000000 / IOUART_BAUDRATE)  /* 单位：us */

/* 发送状态机状�?*/


/* 私有变量 */
static uint8_t tx_buffer[IOUART_BUFFER_SIZE];  /* 发送缓冲区 */
static uint16_t tx_head = 0;                   /* 缓冲区头指针 */
static uint16_t tx_tail = 0;                   /* 缓冲区尾指针 */

uint8_t tx_busy = 0;                    /* 发送忙标志 */
IOUART_TxStateTypeDef tx_state = TX_STATE_IDLE;  /* 发送状态机状�?*/
uint8_t tx_data = 0;                    /* 当前发送的字节 */
uint8_t tx_bit_index = 0;               /* 当前发送的位索�?*/

/**
 * @brief 初始化IO模拟UART
 */
void IOUART_Init(void)
{
    /* 初始化缓冲区 */
    tx_head = 0;
    tx_tail = 0;
    tx_busy = 0;
    tx_state = TX_STATE_IDLE;
    
    /* 初始化硬�?*/
    //hal_iouart_TxTimerInit();
    
    /* 默认TX引脚为高电平（空闲状态） */
    //hal_iouart_SetTxPin();
    HAL_GPIO_TX_DIR(0);
    
}

/**
 * @brief 检查缓冲区是否为空
 * @return 1:�?0:非空
 */
static uint8_t IOUART_IsBufferEmpty(void)
{
    return (tx_head == tx_tail);
}

/**
 * @brief 检查缓冲区是否已满
 * @return 1:�?0:非满
 */
static uint8_t IOUART_IsBufferFull(void)
{
    return (((tx_head + 1) % IOUART_BUFFER_SIZE) == tx_tail);
}

/**
 * @brief 从缓冲区获取一个字�?
 * @param data 数据存储指针
 * @return 1:成功 0:缓冲区为�?
 */
static uint8_t IOUART_GetByteFromBuffer(uint8_t *data)
{
    if (IOUART_IsBufferEmpty()) {
        return 0;
    }
    
    *data = tx_buffer[tx_tail];
    tx_tail = (tx_tail + 1) % IOUART_BUFFER_SIZE;
    
    return 1;
}

/**
 * @brief 发送单个字�?
 * @param data 要发送的数据
 * @return 1:成功加入缓冲�?0:缓冲区已�?
 */
uint8_t IOUART_SendByte(uint8_t data)
{
    /* 检查缓冲区是否已满 */
    if (IOUART_IsBufferFull()) {
        return 0;
    }
    
    /* 将数据加入缓冲区 */
    tx_buffer[tx_head] = data;
    tx_head = (tx_head + 1) % IOUART_BUFFER_SIZE;
    
    /* 如果当前空闲，启动发�?*/
    #if 0
    if (!tx_busy) 
    {
        tx_busy = 1;
        tx_state = TX_STATE_START_BIT;
    }
    #endif
    
    return 1;
}

void iouart_startscan(void)
{
    if (!tx_busy) 
    {
        if(IOUART_GetByteFromBuffer(&tx_data))
        {
            tx_busy = 1;
            tx_state = TX_STATE_START_BIT;
        }
    }
}



/**
 * @brief 发送字符串
 * @param str 要发送的字符�?
 * @return 成功加入缓冲区的字节�?
 */
uint16_t IOUART_SendString(const char *str)
{
    uint16_t count = 0;
    
    while (*str) {
        if (IOUART_SendByte(*str)) {
            count++;
            str++;
        } else {
            break;  /* 缓冲区已�?*/
        }
    }
    
    return count;
}

/**
 * @brief 发送数据缓冲区
 * @param data 数据缓冲�?
 * @param len 数据长度
 * @return 成功加入缓冲区的字节�?
 */
uint16_t IOUART_SendBuffer(const uint8_t *data, uint16_t len)
{
    uint16_t count = 0;
    uint16_t i;
    
    for (i = 0; i < len; i++) {
        if (IOUART_SendByte(data[i])) {
            count++;
        } else {
            break;  /* 缓冲区已�?*/
        }
    }
    
    return count;
}

/**
 * @brief 获取UART发送状�?
 * @return IOUART_StatusTypeDef
 */
IOUART_StatusTypeDef IOUART_GetStatus(void)
{
    return tx_busy ? IOUART_BUSY : IOUART_IDLE;
}

/**
 * @brief 定时器中断处理函数，需要在定时器中断中调用
 */
void IOUART_TimerIRQHandler(void)
{
    /* 如果不在发送状态，直接返回 */
    if (!tx_busy) {
        return;
    }
    
    /* 根据状态机状态处�?*/
    switch (tx_state) 
    {
        case TX_STATE_IDLE:
            /* 检查缓冲区是否有数�?*/
            #if 0
            if (IOUART_GetByteFromBuffer(&tx_data)) {
                tx_state = TX_STATE_START_BIT;
            } else {
                tx_busy = 0;  /* 无数据发送，标记为空�?*/
            }
            #else
                tx_busy = 0;  /* 无数据发送，标记为空�?*/
            #endif
            break;
            
        case TX_STATE_START_BIT:
            /* 发送起始位（低电平�?*/
            HAL_GPIO_TX_SET(0);
            tx_bit_index = 0;
            tx_state = TX_STATE_DATA_BITS;
            break;
            
        case TX_STATE_DATA_BITS:
            /* 发送数据位（LSB优先�?*/
            HAL_GPIO_TX_SET((tx_data >> tx_bit_index) & 0x01);
            tx_bit_index++;
            
            /* 检查是否发送完8位数�?*/
            if (tx_bit_index >= 8) {
                tx_state = TX_STATE_STOP_BIT;
            }
            break;
            
        case TX_STATE_STOP_BIT:
            /* 发送停止位（高电平�?*/
            HAL_GPIO_TX_SET(1);
            
            /* 检查缓冲区是否有更多数�?*/
            #if 0
            if (IOUART_GetByteFromBuffer(&tx_data)) {
                tx_state = TX_STATE_START_BIT;
            } else {
                tx_state = TX_STATE_IDLE;
                tx_busy = 0;  /* 无数据发送，标记为空�?*/
            }
            #else
                tx_state = TX_STATE_IDLE;
            #endif
            break;
            
        default:
            tx_state = TX_STATE_IDLE;
            break;
    }
}

#if 0
/* 以下是需要根据具体MCU实现的硬件相关函�?*/

/**
 * @brief 硬件初始化函数，需要根据具体MCU实现
 * 
 * 示例实现（需要根据实际MCU修改�?
 * 1. 配置TX引脚为输出模�?
 * 2. 配置定时器，周期为波特率对应的位时间
 */
__attribute__((weak)) void hal_iouart_TxTimerInit(void)
{
    /* 
     * 此处应实�?
     * 1. 配置TX引脚为输出模�?
     * 2. 配置定时器，周期为IOUART_BIT_DURATION微秒
     * 3. 启动定时�?
     */
}

/**
 * @brief 设置TX引脚电平，需要根据具体MCU实现
 * @param level 0:低电�?1:高电�?
 */
__attribute__((weak)) void hal_iouart_SetTxPin(uint8_t level)
{
    /*
     * 此处应实�?
     * 根据level参数设置TX引脚的电�?
     */
     HAL_GPIO_TX_DIR(0);
     HAL_GPIO_TX_SET(0);
}
#endif