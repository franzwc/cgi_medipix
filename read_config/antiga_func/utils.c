/*C FILE
--------------------------------------------------------------------------------
--!@brief utils.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Funcoes importantes
--!
--! DETAILS:      
--!
--!- Project Name: utils
--!- Module Name: utils.c
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 08/05/2014     
--!- Version: 1.0.0 (mai/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define BASE 2
#define DIGITS 4

char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';
    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }
    return b;
}

void strreverse(char* begin, char* end) 
{
	char aux[8],aux2[8];
	int a=0,b=7;
	for(a=0;a<=7;a++)
	{
		strcpy(&aux[a],&begin[b]);
		b--;
	}
	strncpy(aux2,aux,5);
	b=4;	
	for(a=0;a<=4;a++)
	{
		strcpy(&end[a],&aux2[b]);
		b--;
	}
}


