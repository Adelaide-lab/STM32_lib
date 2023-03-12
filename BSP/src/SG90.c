#include "SG90.h"

void Timer_Init(void)
{
//		GPIO_InitTypeDef Timer_Init;
//		TIM_TimeBaseInitTypeDef Timer_BaseInitStruct;
//		TIM_OCInitTypeDef 	Timer_OCInitStruct;
//	
//		Timer_Init.GPIO_Mode  = GPIO_Mode_AF_PP;
//		Timer_Init.GPIO_Pin      = GPIO_Pin_5;
//		Timer_Init.GPIO_Speed = GPIO_Speed_50MHz;
//	
//		GPIO_Init(GPIOB,&Timer_Init);
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//		RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	
//		Timer_BaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//		Timer_BaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
//		Timer_BaseInitStruct.TIM_Period						= 20000-1;
//		Timer_BaseInitStruct.TIM_Prescaler       = 72-1;
//		Timer_BaseInitStruct.TIM_RepetitionCounter = 0;
//		TIM_TimeBaseInit(TIM3,&Timer_BaseInitStruct);
//	
//		TIM_OCStructInit(&Timer_OCInitStruct);
//		Timer_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
//		Timer_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
//		Timer_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
//		Timer_OCInitStruct.TIM_Pulse = 0;
//		TIM_OC3Init(TIM3,&Timer_OCInitStruct);
//		
//		TIM_Cmd(TIM3,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	

  /*  clock enable */
  RCC_APB2PeriphClockCmd(BRE_TIM_GPIO_CLK, ENABLE); 
  BRE_TIM_GPIO_APBxClock_FUN  ( BRE_TIM_GPIO_CLK, ENABLE );
		
	BRE_GPIO_REMAP_FUN();  

  /* ���ú������õ������� */
  GPIO_InitStructure.GPIO_Pin =  BRE_TIM_LED_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init( BRE_TIM_LED_PORT, &GPIO_InitStructure );																			
	
	
	/* ����TIM3CLK ʱ�� */
	BRE_TIM_APBxClock_FUN ( BRE_TIM_CLK, ENABLE ); 
	
	/* ������ʱ������ ,���PWM��������жϷ������е�period_cntѭ����������*/	
	
	/* ����ʹ��������������Ϊ3�����Ҽ��ɴﵽ�ܺõ�Ч�� */	
	
	//Ҫ��
	//TIM_Period����PWM������ֵ��Χһ��
	//TIM_Prescaler��ԽСԽ�ã��ɼ�����˸����
	//PERIOD_CLASS���жϷ������п��Ƶ�����ѭ���Ĵ������������ɿ���������ߵ�����
	//POINT_NUM��PWM���Ԫ�أ�����PWM������ߵĲ�������

	/*************��ʵ���е�����***************/	
	/***********************************************
	#python����ű�	count.py
	#PWM����
	POINT_NUM = 110

	#���ڱ���
	PERIOD_CLASS = 10

	#��ʱ����ʱ����
	TIMER_TIM_Period = 2**10
	#��ʱ����Ƶ
	TIMER_TIM_Prescaler = 200

	#STM32ϵͳʱ��Ƶ�ʺ�����
	f_pclk = 72000000
	t_pclk = 1/f_pclk

	#��ʱ��update�¼�����
	t_timer = t_pclk*TIMER_TIM_Prescaler*TIMER_TIM_Period

	#ÿ��PWM���ʱ��
	T_Point = t_timer * PERIOD_CLASS

	#������������
	T_Up_Down_Cycle = T_Point * POINT_NUM

	print ("�������ڣ�",T_Up_Down_Cycle)
	
	#���н����
	
	�������ڣ�3.12888
	************************************************************/

  /* ������ʱ������ */		  
  TIM_TimeBaseStructure.TIM_Period = (20000-1);;       							  //����ʱ����0������ TIM_Period+1 ��Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = (72-1);	    							//����Ԥ��Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
  TIM_TimeBaseInit(BRE_TIMx, &TIM_TimeBaseStructure);

  /* PWMģʽ���� */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
  TIM_OCInitStructure.TIM_Pulse = 0;				 						  			//���ó�ʼPWM������Ϊ0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ

  BRE_TIM_OCxInit ( BRE_TIMx, &TIM_OCInitStructure );	 									//ʹ��ͨ��
	

  BRE_TIM_OCxPreloadConfig ( BRE_TIMx, TIM_OCPreload_Enable );						//ʹ��Ԥװ��	

  TIM_ARRPreloadConfig(BRE_TIMx, ENABLE);			 										//ʹ��TIM���ؼĴ���ARR

  /* TIM3 enable counter */
  TIM_Cmd(BRE_TIMx, ENABLE);                   										//ʹ�ܶ�ʱ��	
}
