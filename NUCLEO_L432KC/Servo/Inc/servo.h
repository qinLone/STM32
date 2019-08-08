#ifndef __SERVO_H__
#define __SERVO_H__

#include "main.h"
#include "tim.h"

void Servo_Init();
void Servo_Control_X(float angle);
void Servo_Control_Y(float angle);
void Pan_Tilt(uint16_t x_angle,uint16_t y_angle);
void Servo_Control_X_PID(float PWM_Duty);
void Servo_Control_PID(float PWM_Duty);
void Pan_Tilt_PID(float X_PWM_Duty,float Y_PWM_Duty);
#endif