#include "gy25.h"
#include "stdio.h"

uint8_t CMD[2]={0xa5,0x51};
uint8_t RX_STA=0;
uint8_t RX_Buff[8];

uint16_t YAW=0.0;
uint16_t PITCH=0.0;
uint16_t ROLL=0.0;

void Send_CMD() 
{
	HAL_UART_Transmit(&huart1,CMD,sizeof(CMD),1000);
}

void Get_Angle(int t)
{
	HAL_Delay(t);
	Send_CMD();
	HAL_UART_Receive_IT(&huart1,RX_Buff,8);
	if(RX_STA)
	{
		RX_STA=0;
		printf("%f\t",YAW);
		printf("%f\t",PITCH);
		printf("%f\t\n",ROLL);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)
	{
		if(RX_Buff[0]==0xaa)//如果帧头错误，清缓存
		{
			if(RX_Buff[7]==0x55)//判断帧尾，正确则解析姿态角
			{
				HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
				YAW=(RX_Buff[1]<<8|RX_Buff[2]);//YAW，PITCH,ROLL为真实值的100倍
				PITCH=(RX_Buff[3]<<8|RX_Buff[4]);
				ROLL=(RX_Buff[5]<<8|RX_Buff[6]);
				RX_STA=1;
			}
		}
	}
}
