#ifndef __NT35510_LCD_H__
#define __NT35510_LCD_H__

#include "main.h"
//RS为A10
//RAM基地址 = 0x6C000000+2^10*2 = 0X60000000 + 0X800 = 0X6C000800
#define DATA_ADDR   0X6C000800   	
#define CMD_ADDR    0x6C000000	 		



//画笔颜色
#define WHITE  			0xFFFF
#define BLACK       0x0000	  
#define BLUE        0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色

extern uint16_t BACK_COLOR;
extern uint16_t DRAW_COLOR;

__inline void LCD_WR_REG ( uint16_t usCmd );
__inline void LCD_WR_DATA ( uint16_t usData );
__inline uint16_t LCD_RD_DATA (void);
static void delay_us(uint32_t us);
static void delay_ms(uint32_t ms);
void NT35510_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t NT35510_ReadReg(uint16_t LCD_Reg);
void LCD_Reset(void);
void Back_Light(int s);
void NT35510_WriteRAM_Prepare(void);
void NT35510_DisplayOn(void);
void NT35510_DisplayOff(void);
void NT35510_SetWindow(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1);
void NT35510_DrawPixel(uint16_t color, uint16_t x, uint16_t y);
void NT35510_Clear(uint16_t color);
uint32_t NT35510_CheckID(void);
void NT35510_Init(void);
void NT35510_FillRect(uint16_t color, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void NT35510_DrawBitmap(uint16_t color[], uint16_t x0, uint16_t y0, uint16_t width, uint16_t height);

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode);
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p);
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);
uint32_t LCD_Pow(uint8_t m,uint8_t n);

#endif



