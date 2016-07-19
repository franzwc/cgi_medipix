#include<stdio.h>
#include<stdlib.h>
#include"global.h"

int main(void)
{
	unsigned int LFSR12bits[4096];
	unsigned int LFSR=0;
    unsigned int b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,newb0;
	int i;
    for (i=0;i<4096;i++)
    {
        LFSR12bits[i]=LFSR;
        b0=LFSR & 1;
        b1=(LFSR>>1) & 1;
        b2=(LFSR>>2) & 1;
        b3=(LFSR>>3) & 1;
        b4=(LFSR>>4) & 1;
        b5=(LFSR>>5) & 1;
        b6=(LFSR>>6) & 1;
        b7=(LFSR>>7) & 1;
        b8=(LFSR>>8) & 1;
        b9=(LFSR>>9) & 1;
        b10=(LFSR>>10) & 1;
        b11=(LFSR>>11) & 1;
        newb0=(!(b0|b1|b2|b3|b4|b5|b6|b7|b8|b9|b10))^b0^b3^b5^b11;
        b11=b10;
        b10=b9;
        b9=b8;
        b8=b7;
        b7=b6;
        b6=b5;
        b5=b4;
        b4=b3;
        b3=b2;
        b2=b1;
        b1=b0;
        b0=newb0;
        LFSR=b0|(b1<<1)|(b2<<2)|(b3<<3)|(b4<<4)|(b5<<5)|(b6<<6)|(b7<<7)|(b8<<8)|(b9<<9)|(b10<<10)|(b11<<11);
    }
	int a;
	for(a=0;a<4096;a++)
	{
		printf("%d\n",LFSR12bits[a]);
	}
    return 0;
}


