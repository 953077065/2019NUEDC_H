#ifndef _LCD_H_
#define _LCD_H_
#define Lcd1602_DATA P0//8位数据口
#include <Dingyi.h>
sbit Lcd1602_E=P3^7;//使能端
sbit Lcd1602_RS=P3^5;//指令or数据
sbit Lcd1602_RW=P3^6;//写入or读出
sbit Lcd1602_Busy=Lcd1602_DATA^7;
 
/*****************Lcd1602.h**************/
/*****************可用函数***************/
/************编写于2018/08/18************/
/**************作者：Belous**************/
/*******测试应用与STC89C516——12MHZ*******/
void Lcd1602_Init(void);//初始化Lcd1602
void Lcd1602_WriteDC(uchar com,uchar control);
//向Lcd1602写入指令或数据，control=0指令，control=1数据;
//进行数据写入操作后，光标会按预设左移或右移
//uchar Lcd1602_ReadDC(uchar control);
//从Lcd1602读出状态或数据，control=0状态，control=1数据
//读取状态，D7是读写检测端、D0-D6为当前数据指针的数值
//读取数据，返回当前数据指针处字节，不会改变数据指针，须自行移位
void Lcd1602_Firstrow(void);//调整位置-第一行
void Lcd1602_Secondrow(void);//调整位置-第二行——！须确保开启两行模式！
//void Lcd1602_MoveSP(uchar sp);//改变数据指针为指定数值
/****************************************/
 
void Lcd1602_Init(void)
{
	//所有指令
	Lcd1602_WriteDC(0x38,0);//2行和5*7矩阵（数据总线8位）
	//Lcd1602_WriteDC(0x30,0);//1行和5*7矩阵（数据总线8位）
	//Lcd1602_WriteDC(0x3C,0);//2行和5*10矩阵（数据总线8位）
	//Lcd1602_WriteDC(0x34,0);//1行和5*10矩阵（数据总线8位）
	Lcd1602_WriteDC(0x01,0);//清除显示屏幕
	//Lcd1602_WriteDC(0x02,0);//归起始位
	//Lcd1602_WriteDC(0x04,0);//光标左移
	//Lcd1602_WriteDC(0x06,0);//光标右移
	//Lcd1602_WriteDC(0x05,0);//显示右移
	//Lcd1602_WriteDC(0x07,0);//显示左移
	//Lcd1602_WriteDC(0x08,0);//显示关，光标关
	//Lcd1602_WriteDC(0x0A,0);//显示关，光标开
	Lcd1602_WriteDC(0x0C,0);//显示开，光标关
	//Lcd1602_WriteDC(0x0E,0);//显示开，光标闪
	//Lcd1602_WriteDC(0x10,0);//光标位置左移
	//Lcd1602_WriteDC(0x14,0);//光标位置右移
	//Lcd1602_WriteDC(0x18,0);//整个显示左移
	//Lcd1602_WriteDC(0x1C,0);//整个显示右移
	Lcd1602_WriteDC(0x80,0);//使光标到第一行起点
	//Lcd1602_WriteDC(0xC0,0);//使光标到第二行起点
}
void Lcd1602_Delay(uint c)//1602延迟1us，测试通过于24MHZ
{
	
	while (--c);

}


void Lcd1602_Ready(void)
{
	Lcd1602_Busy=1;//使输入
	Lcd1602_RS=0;//命令
	Lcd1602_RW=1;//读出
	Lcd1602_E=1;
	while(Lcd1602_Busy)
	{
		Lcd1602_E=0;
		Lcd1602_Delay(1);
		Lcd1602_E=1;
	}
	return;
}
void Lcd1602_WriteDC(uchar com,uchar control)
{
	Lcd1602_Ready();
	if(control)
		Lcd1602_RS=1;//数据
	else
		Lcd1602_RS=0;//命令
	Lcd1602_RW = 0;//写入
	Lcd1602_DATA = com;
	Lcd1602_Delay(5);
	Lcd1602_E = 1;
	Lcd1602_Delay(1);
	Lcd1602_E = 0;//Lcd得到信息
}
/*uchar Lcd1602_ReadDC(uchar control)
{
	Lcd1602_DATA=0xFF;//I/0口至输入模式
	Lcd1602_Ready();
	if(control)
		Lcd1602_RS = 1;//读取数据
	else
		Lcd1602_RS = 0;//读取状态
	Lcd1602_RW = 1;
	Lcd1602_Delay(1);
	Lcd1602_E = 1;
	return Lcd1602_DATA;
}*/
void Lcd1602_Firstrow(void)
{
	Lcd1602_WriteDC(0x80,0);//使光标到第一行起点
	return;
}
void Lcd1602_Secondrow(void)
{
	//Lcd1602_WriteDC(0x38,0);//确保可以显示第二行
	Lcd1602_WriteDC(0xC0,0);//使光标到第二行起点
	return;
}
/*void Lcd1602_MoveSP(uchar sp)
{
	Lcd1602_WriteDC(sp+0x80,0);
	return;
}*/
#endif