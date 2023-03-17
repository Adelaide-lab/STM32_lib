#include "bsp_led.h"


void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructR; //define the red led
	GPIO_InitTypeDef GPIO_InitStructG; //define the green led
	GPIO_InitTypeDef GPIO_InitStructB; //define the blue led
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructR.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructR.GPIO_Pin =GPIO_Pin_5;
	GPIO_InitStructR.GPIO_Speed=GPIO_Speed_50MHz;
	
	
	GPIO_InitStructG.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructG.GPIO_Pin =GPIO_Pin_0;
	GPIO_InitStructG.GPIO_Speed=GPIO_Speed_50MHz;
	
	
	GPIO_InitStructB.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructB.GPIO_Pin =GPIO_Pin_1;
	GPIO_InitStructB.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructR);
	GPIO_Init(GPIOB,&GPIO_InitStructG);
	GPIO_Init(GPIOB,&GPIO_InitStructB);
	/*turn off leds*/
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
}

void led_on(uint32_t color)
{
	assert_param(IS_COLOR_VALID(color));
	if(color==LED_R)
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	else if(color==LED_G)
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	else 
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}



void led_off(uint32_t color)
{
	assert_param(IS_COLOR_VALID(color));
	if(color==LED_R)
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
	else if(color==LED_G)
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
	else 
			GPIO_SetBits(GPIOB,GPIO_Pin_1);
	
}

void led_toggle(uint32_t color)
{
	assert_param(IS_COLOR_VALID(color));
	if(color==LED_R)
			GPIOB->ODR^=GPIO_Pin_5;
	else if(color==LED_G)
			GPIOB->ODR^=GPIO_Pin_0;
	else 
			GPIOB->ODR^=GPIO_Pin_1;
}

void led_blink(uint32_t time,uint32_t color)
{
	assert_param(IS_COLOR_VALID(color));
	while(key_scan(GPIOA,GPIO_Pin_0)==KEY_OFF)
	{
	 led_toggle(color);
	 sysdelay_secs(time);
	 led_toggle(color);
	 sysdelay_secs(time);
	}
}
