#include <stc8.h>
#include <Lcd1602.h>
#include <keyboard.h>
#include <Dingyi.h>
#include <pwm.h>
#include <math.h>

//距离控制   key10——s11
int CONFIGMODE=0;	//自动设置模式  0-距离	1-角度 默认调整距离
//角度，key11——s12 
//发射 	key12——s13
//双舵机控制，key13——s14 
//自动打靶，key14——s15 
int SYSMODE=0; //默认舵机手动调整模式 0——手动，1-自动，2-自动+ 3-DEBUG模式
int V=0;					//垂直舵机角度控制——P21
int H=0;					//水平舵机角度控制——P20
int D=0;					//发射距离 单位DM 默认0s
int DEBUG=0;			//debug模式手动调整舵机旋转角度	默认0	
int CUE=0;//当前修改的参数 0-D 1-H 2-V 默认0
sbit BEEP=P5^5;		//蜂鸣器 	P55
sbit LAUNCH=P5^4;	//发射		P56 低电平触发

code uchar array1[]	="=WELCOME TO USE=";
code uchar array2[]	="   LOADING...   ";
code uchar ready[] 	="  READY ";
code uchar finish[]	="LAUNCH FINISHED!";
code uchar debugcode[]	="TESTMODE";
void scanX();
void scanX2();
void Delay500ms()		//@24.000MHz
{
	uchar i, j, k;
	i = 61;	j = 225;	k = 62;
	do	{
		do		{
			while (--k);		} 
		while (--j);	} 
	while (--i);
}
void Delay100ms()		//@24.000MHz
{
	unsigned char i, j, k;

	i = 13;
	j = 45;
	k = 214;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void fire(){	//发射按钮  
	uchar i;
	if(DEBUG){
		LAUNCH=0;
		delay_ms(150);
		LAUNCH=1;
		Lcd1602_Firstrow();
		for(i=0;finish[i];i++)
			Lcd1602_WriteDC(finish[i],1);
		BEEP=0;
		delay_ms(500);
		BEEP=1;
	}else{
		if(SYSMODE==0){
		
		}else if(SYSMODE==1){
			scanX();
		}else if(SYSMODE==2){
			scanX2();
		}
	}
	return;
}
void numberKey(int i){
	if(CUE==0){	//修改D的值
		if(D>30) D=0;
		if(D!=0) D=D*10+i;
		else D=i;
	}
	if(CUE==1){	//修改H的值
		if(H>30||H<-30) H=0;
		if(H!=0) H=H*10+i;
		else H=i;
	}
	if(CUE==2){	//修改V的值
		if(V>60) V=0;
		if(V!=0) V=V*10+i;
		else V=i;
	}
}
void key10(){
	CUE=0;
}
void key11(){
	CUE=1;
}
void key12(){
	fire();
}
void key13(){
	CUE=2;
}

void key14(){	//修改工作模式
	if(SYSMODE==2) SYSMODE=0;
	else SYSMODE++;
}
void key15(){	//负号 只针对水平角度调节 
	if(CUE==1)	//当前修改的是H的值
		H*=-1;
	else DEBUG=!DEBUG;
}
void scanX(){
	int i=-30;
	V=10;
	while(i<=28){
			Delay500ms();
			horizontal_change(i+=2);
	}
	//i=30;
	while(i>=-28){
		Delay500ms();
			horizontal_change(i-=2);
	}
	
}
void scanX2(){
	int i=-30;
	V=10;
	while(i<=28){
			Delay100ms();
			horizontal_change(i++);
	}
	while(i>=-28){
		Delay100ms();
			horizontal_change(i--);
	}
	
}
void main(void)
{
	uchar i;
	V=0;					//垂直舵机角度控制——P21
	H=0;					//水平舵机角度控制——P20
	D=0;
	BEEP=1;
	LAUNCH=1;
	//pwm_init();
	Lcd1602_Init();
	
	for(i=0;array1[i];i++)
		Lcd1602_WriteDC(array1[i],1);
	Lcd1602_Secondrow();
	for(i=0;array2[i];i++)
		Lcd1602_WriteDC(array2[i],1);
	Delay500ms();
	
	
	while(1){
		
		Lcd1602_Firstrow();
		Lcd1602_WriteDC('M',1);
		Lcd1602_WriteDC('O',1);
		Lcd1602_WriteDC('D',1);
		Lcd1602_WriteDC('E',1);
		Lcd1602_WriteDC(':',1);
		if(SYSMODE==0) {Lcd1602_WriteDC('M',1);Lcd1602_WriteDC(' ',1);Lcd1602_WriteDC(' ',1);}
		else if(SYSMODE==1){Lcd1602_WriteDC('A',1);Lcd1602_WriteDC(' ',1);Lcd1602_WriteDC(' ',1);}
		else if(SYSMODE==2){Lcd1602_WriteDC('A',1);Lcd1602_WriteDC('+',1);Lcd1602_WriteDC(' ',1);}
		if(!DEBUG){
		for(i=0;ready[i];i++)
		Lcd1602_WriteDC(ready[i],1);
		}else{
			for(i=0;debugcode[i];i++)
			Lcd1602_WriteDC(debugcode[i],1);
		}
		Lcd1602_Secondrow();
		Lcd1602_WriteDC('D',1);
		Lcd1602_WriteDC(':',1);
		Lcd1602_WriteDC(D/10+'0',1);
		Lcd1602_WriteDC(D%10+'0',1);
		Lcd1602_WriteDC(' ',1);
		Lcd1602_WriteDC('H',1);
		Lcd1602_WriteDC(':',1);
		if(H<0 && H>=-30){
			Lcd1602_WriteDC('-',1);
			Lcd1602_WriteDC(abs(H)/10+'0',1);
			Lcd1602_WriteDC(abs(H)%10+'0',1);
			Lcd1602_WriteDC(' ',1);
		}
		if(H>=0 && H<=30){
			Lcd1602_WriteDC('+',1);
			Lcd1602_WriteDC(H/10+'0',1);
			Lcd1602_WriteDC(H%10+'0',1);
			Lcd1602_WriteDC(' ',1);
		}
		Lcd1602_WriteDC('V',1);
		Lcd1602_WriteDC(':',1);
		Lcd1602_WriteDC(V/10+'0',1);
		Lcd1602_WriteDC(V%10+'0',1);
		Lcd1602_WriteDC(' ',1);
		switch(keyscanner()){
					case 0:				numberKey(0);				break;
					case 1:				numberKey(1);				break;
					case 2:				numberKey(2);				break;			
					case 3:				numberKey(3);				break;
					case 4:				numberKey(4);				break;
					case 5:				numberKey(5);				break;
					case 6:				numberKey(6);				break;
					case 7:				numberKey(7);				break;
					case 8:				numberKey(8);				break;
					case 9:				numberKey(9);				break;
					case 10:			key10();				break; 		//
					case 11:			key11();				break;  	//
					case 12:			key12();				break;
					case 13:			key13();				break;
					case 14:			key14();				break;  	//
					case 15:			key15();				break;  	 //
			}
		
			switch(D){
				case 20:V=12;break;
				case 21:V=14;break;
				case 22:V=15;break;
				case 23:V=16;break;
				case 24:V=17;break;
				case 25:V=20;break;
				case 26:V=22;break;
				case 27:V=26;break;
				case 28:V=28;break;
				case 29:V=31;break;
				case 30:V=33;break;		
				default:V=0;break;
			}
		vertical_change(V);  //调整垂直舵机
		horizontal_change(H);//调整水平舵机
		delay_ms(100);
		}
return;
}
