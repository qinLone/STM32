#include "hcsr04.h"
#include "stdio.h"

uint16_t count=0;

void Send_Trig()
{
	HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_RESET);
}

uint32_t Get_Time()
{
	uint32_t time=0;
	time=count*1000;
	time+=__HAL_TIM_GET_COUNTER(&htim6);
	__HAL_TIM_SetCounter(&htim6,0);
	count=0;
	return time;
}

float Get_Length()
{ 
	uint32_t time;
	float lengthTemp=0.0;
	Send_Trig();
	while(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin)==RESET);
	HAL_TIM_Base_Start_IT(&htim6);
	while(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin)==SET);
	HAL_TIM_Base_Stop_IT(&htim6);
	time=Get_Time();
	lengthTemp =(float)time*170/20000; //厘米  
	if(lengthTemp>400)
	{
		printf("超出测量范围，不准确");
		lengthTemp=400;
	}
	return lengthTemp;
	
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (htim->Instance == TIM6)
	{
		count++;
	}
}