#ifndef _udf_uart_H_
#define _udf_uart_H_

#include "stdint.h"
#include "stdbool.h"

#include "stdio.h"  //the two libs below use to redefine function "printf()"  use UART0 default
#include "stdarg.h"

void Uart0Config(void);
void UART0_Handler(void);

#endif

