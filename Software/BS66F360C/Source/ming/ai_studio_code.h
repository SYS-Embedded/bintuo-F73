#ifndef _TM1652_H_
#define _TM1652_H_

#include "MCU_Hardware.h" // 包含你的MCU寄存器定义，如holtek的头文件

// =================配置区域=================
// 定义显示缓冲区的长度 (TM1652最大支持6位显示)
#define TM1652_DIGIT_CNT    6 

// 亮度定义 (0-7共8级)
#define TM1652_BRIGHT_1_8   0
#define TM1652_BRIGHT_2_8   1
#define TM1652_BRIGHT_4_8   2 // 常用
#define TM1652_BRIGHT_8_8   7

// =================接口声明=================

/**
 * @brief 初始化IO口和内部变量
 */
void TM1652_Init(void);

/**
 * @brief 设置显存数据（非阻塞，写入缓存即返回）
 * @param addr: 数码管位置 0~(TM1652_DIGIT_CNT-1)
 * @param data: 7段码数据
 */
void TM1652_SetDigit(unsigned char addr, unsigned char data);

/**
 * @brief 设置亮度（非阻塞）
 * @param level: 0-7
 */
void TM1652_SetBrightness(unsigned char level);

/**
 * @brief 驱动主任务
 * @note  请在main函数的while(1)中调用，建议调用周期 < 1ms
 */
void TM1652_Task(void);

#endif