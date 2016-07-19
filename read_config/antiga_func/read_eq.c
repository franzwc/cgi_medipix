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

int main(void)
{
	FILE *fp;
	char matrix[327680];
	char test_bits[65536];
	char mask_bits[65536];
	char threshold_high[196865];//196609
	char all_bits[786433];
	char all_bits_mirror[786433];
	char* token;
	char token2[5];
	int buff;
	int tamanho;
	int conta_mask=0;
	int conta_th0=0;
	int conta_th1=0;
	int conta_th2=0;
	int conta_th3=0;
	int conta_th4=0;
	int conta_test=0;
	int line=0;
	int conta=0;

	bzero(matrix,sizeof(matrix));
	bzero(mask_bits,sizeof(mask_bits));
	bzero(test_bits,sizeof(test_bits));
	bzero(threshold_high,sizeof(threshold_high));

	// lendo arquivo mask bit
	fp = fopen("ajustes_por_pixel/maskbit","r");
	if(fp==NULL)
  	{
    	fprintf(stderr,"Error on opening file.\n");
      	return -1;
  	}
	do
	{
		tamanho=fread(matrix,sizeof(char),sizeof(matrix),fp);
	}while(!feof(fp));
  	fclose(fp);
	for(line=0;line<=131326;line++)
	{
		// tira os espaços fim de curso e nova linha
		if((matrix[line]!=0x20)&(matrix[line]!=0x0d)&(matrix[line]!=0x0a))
		{	
			mask_bits[conta]=(matrix[line]);
			conta++;			
		}
	}
	bzero(matrix,sizeof(matrix));
	// lendo arquivo test bit
	fp = fopen("ajustes_por_pixel/testbit","r");
	if(fp==NULL)
  	{
    	fprintf(stderr,"Error on opening file.\n");
      	return -1;
  	}
	do
	{
		tamanho=fread(matrix,sizeof(char),sizeof(matrix),fp);
	}while(!feof(fp));
  	fclose(fp);
	conta=0;
	for(line=0;line<=131326;line++)
	{
		// tira os espaços fim de curso e nova linha
		if((matrix[line]!=0x20)&(matrix[line]!=0x0d)&(matrix[line]!=0x0a))
		{	
			test_bits[conta]=(matrix[line]);

			conta++;
		}
	}
	conta=0;
	memset(matrix,'\0',sizeof(matrix));
	// lendo arquivo threshold high
	fp = fopen("ajustes_por_pixel/ThAdjustmentH","r");
	if(fp==NULL)
  	{
    	fprintf(stderr,"Error on opening file.\n");
      	return -1;
  	}
	do
	{
		tamanho=fread(matrix,sizeof(char),sizeof(matrix),fp);
	}while(!feof(fp));
  	fclose(fp);

	for(line=0;line<=196863;line++)//196864 196608
	{
		// tira fim de curso e nova linha
		if((matrix[line]!=0x0d)&(matrix[line]!=0x0a))
		{	
			threshold_high[conta]=(matrix[line]);
			conta++;			
		}
		else if(matrix[line]=0x0d)
		{	
			threshold_high[conta]=(0x20);
			conta++;			
		}
	}
	// conversao ascii binario
	bzero(matrix,sizeof(matrix));
	token = strtok(threshold_high, " ");
	buff=atoi(token);
	strreverse(byte_to_binary(buff),token2);
	strncat(matrix,token2,5);
	line=0;
	while(token!= NULL)
	{
		token = strtok(NULL, " ");
		if (token!=NULL)
		{
			buff=atoi(token);
			strreverse(byte_to_binary(buff),token2);
			strncat(matrix,token2,5);
		}
		line++;
	}

	// gravando stream de saida
	for(line=0;line<=786431;line++)
	{
		strcpy(&all_bits[line],"0");	
	}

	// todos os mask bit th e test bit no buffer de saida
	for(line=0;line<=65535;line++)
	{
		if(line==0)
		{
			conta_mask=0;
			conta_th0=1536;
			conta_th1=1792;
			conta_th2=2048;
			conta_th3=2304;
			conta_th4=2560;
			conta_test=2816;
			all_bits[conta_mask]=mask_bits[line];
			all_bits[conta_th0]=matrix[line];
			all_bits[conta_th1]=matrix[line+1];
			all_bits[conta_th2]=matrix[line+2];
			all_bits[conta_th3]=matrix[line+3];
			all_bits[conta_th4]=matrix[line+4];
			//all_bits[conta_test]=test_bits[line];
			//fprintf(stderr,"\n%d %c %d %c %d", conta_th4,all_bits[conta_th4],line+4,matrix[line+4],line);
		}
		else if(line%256==0)
		{
			conta_mask+=2817;
			conta_th0+=2817;
			conta_th1+=2817;
			conta_th2+=2817;
			conta_th3+=2817;
			conta_th4+=2817;
			conta_test+=2817;
			all_bits[conta_mask]=mask_bits[line];
			all_bits[conta_th0]=matrix[(line)*5];
			all_bits[conta_th1]=matrix[(line*5)+1];
			all_bits[conta_th2]=matrix[(line*5)+2];
			all_bits[conta_th3]=matrix[(line*5)+3];
			all_bits[conta_th4]=matrix[(line*5)+4];
			//all_bits[conta_test]=test_bits[line];
			//fprintf(stderr,"\n%d %c %d %c %d", conta_th4,all_bits[conta_th4],(line*5)+4,matrix[(line*5)+4],line);
		}
		else
		{
			conta_mask++;
			conta_th0++;
			conta_th1++;
			conta_th2++;
			conta_th3++;
			conta_th4++;
			conta_test++;
			all_bits[conta_mask]=mask_bits[line];
			all_bits[conta_th0]=matrix[(line)*5];
			all_bits[conta_th1]=matrix[(line*5)+1];
			all_bits[conta_th2]=matrix[(line*5)+2];
			all_bits[conta_th3]=matrix[(line*5)+3];
			all_bits[conta_th4]=matrix[(line*5)+4];
			//all_bits[conta_test]=test_bits[line];
			//fprintf(stderr,"\n%d %c %d %c %d", conta_th4,all_bits[conta_th4],(line*5)+4,matrix[(line*5)+4],line);
		}
	}
	
	/*for(line=0;line<=10000;line++)
	{
		fprintf(stderr,"%c", all_bits[line]);
	}*/
	conta=0;

	for (line=786431;line>=0;line--)
	{
		sprintf(&all_bits_mirror[conta],"%c",all_bits[line]);
		conta++;
	}

	printf("\33[2J");
	printf("\33[1;1H");

    fp=fopen("/home/franz/altera/Interface/cgi_medipix/send_eq_udp/equalize.dat","w+");
	
    if(fp==NULL)
    {    
         fprintf(stderr,"Error open file \n");
         return -1;
    }

	for(line=0;line<=786431;line++)
	{	
	   	if ((line%3072==0)&(line!=0))
		{	
			fprintf(fp,"\n");
		}
		fprintf(fp,"%c",all_bits_mirror[line]);
	}
    fclose(fp);
	printf("enjoy!\n\n");

    return 0;
}

