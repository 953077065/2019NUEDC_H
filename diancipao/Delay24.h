#ifndef __DELAY_H__
#define __DELAY_H__
#include "Dingyi.h"
/*
**************
文件名：延时头文件
创建人：claire
创建日期：2019-8-4
说明：定义各种延时函数
适用芯片: stc8单片机		 
晶振Crystal  : 24Mhz
**************
*/

 void delay_ms( uint n );	//ms延时
 void delay_500ms();		//0.5s延时


void delay_ms( uint n )	//ms延时	(50ms误差0.5ms，delay_ms（50）结果为50.5ms）
{
	uint i,j;
	while(n--)
		for(i=100;i>0;i--)
			for(j=17;j>0;j--);	  
}

void delay_500ms()	//0.5s延时
{
	uint i,j,k;
		for(i=78;i>0;i--)
			for(j=193;j>0;j--)
				for(k=60;k>0;k--);
}


#endif