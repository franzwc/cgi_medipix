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
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MASK_BIT_FILE "ajustes_por_pixel/maskbit"
#define TEST_BIT_FILE "ajustes_por_pixel/testbit"
#define THADJ_H_FILE "ajustes_por_pixel/ThAdjustmentH"
#define EQ_ARQUIVO "/home/franz/altera/Interface/cgi_medipix/send_eq_udp/equalize.dat"

int main(void)
{
	char matrix[327680];
	char test_bits[65536];
	char mask_bits[65536];
	char threshold_high[196865];
	char all_bits[786433];
	int tamanho;
	int line=0;
	int conta=0;
	int i=0,j=0;

	// lendo arquivo mask bit
	read_file(MASK_BIT_FILE,matrix,131328);	
	cast_mask_test_bit(matrix,mask_bits);
	memset(matrix,'\0',sizeof(matrix));
	// lendo arquivo test bit
	read_file(TEST_BIT_FILE,matrix,131328);
	cast_mask_test_bit(matrix,test_bits);
	memset(matrix,'\0',sizeof(matrix));
	// lendo arquivo threshold high
	read_file(THADJ_H_FILE,matrix,327680);
	cast_threshold_bit(matrix,threshold_high);
	memset(matrix,'\0',sizeof(matrix));
	// conversao ascii binario
	ascii_to_bin(threshold_high, matrix);
	memset(threshold_high,'\0',sizeof(threshold_high));
	// gravar stream de saida
	write_out_stream(matrix,mask_bits,test_bits,all_bits);
	printf("\33[2J");
	printf("\33[1;1H");
	/*for(line=0;line<=786432;line++)
	{
		fprintf(stderr,"%c",all_bits[line]);
	}*/
	// grava em arquivo
    write_eq_arquivo(EQ_ARQUIVO, all_bits);

	printf("\nenjoy!\n\n");

    return 0;
}


