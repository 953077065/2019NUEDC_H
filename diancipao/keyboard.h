#ifndef _KEY_H_
#define _KEY_H_
#define KEYPORT P1


void delay_ms( uint n )	//msÑÓÊ±	
{
	uint i,j;
	while(n--)
		for(i=100;i>0;i--)
			for(j=17;j>0;j--);	  
}
uchar keyscanner(void){
	static uint  tmp=0xff;
	P1 =0xf0; //µÍ4Î»Êä³ö0£¬¸ß4Î»ÊäÈëÄ£Ê½  
	if(P1!=0xf0)
	{
      tmp=P1;   //1110 0000
			P1=0x0f;  //0000 1111
			delay_ms(185)	;
			tmp|=(P1&0x0f);   
      switch(tmp)  //½«°´¼üÖµ×ª»»ÎªÊý×ÖºÅ
      {
        case 0xee: 				tmp =0;				break;		//1110 1110
				case 0xde: 				tmp =1;				break;//1101 1110	
				case 190:					tmp =2;				break;
				case 126:					tmp =3;				break;
				case 237:					tmp =4;				break;
				case 221:					tmp =5;				break;
				case 189:					tmp =6;				break;
				case 125:					tmp =7;				break;
				case 235:					tmp =8;				break;
        case 219:					tmp =9;       break; 				
				case 187:					tmp =10;			break;
				case 123:					tmp =11;			break;
				case 231:					tmp =12;			break;
				case 215:					tmp =13;			break;
				case 183:					tmp =14; 			break;
				case 119:					tmp =15;			break;
      }			
    }            
  return tmp; //¼üÖµ·µ»Ø
}


#endif