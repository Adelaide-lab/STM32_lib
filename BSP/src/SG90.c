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

  /* 配置呼吸灯用到的引脚 */
  GPIO_InitStructure.GPIO_Pin =  BRE_TIM_LED_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init( BRE_TIM_LED_PORT, &GPIO_InitStructure );																			
	
	
	/* 设置TIM3CLK 时钟 */
	BRE_TIM_APBxClock_FUN ( BRE_TIM_CLK, ENABLE ); 
	
	/* 基本定时器配置 ,配合PWM表点数、中断服务函数中的period_cnt循环次数设置*/	
	
	/* 设置使得整个呼吸过程为3秒左右即可达到很好的效果 */	
	
	//要求：
	//TIM_Period：与PWM表中数值范围一致
	//TIM_Prescaler：越小越好，可减轻闪烁现象
	//PERIOD_CLASS：中断服务函数中控制单个点循环的次数，调整它可控制拟合曲线的周期
	//POINT_NUM：PWM表的元素，它是PWM拟合曲线的采样点数

	/*************本实验中的配置***************/	
	/***********************************************
	#python计算脚本	count.py
	#PWM点数
	POINT_NUM = 110

	#周期倍数
	PERIOD_CLASS = 10

	#定时器定时周期
	TIMER_TIM_Period = 2**10
	#定时器分频
	TIMER_TIM_Prescaler = 200

	#STM32系统时钟频率和周期
	f_pclk = 72000000
	t_pclk = 1/f_pclk

	#定时器update事件周期
	t_timer = t_pclk*TIMER_TIM_Prescaler*TIMER_TIM_Period

	#每个PWM点的时间
	T_Point = t_timer * PERIOD_CLASS

	#整个呼吸周期
	T_Up_Down_Cycle = T_Point * POINT_NUM

	print ("呼吸周期：",T_Up_Down_Cycle)
	
	#运行结果：
	
	呼吸周期：3.12888
	************************************************************/

  /* 基本定时器配置 */		  
  TIM_TimeBaseStructure.TIM_Period = (20000-1);;       							  //当定时器从0计数到 TIM_Period+1 ，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = (72-1);	    							//设置预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//设置时钟分频系数：不分频(这里用不到)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//向上计数模式
  TIM_TimeBaseInit(BRE_TIMx, &TIM_TimeBaseStructure);

  /* PWM模式配置 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
  TIM_OCInitStructure.TIM_Pulse = 0;				 						  			//设置初始PWM脉冲宽度为0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //当定时器计数值小于CCR1_Val时为低电平

  BRE_TIM_OCxInit ( BRE_TIMx, &TIM_OCInitStructure );	 									//使能通道
	

  BRE_TIM_OCxPreloadConfig ( BRE_TIMx, TIM_OCPreload_Enable );						//使能预装载	

  TIM_ARRPreloadConfig(BRE_TIMx, ENABLE);			 										//使能TIM重载寄存器ARR

  /* TIM3 enable counter */
  TIM_Cmd(BRE_TIMx, ENABLE);                   										//使能定时器	
}
