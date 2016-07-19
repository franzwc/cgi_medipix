/*MAIN FILE
--------------------------------------------------------------------------------
--!@brief Listen_UDP_port.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Programa que abre uma porta UDP e aguarda chegada de pacotes e grava em 
--! arquivo texto
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
-- ENTRADAS => numero de bits de aquisicao, numero de imagens , nome e caminho pra salvar sem o .dat
*/
#include<stdio.h>
#include<string.h>
#include"global.h"

int main(int argc, char *argv[])
{

	int contador;
	int ibit;

	Generate6BitTable();

	for(ibit=0;ibit<=63;ibit++)
	{
		fprintf(stderr,"%d %d\n",ibit,LFSR6bits[ibit]);
					
	}

	printf("enjoy!\n\n");
    return 0;
}

