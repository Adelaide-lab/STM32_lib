#include "bsp_key.h"
#include "bsp_led.h"

void key_init()
{
	GPIO_InitTypeDef GPIO_InitStructK1; //define the key1
	GPIO_InitTypeDef GPIO_InitStructK2; //define the key2
	NVIC_InitTypeDef NVIC_KEY_InitStruct;
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE|RCC_APB2Periph_AFIO);
	GPIO_InitStructK1.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructK1.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructK2.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructK2.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOA,&GPIO_InitStructK1);
	GPIO_Init(GPIOC,&GPIO_InitStructK2);
	
	NVIC_KEY_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_KEY_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_KEY_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_KEY_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_KEY_InitStruct);
	
	NVIC_KEY_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_Init(&NVIC_KEY_InitStruct);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line13; 
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI0_IRQHandler(void)
{
		if(EXTI_GetITStatus(EXTI_Line0) != RESET)
		{
				led_toggle(LED_R);
			  EXTI_ClearITPendingBit(EXTI_Line0);
		}
}

void EXTI15_10_IRQHandler(void)
{
		if(EXTI_GetITStatus(EXTI_Line13) != RESET)
		{
				led_toggle(LED_G);
			  EXTI_ClearITPendingBit(EXTI_Line13);
		}
}

uint8_t key_scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
		{while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
					return KEY_ON;}
	else 
		{return KEY_OFF;}
}
