/**
 * @file    drv_tm1652.h
 * @brief   TM1652 LED Driver (Single-wire UART)
 * @author  Senior Embedded Engineer
 * @date    2026-01-03
 * @version 1.1
 * @note    Target: Holtek 8-bit RISC MCU (Limited RAM/Stack)
 */

#ifndef _DRV_TM1652_H_
#define _DRV_TM1652_H_

#include "MCU_Hardware.h" // Include your MCU specific register definitions

// ================= Configurations =================

// Max supported digits (TM1652 supports up to 6 Grids)
#define TM1652_MAX_DIGITS   6 

// Brightness Levels (Pulse Width Control)
// Reference Datasheet Page 6
#define TM1652_BRIGHT_1_16  0  // 1/16 duty
#define TM1652_BRIGHT_2_16  1
#define TM1652_BRIGHT_4_16  2
#define TM1652_BRIGHT_10_16 5
#define TM1652_BRIGHT_14_16 7  // Max brightness

// ================= API Declarations =================

/**
 * @brief  Initialize the TM1652 driver and GPIOs.
 *         Should be called once during system boot.
 */
void Drv_TM1652_Init(void);

/**
 * @brief  Update the display buffer for a specific grid.
 *         This function is Non-blocking (writes to RAM only).
 * @param  grid_idx: Index of the digit (0 ~ TM1652_MAX_DIGITS-1)
 * @param  seg_data: 7-segment data (Common Cathode)
 */
void Drv_TM1652_SetDigit(unsigned char grid_idx, unsigned char seg_data);

/**
 * @brief  Set the display brightness.
 *         This function is Non-blocking.
 * @param  level: Brightness constant (TM1652_BRIGHT_x_16)
 */
void Drv_TM1652_SetBrightness(unsigned char level);

/**
 * @brief  Main driver task. Implements the protocol state machine.
 *         MUST be called cyclically in the main loop (e.g., every 1ms).
 *         DO NOT call this inside an ISR.
 */
void Drv_TM1652_Task(void);

#endif // _DRV_TM1652_H_