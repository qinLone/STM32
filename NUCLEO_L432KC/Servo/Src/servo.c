#include "servo.h"

//X轴：TIM2->CH1 
//Y轴：TIM2->CH2
void Servo_Init()
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
}

void Servo_Control_X(float angle)
{
	float temp;
	if(angle<0)
		angle=0;
	if(angle>270)
		angle=270;
	temp=19.0/270.0*angle+5.0;
	TIM2->CCR1=temp;
}

void Servo_Control_Y(float angle)
{
	float temp;
	if(angle<0)
		angle=0;
	if(angle>180)
		angle=180;
	temp=11.0/180.0*angle+6.0;
	TIM2->CCR2=temp;
}

void Pan_Tilt(uint16_t x_angle,uint16_t y_angle)
{
	Servo_Control_X(x_angle);
	Servo_Control_Y(y_angle);
}

//以下用于PID直接输入占空比控制
void Servo_Control_X_PID(float PWM_Duty)
{
	if(PWM_Duty<5)
		PWM_Duty=5;
	if(PWM_Duty>25)
		PWM_Duty=25;
	TIM2->CCR1=PWM_Duty;
}

void Servo_Control_PID(float PWM_Duty)
{
	if(PWM_Duty<6)
		PWM_Duty=6;
	if(PWM_Duty>17)
		PWM_Duty=17;
	TIM2->CCR2=PWM_Duty;
}

void Pan_Tilt_PID(float X_PWM_Duty,float Y_PWM_Duty)
{
	Servo_Control_X_PID(X_PWM_Duty);
	Servo_Control_PID(Y_PWM_Duty);
}