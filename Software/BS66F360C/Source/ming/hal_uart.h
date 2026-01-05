#ifndef __HAL_UART_H__
#define __HAL_UART_H__

#include	"MyDefine.h"
#include	"Variants.h"

void uart_init(void);
void uart_putchar(unsigned char c);
void uart_puts(const char *s);
void uart_putint(int num);
unsigned char uart_getchar(unsigned char *dat); // Non-blocking, returns 1 if data available, 0 if no data
void hal_uart_sendisr(unsigned char byte); 
void Log_PrintHex8(const char val);

#endif