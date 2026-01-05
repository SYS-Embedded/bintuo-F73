/**
 * @file    drv_tm1652.c
 * @brief   Implementation of TM1652 Driver
 */
#include "hal_uart.h"
#include "drv_tm1652.h"

// ================= Hardware Abstraction =================

#if 0
// Adjust these macros based on your schematic
// Example: SDA is connected to Port A, Pin 3
#define TM1652_SDA_PIN      _pa3
#define TM1652_SDA_DIR      _pac3 

// Set SDA Line High (Idle State)
#define PIN_SDA_HIGH()      { TM1652_SDA_DIR = 0; TM1652_SDA_PIN = 1; }
// Set SDA Line Low
#define PIN_SDA_LOW()       { TM1652_SDA_DIR = 0; TM1652_SDA_PIN = 0; }


// ================= Timing Calibration =================

// Baudrate: 19200 bps => 1 bit ~= 52us
// Calibration Guide:
// 1. Connect an oscilloscope to the SDA pin.
// 2. Adjust the loop count 't' until the bit width is approx 52us.
// 3. For Holtek @ 8MHz (0.5us instruction cycle), ~100 cycles needed.
static void DelayBit_52us(void)
{
    // 'volatile' prevents compiler optimization from removing the loop
    volatile unsigned char t = 30; 
    while(t--) { _nop(); }
}
#endif

// ================= Private Definitions =================

// State Machine States
typedef enum {
    STATE_IDLE = 0,
    STATE_SEND_ADDR,
    STATE_SEND_DATA,
    STATE_WAIT_LATCH_DATA,  // Wait >3ms for data latch
    STATE_SEND_CTRL,
    STATE_WAIT_LATCH_CTRL   // Wait >3ms for control latch
} DrvState_t;

// Flags for update management
#define FLAG_UPDATE_DATA    0x01
#define FLAG_UPDATE_CTRL    0x02

// ================= Private Variables =================

// Display Buffer (RAM Bank 0)
static unsigned char s_DispBuf[TM1652_MAX_DIGITS];
static unsigned char s_BrightnessLevel;
static unsigned char s_UpdateFlags;

static DrvState_t    s_CurrentState;
static unsigned char s_SendIndex;
static unsigned char s_WaitTimer; // Timer for non-blocking delay

// ================= Private Functions =================

/**
 * @brief  Bit-Bang a single byte using 19200bps 8-O-1 Protocol.
 *         Format: Start(0) + 8 Data + Parity(Odd) + Stop(1)
 * @param  dat: Byte to send
 */

static void TM1652_SendByte(unsigned char dat)
{
#if 0
    unsigned char i;
    unsigned char ones_count = 0;


    // 1. Start Bit (Low)
    PIN_SDA_LOW();
    DelayBit_52us();

    // 2. Data Bits (LSB First)
    for(i = 0; i < 8; i++)
    {
        if(dat & 0x01)
        {
            PIN_SDA_HIGH();
            ones_count++;
        }
        else
        {
            PIN_SDA_LOW();
        }
        dat >>= 1;
        DelayBit_52us();
    }

    // 3. Odd Parity Bit
    // Rule: If number of 1s in data is ODD, Parity bit = 0 (Low).
    //       If number of 1s in data is EVEN, Parity bit = 1 (High).
    if(ones_count & 0x01) 
    {
        PIN_SDA_LOW();  // Odd 1s -> Parity 0
    }
    else 
    {
        PIN_SDA_HIGH(); // Even 1s -> Parity 1
    }
    DelayBit_52us();

    // 4. Stop Bit (High)
    PIN_SDA_HIGH();
    DelayBit_52us();
#endif
}

// ================= Public API Implementation =================

void drv_tm1652_init(void)
{
    unsigned char i;
    
    // 1. Init Hardware
    //PIN_SDA_HIGH(); 
    uart_init();
    
    // 2. Clear Buffer
    for(i = 0; i < TM1652_MAX_DIGITS; i++)
    {
        s_DispBuf[i] = 0x00; 
    }
    
    // 3. Default Settings
    s_BrightnessLevel = TM1652_BRIGHT_4_16; 
    s_CurrentState = STATE_IDLE;
    
    // 4. Force refresh on startup
    s_UpdateFlags = FLAG_UPDATE_DATA | FLAG_UPDATE_CTRL;
}

void drv_tm1652_setdigit(unsigned char grid_idx, unsigned char seg_data)
{
    if(grid_idx >= TM1652_MAX_DIGITS) return;

    // Only set flag if data actually changed to save CPU time
    if(s_DispBuf[grid_idx] != seg_data)
    {
        s_DispBuf[grid_idx] = seg_data;
        s_UpdateFlags |= FLAG_UPDATE_DATA;
    }
}

void drv_tm1652_setbrightness(unsigned char level)
{
    if(level > 7) level = 7;
    
    if(s_BrightnessLevel != level)
    {
        s_BrightnessLevel = level;
        s_UpdateFlags |= FLAG_UPDATE_CTRL;
    }
}

#if 1
void drv_tm1652_task(void)
{
    unsigned char param = 0x10;
    
    if(s_UpdateFlags & FLAG_UPDATE_DATA)
    {
        // Start sending display data
        hal_uart_sendisr(0x08);
        hal_uart_sendisr(s_DispBuf[0]);
        hal_uart_sendisr(s_DispBuf[1]);
        hal_uart_sendisr(s_DispBuf[2]);
        hal_uart_sendisr(s_DispBuf[3]);
        hal_uart_sendisr(s_DispBuf[4]);
        hal_uart_sendisr(s_DispBuf[5]);
        s_UpdateFlags &= ~FLAG_UPDATE_DATA;
    }
    else if(s_UpdateFlags & FLAG_UPDATE_CTRL)
    {
        // Start sending control command
        hal_uart_sendisr(0x18);
        param |= (s_BrightnessLevel << 4); 
        hal_uart_sendisr(param);
        s_UpdateFlags &= ~FLAG_UPDATE_CTRL;
    }

}
#else
void drv_tm1652_task(void)
{
    // Simple FSM to handle protocol without blocking main loop
    switch(s_CurrentState)
    {
        case STATE_IDLE:
            if(s_UpdateFlags & FLAG_UPDATE_DATA)
            {
                // Start sending display data
                s_CurrentState = STATE_SEND_ADDR;
            }
            else if(s_UpdateFlags & FLAG_UPDATE_CTRL)
            {
                // Start sending control command
                s_CurrentState = STATE_SEND_CTRL;
            }
            break;

        case STATE_SEND_ADDR:
            // Command: Set Address (0x08)
            hal_uart_sendisr(0x08); 
            s_SendIndex = 0;
            s_CurrentState = STATE_SEND_DATA;
            break;

        case STATE_SEND_DATA:
            // Send current digit data
            hal_uart_sendisr(s_DispBuf[s_SendIndex]);
            s_SendIndex++;
            
            // Check if all digits sent
            if(s_SendIndex >= TM1652_MAX_DIGITS)
            {
                // Clear data flag
                s_UpdateFlags &= ~FLAG_UPDATE_DATA;
                // Setup timer for Latch delay (need >3ms)
                // Assuming Task called every 0.5ms~1ms, 20 ticks is safe
                s_WaitTimer = 20; 
                s_CurrentState = STATE_WAIT_LATCH_DATA;
            }
            break;

        case STATE_WAIT_LATCH_DATA:
            // Non-blocking wait for >3ms Latch signal (High Level)
            if(s_WaitTimer > 0)
            {
                s_WaitTimer--;
            }
            else
            {
                s_CurrentState = STATE_IDLE; // Ready for next transaction
            }
            break;

        case STATE_SEND_CTRL:
            // 1. Header: Display Control (0x18)
            hal_uart_sendisr(0x18);
            
            // 2. Parameter: Brightness + Current + On/Off
            // Constructing the byte based on Table 5 (Page 6)
            // Example configuration:
            // - Display Mode: 7-segment (Bit0=1 is implied in some settings, check specific wiring)
            // - Current: Medium
            // - Brightness: s_BrightnessLevel
            {
                // Base: 0x10 (Display ON logic base)
                // Adjust this byte according to your schematic (7-seg or 8-seg mode)
                unsigned char param = 0x10; 
                param |= (s_BrightnessLevel << 4); 
                hal_uart_sendisr(param);
            }
            
            s_UpdateFlags &= ~FLAG_UPDATE_CTRL;
            s_WaitTimer = 20; // >3ms wait
            s_CurrentState = STATE_WAIT_LATCH_CTRL;
            break;

        case STATE_WAIT_LATCH_CTRL:
            if(s_WaitTimer > 0)
                s_WaitTimer--;
            else
                s_CurrentState = STATE_IDLE;
            break;
            
        default:
            s_CurrentState = STATE_IDLE;
            break;
    }
}
#endif