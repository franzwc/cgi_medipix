/*CGI FILE
--------------------------------------------------------------------------------
--!@brief Init Medipix
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Inicializa o Medipix com os parametros gravados anteriormente
--!
--! DETAILS:      le os dados gravados e aplica 
--!               
--!
--!- Project Name: init_medipix
--!- Module Name: init_medipix.c
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: /1/2015     
--!- Version: 1.0.0 (jan/2015) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2015
--------------------------------------------------------------------------------
Header*/
#include <stdio.h>
#include <stdlib.h>
#define IORD(address,offset)		(*(volatile unsigned *)(((address)|0x80000000)+4*(offset)))
#define IOWR(address,offset,value)	(*(volatile unsigned *)(((address)|0x80000000)+4*(offset)))=(value)

int main()
{
	
	
	IOWR(0x08000060,0x2,111);
	usleep(10000000);
	IOWR(0x08000060,0x2,000);
	usleep(10000000);
	IOWR(0x08000060,0x3,111);
	usleep(10000000);
	printf("\nInit Complete!!!\n");
	return 0;
}


