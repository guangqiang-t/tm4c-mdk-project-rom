#include "udf_uart.h"

#include "driverlib/rom.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"  // about line 30 in this file  use "GPIO_PA0_U0RX" in this lib (in line 8052)
#include "driverlib/interrupt.h"

#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"

void Uart0Config(void)
{
		//
    // Enable the peripherals used.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
		
		ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
		ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
	
		//
    // Set GPIO A0 and A1 as UART pins.
    //
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
		ROM_UARTClockSourceSet(UART0_BASE,UART_CLOCK_SYSTEM);
		
		ROM_UARTFIFODisable(UART0_BASE);
	
		ROM_UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	
//		Enable Interrupt
		ROM_IntEnable(INT_UART0);
		ROM_UARTIntEnable(UART0_BASE, UART_INT_RX|UART_INT_RT);
	
		ROM_UARTEnable(UART0_BASE);
		
//		UARTCharPut(UART0_BASE,'#');//begin 
		printf("\r\nUART0 Init OK!,This is TM4C123GH6PM...\r\n");
}

int fputc(int ch, FILE *f)
{
	while(ROM_UARTBusy(UART0_BASE)==true);
	ROM_UARTCharPut(UART0_BASE,ch);
  return (ch);
}

//
//  this is the INTERRUPT handler of UART0
//
void UART0_Handler(void)
{
	uint8_t ui8CharTemp=0;
	uint32_t ui32Status;
	ui32Status = ROM_UARTIntStatus(UART0_BASE, true);
	ROM_UARTIntClear(UART0_BASE,ui32Status);
	ui8CharTemp=ROM_UARTCharGet(UART0_BASE);
	ROM_GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0xff);
	printf("\r\nUART0 Rxd a char :%c\r\n",ui8CharTemp);
}

