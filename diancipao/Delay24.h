#ifndef __DELAY_H__
#define __DELAY_H__
#include "Dingyi.h"
/*
**************
�ļ�������ʱͷ�ļ�
�����ˣ�claire
�������ڣ�2019-8-4
˵�������������ʱ����
����оƬ: stc8��Ƭ��		 
����Crystal  : 24Mhz
**************
*/

 void delay_ms( uint n );	//ms��ʱ
 void delay_500ms();		//0.5s��ʱ


void delay_ms( uint n )	//ms��ʱ	(50ms���0.5ms��delay_ms��50�����Ϊ50.5ms��
{
	uint i,j;
	while(n--)
		for(i=100;i>0;i--)
			for(j=17;j>0;j--);	  
}

void delay_500ms()	//0.5s��ʱ
{
	uint i,j,k;
		for(i=78;i>0;i--)
			for(j=193;j>0;j--)
				for(k=60;k>0;k--);
}


#endif