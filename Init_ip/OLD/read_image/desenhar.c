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
#include "cgivars.h"
#include "htmllib.h"
#include "ler.h"

int template_page(char **postvars, char **getvars, int form_method) 
{	
	char callback[280];
	int i=0;
	int write_flag = FALSE;
	char* nlinha;
	int linha_n;

	if(form_method == GET)
    {
		for (i = 0; getvars[i]; i += 2)
		{
			/// Main
			if (strncmp(getvars[i], "linha",16)==0)
			{
            	strncpy(nlinha, getvars[i+1],16);
			    linha_n=atoi(nlinha);
			    if(response_callback(&callback,linha_n)==0)
				{
					printf("%s",callback);
				}
			}
		}
	}
	return 0;
}


int response_callback(char *buffer, int linha_n)
{
	if(buffer == NULL)
	{
		return -1;
	}

	char linha[257];

    read_image(IMAGE_FILE, linha, linha_n);

    snprintf(buffer,280,"!#mac=%s!#",&linha);

	return 0;	
}

int error_callback(char *msg)
{
	if(msg == NULL)
	{
		return -1;
	}
	printf("!#ERROR=%s!#",msg);
	return 0;
}

int success_callback(char *msg)
{
	if(msg == NULL)
	{
		return -1;
	}
	printf("!#SUCCESS=%s!#",msg);
	return 0;
}

int debug_callback(char *option,char *msg)
{
	if(msg == NULL)
	{
		return -1;
	}
	printf("!#DEBUG=%s : %s!#",option,msg);
	return 0;
}
