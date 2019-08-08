#include "oled.h"
#include "spi.h"
#include "font.h"

uint8_t OLED_GRAM [128][8];	

void OLED_Write_Byte(uint8_t dat)
{
	HAL_SPI_Transmit(&hspi1,&dat,1,1000);
}

//写入数据
void OLED_Write_Data(uint8_t dat)
{
	OLED_CS_Clr();
	OLED_DC_Set();
	OLED_Write_Byte(dat);
}

//写入命令
void OLED_Write_Cmd(uint8_t cmd)
{
	OLED_CS_Clr();
	OLED_DC_Clr();
	OLED_Write_Byte(cmd);
}

void OLED_Refresh_Gram(void)
{
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_Write_Cmd(0xb0+i);    //设置页地址（0~7）
		OLED_Write_Cmd(0x00);      //设置显示位置—列低地址
		OLED_Write_Cmd(0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++) 
		OLED_Write_Data(OLED_GRAM[n][i]); 
	}   
}


void OLED_Init(void)
{
	OLED_RST_Clr();
	HAL_Delay(100);
	OLED_RST_Set();
	
	OLED_Write_Cmd(0xAE); //display off
	OLED_Write_Cmd(0x20);	//Set Memory Addressing Mode	
	OLED_Write_Cmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	OLED_Write_Cmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	OLED_Write_Cmd(0xc8);	//Set COM Output Scan Direction
	OLED_Write_Cmd(0x00); //---set low column address
	OLED_Write_Cmd(0x10); //---set high column address
	OLED_Write_Cmd(0x40); //--set start line address
	OLED_Write_Cmd(0x81); //--set contrast control register
	OLED_Write_Cmd(0xff); //亮度调节 0x00~0xff
	OLED_Write_Cmd(0xa1); //--set segment re-map 0 to 127
	OLED_Write_Cmd(0xa6); //--set normal display
	OLED_Write_Cmd(0xa8); //--set multiplex ratio(1 to 64)
	OLED_Write_Cmd(0x3F); //
	OLED_Write_Cmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_Write_Cmd(0xd3); //-set display offset
	OLED_Write_Cmd(0x00); //-not offset
	OLED_Write_Cmd(0xd5); //--set display clock divide ratio/oscillator frequency
	OLED_Write_Cmd(0xf0); //--set divide ratio
	OLED_Write_Cmd(0xd9); //--set pre-charge period
	OLED_Write_Cmd(0x22); //
	OLED_Write_Cmd(0xda); //--set com pins hardware configuration
	OLED_Write_Cmd(0x12);
	OLED_Write_Cmd(0xdb); //--set vcomh
	OLED_Write_Cmd(0x20); //0x20,0.77xVcc
	OLED_Write_Cmd(0x8d); //--set DC-DC enable
	OLED_Write_Cmd(0x14); //
	OLED_Write_Cmd(0xaf); //--turn on oled panel
	OLED_CLS();
}


//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空				   
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t)
{
	uint8_t pos,bx,temp=0;
	if(x>127||y>63)return;
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}

/**********************写满屏数据**********************/
//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,清空;1,填充	  
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot)  
{  
	uint8_t x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)
			OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();
}


/*********************清屏函数***********************/
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_CLS(void)
{	
	OLED_Fill(0,0,127,63, 0x00);
	HAL_Delay(200);
}


//Function:开启OLED显示
//Input:无
//Output:无
//Return:无
//Others:无
void OLED_Display_On(void)
{
	OLED_Write_Cmd(0X8D);//设置DCDC
	OLED_Write_Cmd(0X14);//打开DCDC
	OLED_Write_Cmd(0XAF);//打开OLED
}

//Function:关闭OLED显示
//Input:无
//Output:无
//Return:无
//Others:无
void OLED_Display_Off(void)
{
	OLED_Write_Cmd(0X8D);//设置DCDC
	OLED_Write_Cmd(0X10);//关闭DCDC
	OLED_Write_Cmd(0XAE);//关闭OLED
}


void OLED_Set_Pos(uint8_t x,uint8_t y)
{
	OLED_Write_Cmd(0xb0+y);//列偏移
	OLED_Write_Cmd(((x&0xf0)>>4)|0x10);//行高四位地址
	OLED_Write_Cmd((x&0x0f)|0X01);//行低四位地址
}

void OLED_Display_Onechar(uint8_t x,uint8_t y,uint8_t str,uint8_t size)
{
	uint8_t i=0,ret=0;
	//ret = str -32;
	ret = str - ' ';//得到偏移后的值,对ASCLL码进行一个减法.即在二维数组里找它的位置  
	if(x>Max_Column-1)
	{
		x = 0;
		y = y + 2;//针对16号的字符
	}
	if(size == 2 )
	{
		OLED_Set_Pos(x,y);
		//16的字体分成两部分写入
		for(i=0;i<8;i++)
		OLED_Write_Data(F8X16[ret*16+i]);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
			OLED_Write_Data(F8X16[ret*16+i+8]);
	}
	else{
		OLED_Set_Pos(x,y+1);
		for(i=0;i<6;i++)
			OLED_Write_Data(F6x8[ret][i]);
	}
}

//Function:显示字符串
//Input:x：横坐标;y:纵坐标;str:显示的字符串
//Output:无
//Return:无
//Others:无
void OLED_Display_String(uint8_t x,uint8_t y,uint8_t *str,uint8_t size)
{
	uint8_t i=0;
	
	while(str[i]!='\0')
	{
		OLED_Display_Onechar(x,y,str[i],size);
		x += 8;
		if(x>120)
		{
			x = 0;
			y += 2;
		}
		i++;
	}
}

//Function:显示中文
//Input:x：横坐标;y:纵坐标;no:显示的字的序号
//Output:无
//Return:无
//Others:无
void OLED_Display_Chinese(uint8_t x,uint8_t y,uint8_t no)
{
	uint8_t ch,addr=0;
	
	OLED_Set_Pos(x,y);
	for(ch=0;ch<16;ch++)//数组行列寻址
	{
		OLED_Write_Data(CN[2*no][ch]);//汉字是2个字节
		addr += 1;
	}
	OLED_Set_Pos(x,y+1);
	for(ch=0;ch<16;ch++)
	{
		OLED_Write_Data(CN[2*no+1][ch]);
		addr += 1;
	}
	
}

//Function:显示图片
//Input:x0,x1：横坐标;y0,y1:纵坐标;BMP:显示的图片
//注意：y1<8,页寻址模式
//Output:无
//Return:无
//Others:无
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
		{
			OLED_Write_Data(BMP[j++]);
		}
	}
}


//void OledDispPicture(uint8_t x,uint8_t y,uint8_t width,u16 fontlen,const uint8_t *picture)
//{
//	 uint8_t i,j,pagenum,addyl,addyh;

//	 /*计算显示图像需要的参数*/
//	 pagenum=fontlen/width;							//计算图像使用的页面数量
//	 addyl=y%16;									//计算起始列低地址
//	 addyh=y/16+0x10;									//计算起始列搞地质

//	 /*显示图像*/
//	 for(i=0;i<pagenum;i++)
//	 {
//		OLED_WR_Byte(0xb0+x+i,OLED_CMD);			//设置页地址
//		OLED_WR_Byte(addyl,OLED_CMD);				//设置列低地址
//		OLED_WR_Byte(addyh,OLED_CMD);				//设置列高地址
//		for(j=0;j<width;j++)
//		{
//			OLED_Write_Data(*(picture++));	
//		}	
//	 }
//}

//计算m的n次方
uint32_t OLED_Pow(uint8_t m,uint8_t n)
{
	uint32_t ret = 1;
	while(n--)
		ret *= m;
	return ret;
}

