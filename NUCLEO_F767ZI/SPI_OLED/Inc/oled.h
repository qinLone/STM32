#ifndef __OLED_H__
#define __OLED_H__

#include "main.h"


#define     OLED_CS_Set()       HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)
#define     OLED_CS_Clr()       HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)

#define     OLED_DC_Set()       HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET)
#define     OLED_DC_Clr()       HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET)

#define     OLED_RST_Set()      HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET)
#define     OLED_RST_Clr()      HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET)

#define Max_Column	128
#define Max_Row		64

//OLED≥ı ºªØ
void OLED_Init(void);
//OLED«Â∆¡
void OLED_CLS(void);
//OLEDÀ¢∆¡
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_Set_Pos(uint8_t x,uint8_t y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Display_Onechar(uint8_t x,uint8_t y,uint8_t str,uint8_t size);
void OLED_Display_String(uint8_t x,uint8_t y,uint8_t *str,uint8_t size);
void OLED_Display_Chinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
uint32_t OLED_Pow(uint8_t m,uint8_t n);



#endif