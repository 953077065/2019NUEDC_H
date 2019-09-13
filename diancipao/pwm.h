#ifndef _PWM_H__
#define _PWM_H__
#include <stc8.h>
#include <Dingyi.h>

/*void pwm_init(void)
{
	P_SW2=0x80;    //B7=1——PWM模式，pwm相关寄存器使能
		
	/*16分频，1.5MHz*/
//	PWMCKS=0x0F; //16分频 1.5MHz 30000
//	PWMC=30000; //计数器寄存器，设置周期为20ms ，周期数为30000
//	/*水平*/
//	PWM0T1=750; //初值：1ms ---45度 PWM0 左右
//	PWM0T2=29250;  //7530-02ee
//	/*垂直*/
//	PWM1T1=550; //初值：375  ---12度 PWM1 上下
//	PWM1T2=29450;  //29625
//	
//	PWM0CR=0xC0; //B7=1————pwm为输出口，B6=1——初始为高电平
//	PWM1CR=0xC0; //B7=1————pwm为输出口，B6=1——初始为高电平			
//	
//	P_SW2=0x00;  
//	PWMCR=0x80;  //B7=1————PWM使能
//}*/
void horizontal_change(int angle)
{
	uint remain_h=0;
	P_SW2=0x80;    //B7=1——PWM模式，pwm相关寄存器使能
		
	/*16分频，1.5MHz*/
	PWMCKS=0x0F; //16分频 1.5MHz 30000
	PWMC=30000; //计数器寄存器，设置周期为20ms ，周期数为30000
	/*水平*/
	PWM0T1=750; //初值：1ms ---45度 PWM0 左右
	PWM0T2=29250;  //7530-02ee
	
	PWM0CR=0xC0; //B7=1————pwm为输出口，B6=1——初始为高电平
		
	P_SW2=0x00;  
	PWMCR=0x80;  //B7=1————PWM使能
	if(angle<=30 && angle>=-30)
	{
		angle=angle+45-9;
		remain_h=angle*8+375+(angle/3);
		P_SW2=0x80;
		PWM0T1=remain_h;
		PWM0T2=PWM0T2-remain_h;	
		P_SW2=0x00; 
	}
}
void vertical_change(int angle)
{
	uint remain_h=0;
		angle+=20;
	P_SW2=0x80;    //B7=1——PWM模式，pwm相关寄存器使能
		
	/*16分频，1.5MHz*/
	PWMCKS=0x0F; //16分频 1.5MHz 30000
	PWMC=30000; //计数器寄存器，设置周期为20ms ，周期数为30000
	
	/*垂直*/
	PWM1T1=550; //初值：375  ---12度 PWM1 上下
	PWM1T2=29450;  //29625
	
	PWM1CR=0xC0; //B7=1————pwm为输出口，B6=1——初始为高电平			
	
	P_SW2=0x00;  
	PWMCR=0x80;  //B7=1————PWM使能
	if(angle>=20 && angle<=110)
	{
		remain_h=angle*8+375+(angle/3);
		P_SW2=0x80;
		PWM1T1=remain_h;
		PWM1T2=PWM1T2-remain_h;	
		P_SW2=0x00;
	}
}
#endif