#ifndef  __SG90_H__
#define  __SG90_H__
#include "stm32f10x.h"

/*Ҫʹ��ʲô��ɫ�ĺ����ƣ���ѡRED_LIGHT��GREEN_LIGHT��BLUE_LIGHT*/
#define LIGHT_COLOR 	RED_LIGHT

/********************��ʱ��ͨ��**************************/
#if  LIGHT_COLOR == RED_LIGHT
/************���***************/
	#define   BRE_TIMx                      TIM3

	#define   BRE_TIM_APBxClock_FUN        RCC_APB1PeriphClockCmd
	#define   BRE_TIM_CLK                   RCC_APB1Periph_TIM3
	#define   BRE_TIM_GPIO_APBxClock_FUN   RCC_APB2PeriphClockCmd
	#define   BRE_TIM_GPIO_CLK              (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)

	//��Ƶ�������Ҫ��ӳ��
	#define   BRE_GPIO_REMAP_FUN()						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); 				

	#define  BRE_TIM_LED_PORT               GPIOB
	#define  BRE_TIM_LED_PIN                GPIO_Pin_5

	#define  BRE_TIM_OCxInit                TIM_OC2Init            //ͨ��ѡ��1~4
	#define  BRE_TIM_OCxPreloadConfig       TIM_OC2PreloadConfig 
	#define  BRE_CCRx                       CCR2

	#define   BRE_TIMx_IRQn                TIM3_IRQn              //�ж�
	#define   BRE_TIMx_IRQHandler          TIM3_IRQHandler

#elif LIGHT_COLOR == GREEN_LIGHT
/************�̵�***************/
	#define   BRE_TIMx                      TIM3

	#define   BRE_TIM_APBxClock_FUN        RCC_APB1PeriphClockCmd
	#define   BRE_TIM_CLK                   RCC_APB1Periph_TIM3
	#define   BRE_TIM_GPIO_APBxClock_FUN   RCC_APB2PeriphClockCmd
	#define   BRE_TIM_GPIO_CLK              (RCC_APB2Periph_GPIOB)

	//�̵Ʋ���Ҫ��ӳ��
	#define   BRE_GPIO_REMAP_FUN()				


	#define  BRE_TIM_LED_PORT               GPIOB
	#define  BRE_TIM_LED_PIN                GPIO_Pin_0

	#define  BRE_TIM_OCxInit                TIM_OC3Init            //ͨ��ѡ��1~4
	#define  BRE_TIM_OCxPreloadConfig       TIM_OC3PreloadConfig 
	#define  BRE_CCRx                       CCR3

	#define   BRE_TIMx_IRQn                TIM3_IRQn              //�ж�
	#define   BRE_TIMx_IRQHandler          TIM3_IRQHandler

#elif LIGHT_COLOR == BLUE_LIGHT
/************����***************/
	#define   BRE_TIMx                      TIM3

	#define   BRE_TIM_APBxClock_FUN        RCC_APB1PeriphClockCmd
	#define   BRE_TIM_CLK                   RCC_APB1Periph_TIM3
	#define   BRE_TIM_GPIO_APBxClock_FUN   RCC_APB2PeriphClockCmd
	#define   BRE_TIM_GPIO_CLK              (RCC_APB2Periph_GPIOB)

	//���Ʋ���Ҫ��ӳ��
	#define   BRE_GPIO_REMAP_FUN()	

	#define   BRE_TIM_LED_PORT             GPIOB
	#define   BRE_TIM_LED_PIN              GPIO_Pin_1

	#define   BRE_TIM_OCxInit              TIM_OC4Init            //ͨ��ѡ��1~4
	#define   BRE_TIM_OCxPreloadConfig    TIM_OC4PreloadConfig 
	#define   BRE_CCRx                      CCR4

	#define   BRE_TIMx_IRQn                TIM3_IRQn              //�ж�
	#define   BRE_TIMx_IRQHandler          TIM3_IRQHandler
	

#endif

void Timer_Init(void);
void Servor_Init(void);
void Servor_Angler_Set(float angle);
#endif