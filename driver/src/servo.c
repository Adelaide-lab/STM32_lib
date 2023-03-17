#include "servo.h"

void Servor_Init(void)
{
		Timer_Init();
}

void Servor_Angler_Set(float angle)
{
		uint16_t f_2_angle = (angle/180)*2000+500;
		TIM_SetCompare2(TIM3, f_2_angle);
}

