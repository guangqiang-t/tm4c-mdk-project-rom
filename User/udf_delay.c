#include "udf_delay.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

void DelayMs(uint32_t time)
{
	ROM_SysCtlDelay(time * (ROM_SysCtlClockGet()/3000));
}

void DelayUs(uint32_t time)
{
	ROM_SysCtlDelay(time * (ROM_SysCtlClockGet()/3000000));
}
