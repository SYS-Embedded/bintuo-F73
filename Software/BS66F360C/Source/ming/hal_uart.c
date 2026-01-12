//HT66F3195
#include "hal_uart.h"
#include "drv_iouart_tx.h"
#include "interrupt.h"

#define DEBUG_LOG_ENABLE 0

// ========== Global receive and send buffer (optional, for interrupt reception) ==========
#define UART_RX_BUF_SIZE 16
static unsigned char uart_rx_buffer[UART_RX_BUF_SIZE];
static volatile unsigned char uart_rx_head = 0;
static volatile unsigned char uart_rx_tail = 0;

#define TX_BUFFER_SIZE 21

// buffer for UART TX channel
typedef struct 
{
    unsigned char buffer[TX_BUFFER_SIZE];
    volatile unsigned char head;
    volatile unsigned char tail;
    volatile unsigned char count;
} uart_tx_buffer_t;

static uart_tx_buffer_t uart_tx_buffers;

// ========== Define register bits (for readability) ==========
// UCR1
#define UARTEN  7   // UART enable
#define BNO     6   // Data bits: 0=8bits, 1=9bits
#define PREN    5   // Parity enable
#define PRT     4   // Parity type: 0=even parity, 1=odd parity
#define STOPS   3   // Stop bits: 0=1bit, 1=2bits
#define TXBRK   2   // Send break character
#define RX8     1   // Receive 8th bit (read only)
#define TX8     0   // Send 9th bit (write only)

// UCR2
#define TXEN    7   // Send enable
#define RXEN    6   // Receive enable
#define BRGH    5   // Baud rate selection: 0=low speed, 1=high speed
#define ADDEN   4   // Address detection enable
#define WAKE    3   // RX wake-up enable
#define RIE     2   // Receive interrupt enable
#define TIIE    1   // Transmit idle interrupt enable
#define TEIE    0   // Transmit register empty interrupt enable

// USR (Status register, read only)
#define PERR    7   // Parity error
#define NF      6   // Noise interference
#define FERR    5   // Frame error
#define OERR    4   // Receive overflow error
#define RIDLE   3   // Receive idle
#define RXIF    2   // Receive register full
#define TIDLE   1   // Transmit idle
#define TXIF    0   // Transmit register empty


#define	UART_ENABLE()			{_uarten = 1;}				//UART function enable
#define	UART_DISABLE()			{_uarten = 0;}				//UART function disable

#define	UART_TX_ENABLE()		{_txen = 1;}				//TX function enable
#define	UART_TX_DISABLE()		{_txen = 0;}				//TX function disable

#define	UART_RX_ENABLE()		{_rxen = 1;}				//RX function enable
#define	UART_RX_DISABLE()		{_rxen = 0;}				//RX function disable

#define	UART_ISR_ENABLE()		{_ure = 1;}				//UART interrupt enable
#define	UART_ISR_DISABLE()		{_ure = 0;}				//UART interrupt disable
#define	UART_CLEAR_ISR_FLAG()	{_urf = 0;}				//clear UART interrupt flag
#define	UART_SET_ISR_FLAG()		{_urf = 1;}				//set UART interrupt flag

#define UART_RIE_ENABLE()		{_rie = 1;}                 //UART receiver interrupt enable
#define UART_RIE_DISABLE()		{_rie = 0;}                 //UART receiver interrupt disable

#define UART_TIIE_ENABLE()		{_tiie = 1;}                 //UART transmitter idle interrupt enable
#define UART_TIIE_DISABLE()		{_tiie = 0;}                 //UART transmitter idle interrupt disable

#define UART_TEIE_ENABLE()		{_teie = 1;}                 //UART transmitter empty interrupt enable
#define UART_TEIE_DISABLE()		{_teie = 0;}                 //UART transmitter empty interrupt disable

#define UART_Addr_Det_ENABLE()	{_adden = 1;}                //UART Address detect function enable
#define UART_Addr_Det_DISABLE()	{_adden = 0;}                //UART Address detect function disable

#define UART_RX_Wake_ENABLE()	{_wake = 1;}                 //UART RX pin falling edge wake-up function enable
#define UART_RX_Wake_DISABLE()	{_wake = 0;}                 //UART RX pin falling edge wake-up function disable

#define UART_TXBRK_ENABLE()		{_txbrk = 1;}                //UART transmit break character function enable
#define UART_TXBRK_DISABLE()	{_txbrk = 0;}                //UART transmit break character function disable


void uart_init(void) 
{
    unsigned char dummy;
    //_wdtc = 0b10101111; 

    // Configure PD1 as RX0, PD2 as TX0 (according to PDS0 register)
    _pfc3 = 0;
    _pfs07 = 0;
    _pfs06 = 1; //Pf3 TX  red pin, eighth pin

    // Configure UART
    // UCR1: 8 data bits, no parity, 1 stop bit
    _ucr1 = (0 << UARTEN) |   // First disable UART
             (1 << BNO)     |   // 9 data bits
             (1 << PREN)    |   // No parity
             (1 << PRT)     |   // (even parity, but no parity when disabled)
             (0 << STOPS)   |   // 1 stop bit
             (0 << TXBRK);      // No break character

    // UCR2: Enable send and receive, high speed baud rate, enable receive interrupt
    _ucr2 = (0 << TXEN) |     // Enable send
             (0 << RXEN) |     // Enable receive
             (1 << BRGH) |     // High speed baud rate (fH/16)
             (0 << ADDEN)|     // Disable address detection
             (0 << WAKE) |     // Disable wake-up
             (0 << RIE)  |     // Enable receive interrupt
             (0 << TIIE) |     // Disable transmit idle interrupt
             (0 << TEIE);      // Disable transmit register empty interrupt

    // Set baud rate (high speed mode: baud rate = fSYS / [16 * (BRG + 1)])
    #define SYS_OSC     16000000UL  // System clock 16MHz
    #define UART_BR     38400       // Target baud rate
    _brg = (SYS_OSC / (16UL * UART_BR)) - 1; // Calculate BRG value

    /************************************************************
    PS:If Fsys = 16MHZ, BaudRate input values reference table.
    -------------------------------------------------------------------
    | Baud Rate values | 4800 | 9600 | 19200 | 38400 | 57600 |115200|
    -------------------------------------------------------------------
    | High speed Mode  | 0xcf | 0x67 |  0x33 |  0x19 |  0x10 | 0x08 |
    | error rate       | 0.16%| 0.16%| 0.16% | 0.16% |  2.1% |-3.5% |
    -------------------------------------------------------------------
    | Low speed Mode   | 0x33 | 0x19 | 0x0c  |  ---- |  ---- |    
    | error rate       | 0.16%| 0.16%| 0.16% |  ---- |  ---- |
    -------------------------------------------------------------------  

    PS:If Fsys = 12MHZ, BaudRate input values reference table.
    -------------------------------------------------------------------
    | Baud Rate values | 4800 | 9600 | 19200 | 38400 | 57600 |115200|
    -------------------------------------------------------------------
    | High speed Mode  | 0x9b | 0x4d |  0x26 |  0x13 |  0x0c | ---- |
    | error rate       | 0.16%| 0.16%| 0.16% | -2.3% | 0.16% | ---- |
    -------------------------------------------------------------------
    | Low speed Mode   | 0x26 | 0x13 | 0x09  |  0x04 |  ---- | ---- |  
    | error rate       | 0.16%|-2.3% |-2.3%  | -2.3% |  ---- | ---- |
    -------------------------------------------------------------------  

    PS:If Fsys = 8MHZ, BaudRate input values reference table.
    -------------------------------------------------------------------
    | Baud Rate values | 4800 | 9600 | 19200 | 38400 | 57600 | 
    -------------------------------------------------------------------
    | High speed Mode  | 0x67 | 0x33 |  0x19 |  0x0c |  0x08 | 
    | error rate       | 0.16%| 0.16%| 0.16% | 0.16% | -3.5% |
    -------------------------------------------------------------------
    | Low speed Mode   | 0x19 | 0x0c |  ---- |  ---- |  ---- |    
    | error rate       | 0.16%| 0.16%| 
    -------------------------------------------------------------------  
    **********************************************************************/
    _brg = 0x33; //19200 //fix me using fsys=8Mhz configuration, but now I have 16M?

    dummy = _usr; //read status register
    (void)dummy; 

    // Enable UART
    //_ucr1 |= (1 << UARTEN);

    // Enable UART interrupt and global interrupt
    //_uarte = 1;  
    _emi = 1; 
	//EMI_ENABLE();
	uart_tx_buffers.head = 0;
	uart_tx_buffers.tail = 0;
	uart_tx_buffers.count = 0;

	UART_CLEAR_ISR_FLAG();
	UART_ISR_ENABLE();
	UART_RIE_DISABLE();
    UART_TIIE_DISABLE();
    UART_TEIE_DISABLE();
	UART_ENABLE();
	UART_TX_ENABLE();
	//UART_RX_ENABLE();
}

// ========== UART send one byte ==========
void uart_putchar(unsigned char data) 
{
	#if DEBUG_LOG_ENABLE
	/* Initialization */
	_tx8 = 0;		


	/* waiting UART transmitter free */
	while(!_txif)
	{
		_nop();
	}				
	/* end */
	
	/**************************************/

	/* Write data to UART transmitter */
	#ifdef	NINE_BIT_MODE
		#if defined(EVENPR_MODE) || defined(ODDPR_MODE)
			_txr_rxr = data;	//MSB is parity bit
		#else
			if( data > 255)
			{
				_tx8 = 1;		//MSB is data bit
			}
			_txr_rxr = data;
		#endif	
	#else
		_txr_rxr = data;
	#endif
	/* Write end */

	/**************************************/

	/* Waiting UART transmit data finished*/
	while(!_tidle)		
	{
		_nop();
	}	
	/* transmit finished */
	#endif
}

void uart_putint(int num) 
{
    #if DEBUG_LOG_ENABLE
    char buffer[12]; // Sufficient string table to accommodate 32-bit integer
    int i = 0;
    int is_negative = 0;
    
    // Process negative number
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    // Process special case
    if (num == 0) {
        uart_putchar('0');
        return;
    }
    
    // Convert number to string (in reverse order)
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    
    // Add negative sign
    if (is_negative) {
        buffer[i++] = '-';
    }
    
    // Output characters in reverse order
    while (i > 0) {
        uart_putchar(buffer[--i]);
    }
    #endif
}

void uart_puts(const char *s) 
{
    #if DEBUG_LOG_ENABLE
    while (*s) 
    {
        uart_putchar(*s);
        s++;
    }
    #endif
}


static char NibbleToChar(const char nibble) {
    if (nibble < 10)
        return '0' + nibble;
    else
        return 'A' + (nibble - 10);
}

// --- API: Print 8-bit Hex (Format: XX) ---
// Resource-efficient, only bit shift operations
void Log_PrintHex8(const char val) 
{
    char temp;

    temp = NibbleToChar((val >> 4) & 0x0F);
    uart_putchar(temp); // High 4 bits
    temp = NibbleToChar(val & 0x0F);
    uart_putchar(temp);        // Low 4 bits
}




// ========== UART non-blocking receive one byte ==========
unsigned char uart_getchar(unsigned char *dat) 
{
    unsigned char ret = 0;
    _emi  =	0;
    if (uart_rx_head != uart_rx_tail) 
    {
        // Buffer has data
        *dat = uart_rx_buffer[uart_rx_tail];
        uart_rx_tail = (uart_rx_tail + 1) % UART_RX_BUF_SIZE;
        ret = 1;
    }
    _emi  =	1;
    return ret;
}


#define DISABLE_UART_TX_INT() (_teie=0)
#define ENABLE_UART_TX_INT() (_teie=1)

void hal_uart_sendisr(unsigned char byte) 
{
	//unsigned char old_interrupt_state;
    unsigned char status;
    uart_tx_buffer_t *buf = &uart_tx_buffers;
    unsigned int timeout = 0;
    
    // wait for buffer space
    while (buf->count >= TX_BUFFER_SIZE) {
        // timeout handling
        if(timeout++ > 10000)
        {
            IOUART_SendString("Err-uarttxbuffull\n");
            return;
        }
            
    }
    
	// Disable interrupt to protect critical section
    //old_interrupt_state = HAL_INT_GET();
    //HAL_INT_SET(0);
    
    _emi  =	0;
    // Put byte into buffer
    buf->buffer[buf->head] = byte;
    buf->head++;
	if(buf->head >= TX_BUFFER_SIZE)
	{
		buf->head = 0;
	}
    buf->count++;
    _emi  =	1;
     
    // If UART is idle, start transmission
    if (buf->count == 1) 
	{
        // Write directly to UART transmit register, trigger transmission
        _tx8 = 0;


		//while(TRMT)
		{
			//TXREG = 
            status = _usr;
            (void)status;
            _txr_rxr = buf->buffer[buf->tail];
		}
        // Enable transmission complete interrupt
        //ENABLE_UART_TX_INT();
    }
    UART_TEIE_ENABLE();
    
    // Restore interrupt
	//HAL_INT_SET(old_interrupt_state);
   
}



void UART_ISR(void) 
{
	volatile unsigned char status;
    volatile unsigned char data;
    volatile unsigned char next_head;
    volatile uart_tx_buffer_t *buf = &uart_tx_buffers;

    // Check if it's receive interrupt (RXIF)
    status = _usr;

    #if 0
    if (status & (1 << RXIF)) 
    {
        // Read status register (must read USR first)
        status = _usr;
        // Read received data (automatically clears RXIF and error flags)
        data = _txr_rxr;

        next_head = (uart_rx_head + 1) % UART_RX_BUF_SIZE;
        if (next_head != uart_rx_tail) 
        { // Buffer not full
            uart_rx_buffer[uart_rx_head] = data;
            uart_rx_head = next_head;
        }
        // If buffer is full, new data will be discarded (optional: add overflow counter)
    }
    #endif

    if ((status & (1 << TXIF)) && (buf->count > 0))  //UART transmission complete interrupt
	{
	    
		// Check if there is still data to send
		//if (buf->count > 0) 
        {
			// Update tail pointer
			buf->tail++;
			if(buf->tail >= TX_BUFFER_SIZE)
			{
				buf->tail = 0;
			}

			buf->count--;
			
			// If there is still data, continue sending
			if (buf->count > 0) 
			{
				//TXREG = buf->buffer[buf->tail];
				status = _usr;
                _txr_rxr = buf->buffer[buf->tail];
			} 
			else 
			{
				// No more data, disable send interrupt
				//DISABLE_UART_TX_INT();
                //UART_TEIE_DISABLE();
			}
		}
        //else
		//{
			// No more data, disable send interrupt
			//DISABLE_UART_TX_INT();
         //   UART_TEIE_DISABLE();
		//}
	}

    // Clear interrupt flag (UARTF in INTC2, automatically cleared by hardware)
    // Note: RXIF/TXIF flags in USR need to be cleared by read/write operations, already handled above
    //_uartf = 0; // Clear UART interrupt request flag (in INTC2)
    UART_CLEAR_ISR_FLAG();
}