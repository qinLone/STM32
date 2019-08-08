#ifndef __HCSR04_H
#define __HCSR04_H

#include "main.h"
#include "tim.h"
#include "usart.h"


void Send_Trig();
uint32_t Get_Time();
float Get_Length();

#endif