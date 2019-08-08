#ifndef __GY25_H
#define __GY25_H

#include "usart.h"
#include "main.h"


void GY25_Init();
void Send_CMD();
void Get_Angle(int t);

#endif