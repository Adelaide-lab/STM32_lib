#include "bsp_sysdelay.h"


void sysdelay_init(void)
{
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); /*set the sysclock source*/
}

void sysdelay_micro_secs(uint32_t delay_times)
{
	  uint32_t micro_interval = SystemCoreClock/1000000;
		while(delay_times--)
		{
			SysTick_Config(micro_interval);
			while( !((SysTick->CTRL) & (1<<16)) );
			}
		
		SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
			
}

void sysdelay_mil_secs(uint32_t delay_times)
{
	uint32_t mili_interval = SystemCoreClock/1000;
	while(delay_times--)
		{
			SysTick_Config(mili_interval);
			while( !((SysTick->CTRL) & (1<<16)) );
			}
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
	
}

void sysdelay_secs(uint32_t delay_times)
{
	uint32_t sec_interval = SystemCoreClock/8;
	while(delay_times--)
		{
			SysTick_Config(sec_interval);
			while( !((SysTick->CTRL) & (1<<16)) );
			}
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

