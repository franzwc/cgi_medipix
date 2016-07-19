/*MAIN FILE
--------------------------------------------------------------------------------
--!@brief Listen_UDP_port.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Programa que abre uma porta UDP e escuta aguar
--!
--! DETAILS:      
--!
--!- Project Name: Listen_UDP_port
--!- Module Name: Listen_UDP_port.c
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 08/05/2014     
--!- Version: 1.0.0 (mai/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/global.h"
#include "../utils/reg.h"


/**
 * Ansi C "itoa":
 */
void strreverse(char* begin, char* end) 
{
	char aux;
	while(end>begin)
		aux=*end, *end--=*begin, *begin++=aux;
}
	
void itoa(int value, char* str, int base) 
{
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char* wstr=str;
	int sign;
	
	// Validate base
	if (base<2 || base>35){ *wstr='\0'; return; }
	// Take care of sign
	if ((sign=value) < 0) value = -value;
	// Conversion. Number is reversed.
	do *wstr++ = num[value%base]; while(value/=base);
	if(sign<0) *wstr++='-';
	*wstr='\0';
	// Reverse string
	strreverse(str,wstr-1);
	
}


int main(void) {	
		
	equalization_t* eq_entrada[1030];
	char eq[1030];
	int i;
	char valor;

	//memset(&eq_entrada, 0x31, sizeof(eq_entrada));
	
	for(i=0;i<=1023;i++)
	{
		itoa(i,&valor,10);
		//memset(&eq_entrada[i]->pixel, valor, sizeof(eq_entrada[i].pixel));
		strcpy(&eq_entrada[i]->pixel, &valor);
		//fprintf(stderr,"\n%d",i);
		//fprintf(stderr,"\n%s",&eq_entrada[i]);
	}
	
	fprintf(stderr,"\n%s",eq_entrada[0]->pixel);
    //for(i=0;i<=3;i++)
	//{
		//write_equalization_device(eq_entrada);
	//}
	return 0;
}


