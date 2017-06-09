#include "stdint.h"
#include "stdbool.h"

#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/fpu.h"

#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"

#include "udf_delay.h"
#include "udf_uart.h"


static uint8_t ui8led=2;
//--------------------DO NOT DELETE THIS FUNCTOIN------------------------------------------
void SystemInit(void)
{
	// this function set system clock to 50MHz
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |  SYSCTL_OSC_MAIN);
	//enable fpu
	ROM_FPUStackingEnable();
	ROM_FPUEnable();
	//Config UART0 8-N-1 115200 Use PA0 PA1
	Uart0Config();
	printf("System Init OK!...\r\n");
}
//--------------------END------------------------------------------------------------------

void LEDConfig(void)
{
		ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);  
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); 
		ROM_GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,(GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3));
}

void LEDFlash(void)
{
		ROM_GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0); 
  	DelayMs(50); 
		ROM_GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,ui8led+=2); 
  	DelayMs(950);
		if(ui8led==16)ui8led=2;
}


int main(void)
{   
		float fTemp=3.14;
		LEDConfig();
    while(1)
	   {
			LEDFlash();
			printf("%7.4f\r\n",fTemp);
			printf("Now the CLK is:%f MHZ\r\n",ROM_SysCtlClockGet()/1000000.0f);
		 }
//	return 0;
}
