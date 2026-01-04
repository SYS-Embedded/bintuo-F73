#include "tm1652.h"

// ================== 移植适配层 (Holtek Specific) ==================

// 假设SDA接在 PA.3，请根据实际电路修改
#define SDA_PIN         _pa3
#define SDA_DIR         _pac3 

// 设置SDA为输出高 (空闲态)
#define SDA_HIGH()      { SDA_DIR = 0; SDA_PIN = 1; }
// 设置SDA为输出低
#define SDA_LOW()       { SDA_DIR = 0; SDA_PIN = 0; }

// 19200bps -> 1 bit ≈ 52us
// Holtek @ 8MHz / 4T = 2MHz 指令周期 (0.5us)
// 52us 需要约 104 个指令周期。调用开销约10周期。
// 需要根据示波器实测调整这里的 NOP 数量
#define DELAY_BIT_52US()  { \
    unsigned char i = 30; \
    while(i--) { _nop(); } \
}

// ================== 内部变量 ==================

// 显存 (RAM Bank 0)
static unsigned char g_DispBuf[TM1652_DIGIT_CNT];
static unsigned char g_Brightness;
static unsigned char g_UpdateFlags; // 0:无更新, 1:需要刷新数据, 2:需要刷新控制

// 状态机定义
typedef enum {
    SM_IDLE = 0,
    SM_SEND_ADDR_CMD,
    SM_SEND_DATA,
    SM_WAIT_LATCH_DATA,  // 等待数据帧的3ms
    SM_SEND_CTRL_CMD,
    SM_WAIT_LATCH_CTRL   // 等待控制帧的3ms
} TM1652_State_t;

static TM1652_State_t g_State;
static unsigned char g_SendIdx;
static unsigned char g_WaitTimer; // 用于非阻塞延时计数

// ================== 内部函数 ==================

/**
 * @brief 软件UART发送一个字节 (19200, 8-O-1)
 * @note  TM1652要求奇校验(Odd Parity)
 *        Start(0) + 8 Data + Parity + Stop(1)
 */
static void SendByte(unsigned char dat)
{
    unsigned char i;
    unsigned char parity_cnt = 0;

    // 1. Start Bit (Low)
    SDA_LOW();
    DELAY_BIT_52US();

    // 2. Data Bits (LSB First)
    for(i = 0; i < 8; i++)
    {
        if(dat & 0x01)
        {
            SDA_HIGH();
            parity_cnt++;
        }
        else
        {
            SDA_LOW();
        }
        dat >>= 1;
        DELAY_BIT_52US();
    }

    // 3. Parity Bit (Odd: High if data has even number of 1s)
    // 文档P4: "如果8位数据位中1的个数为奇数，该位为0，否则为1"
    if(parity_cnt % 2 != 0) // 奇数个1
    {
        SDA_LOW(); 
    }
    else // 偶数个1
    {
        SDA_HIGH();
    }
    DELAY_BIT_52US();

    // 4. Stop Bit (High)
    SDA_HIGH();
    DELAY_BIT_52US();
}

// ================== 外部接口实现 ==================

void TM1652_Init(void)
{
    unsigned char i;
    SDA_HIGH(); // 总线空闲
    
    // 初始化显存为全灭 (0x00)
    for(i=0; i<TM1652_DIGIT_CNT; i++)
    {
        g_DispBuf[i] = 0x00; 
    }
    
    // 默认亮度
    g_Brightness = 0xF1; // 默认开显示，亮度适中(根据P6表格拼凑)
    
    g_State = SM_IDLE;
    g_UpdateFlags = 3; // 上电强制刷新一次
}

void TM1652_SetDigit(unsigned char addr, unsigned char data)
{
    if(addr < TM1652_DIGIT_CNT)
    {
        // 只有数据改变才触发刷新，节省CPU
        if(g_DispBuf[addr] != data)
        {
            g_DispBuf[addr] = data;
            g_UpdateFlags |= 1; // 标记：数据需更新
        }
    }
}

void TM1652_SetBrightness(unsigned char level)
{
    unsigned char cmd;
    // 构造控制命令 (参考PDF P6)
    // B7-B0: 
    // 显示控制命令格式: 0 0 0 1 (Fixed) + [B3 B2 B1 B0]
    // 但P6定义有些分散，我们需要发送的是控制调节命令 0x18 + 设置参数
    // PDF P6表格: 
    // 显示开关: 0000(关) / 1000 (开, 对应位占空比设置)
    // 实际上TM1652通常流程是: 发0x18(CommandX) -> 发控制字(CommandY)
    
    // 简化处理，这里仅保存应用层意图，Task里组包
    if(level > 7) level = 7;
    // 组装CommandY (包含开显示位 + 亮度)
    // P6: 0x18命令后的参数。
    // 假设我们要开显示，且设置段驱动电流(通常选中等)
    // 这里简单映射：开显示(BIT3=1) + 占空比(level)
    // 注意：TM1652控制字比较复杂，这里给一个典型值模板
    // CommandY = 0b00010000 | (level << 4) ... 需根据具体需求细调
    // 这里暂存Level，Task中处理
    if(g_Brightness != level) 
    {
        g_Brightness = level;
        g_UpdateFlags |= 2; // 标记：控制需更新
    }
}

// 假设主循环大概 2ms-5ms 跑一圈，或者由定时器Flag驱动
// 为了确保3ms时间够，建议用一个计数器
void TM1652_Task(void)
{
    switch(g_State)
    {
        case SM_IDLE:
            if(g_UpdateFlags & 1) // 优先处理数据刷新
            {
                g_State = SM_SEND_ADDR_CMD;
            }
            else if(g_UpdateFlags & 2) // 处理亮度/控制刷新
            {
                g_State = SM_SEND_CTRL_CMD;
            }
            break;

        case SM_SEND_ADDR_CMD:
            // 发送地址设定命令 (0x08) - PDF P7
            // B7..B0: 0000 1000 = 0x08
            SendByte(0x08); 
            g_SendIdx = 0;
            g_State = SM_SEND_DATA;
            break;

        case SM_SEND_DATA:
            // 发送当前索引的数据
            SendByte(g_DispBuf[g_SendIdx]);
            g_SendIdx++;
            
            // 检查是否发完所有位
            if(g_SendIdx >= TM1652_DIGIT_CNT)
            {
                g_UpdateFlags &= ~1; // 清除数据更新标记
                g_WaitTimer = 20;    // 约需要等待 >3ms
                g_State = SM_WAIT_LATCH_DATA;
            }
            break;

        case SM_WAIT_LATCH_DATA:
            // 这里依赖Task的调用频率。
            // 假设Task每0.5ms调用一次，Count 20 = 10ms > 3ms，安全。
            // 如果主频很快，这里需要调整
            if(g_WaitTimer > 0)
            {
                g_WaitTimer--;
            }
            else
            {
                g_State = SM_IDLE; // 回到空闲，准备下一次可能的传输
            }
            break;

        case SM_SEND_CTRL_CMD:
            // 1. 发送显示控制命令头 0x18
            SendByte(0x18);
            
            // 2. 发送显示控制调节命令 (CommandY) - PDF P6
            // 格式：我们需要设置 亮度(占空比) + 段电流 + 显示开
            // 举例：8段5位模式(0), 14/16占空比(0111), 段电流4/8(110)
            // 组合字节需查表 P6。
            // 简单起见，这里发一个固定配置+亮度
            // 假设: 7段6位模式(1), 开显示, 亮度由g_Brightness决定
            {
                // 构造配置字 (示例：位占空比设置)
                unsigned char ctrl_data = 0x10; // 基础值
                // 实际应用需根据P6的表查出对应的Byte
                // 这里仅作示例发送
                ctrl_data |= (g_Brightness << 4); 
                SendByte(ctrl_data);
            }
            
            g_UpdateFlags &= ~2;
            g_WaitTimer = 20;
            g_State = SM_WAIT_LATCH_CTRL;
            break;

        case SM_WAIT_LATCH_CTRL:
            if(g_WaitTimer > 0)
                g_WaitTimer--;
            else
                g_State = SM_IDLE;
            break;
            
        default:
            g_State = SM_IDLE;
            break;
    }
}