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

char* StrCastReverse(char* str)
{
	char *temp, *ptr, *buff;
	char buf[5];
	int len, i;

	temp=str;
	for(len=0; *temp !='\0';temp++, len++);
	
	ptr=malloc(sizeof(char)*(len+1));
	
	for(i=len-1; i>=0; i--) 
		ptr[len-i-1]=str[i];
	
	ptr[len]='\0';

	strncpy(buf,ptr,5);

	buff=buf;

	temp=buff;
	for(len=0; *temp !='\0';temp++, len++);
	
	ptr=malloc(sizeof(char)*(len+1));
	
	for(i=len-1; i>=0; i--) 
		ptr[len-i-1]=buff[i];
	
	ptr[len]='\0';

	return ptr;
}

char* StrReverse(char* str)
{
	char *temp, *ptr;
	int len, i;

	temp=str;
	for(len=0; *temp !='\0';temp++, len++);
	
	ptr=malloc(sizeof(char)*(len+1));
	
	for(i=len-1; i>=0; i--) 
		ptr[len-i-1]=str[i];
	
	ptr[len]='\0';

	return ptr;
}

int read_file(const char* filename,char matrix[327680],int str_lenght)
{
	FILE *fp;
	int tamanho=0;

	memset(matrix,'\0',sizeof(matrix));

	fp = fopen(filename,"r");
	if(fp==NULL)
  	{
    	fprintf(stderr,"Error on opening file.\n");
      	return -1;
  	}
	tamanho=fread(matrix,sizeof(char),str_lenght,fp);
  	fclose(fp);

	return 0;
}

void cast_mask_test_bit(char matrix[327680], char mt_bits[65536])
{
	int conta=0,line=0;
	char mt_bits_mirror[65536];
	
	memset(mt_bits,'\0',sizeof(mt_bits));

	for(line=0;line<=131326;line++)
	{
		// tira os espaços fim de curso e nova linha
		if((matrix[line]!=0x20)&(matrix[line]!=0x0d)&(matrix[line]!=0x0a)&(matrix[line]!=0x00)&(matrix[line]!=0x09)&(matrix[line]!=0x0b))
		{	
			mt_bits_mirror[conta]=(matrix[line]);
			conta++;
		}
	}
	conta=0;
	for(line=65535;line>=0;line--)
	{
		mt_bits[conta]=mt_bits_mirror[line];
		conta++;
	}

	memset(matrix,'\0',sizeof(matrix));

}

void cast_threshold_bit(char matrix[327680], char threshold[196865])
{
	int conta=0,line=0;

	memset(threshold,'\0',sizeof(threshold));

	for(line=0;line<=196862;line++)
	{
		// tira fim de curso e nova linha
		if((matrix[line]!=0x0d)&(matrix[line]!=0x0a)&(matrix[line]!=0x00)&(matrix[line]!=0x09)&(matrix[line]!=0x0b))
		{	
			threshold[conta]=(matrix[line]);
			conta++;			
		}
		else if(matrix[line]=0x0d)
		{	
			threshold[conta]=(0x20);
			conta++;			
		}
	}
	memset(matrix,'\0',sizeof(matrix));
}

void write_out_stream(char matrix_low[327680], char matrix[327680], char mask_bits[65536],char test_bits[65536],char all_bits[786433])
{
	int line;
	int conta_mask=0;
	int conta_th0=0;
	int conta_th1=0;
	int conta_th2=0;
	int conta_th3=0;
	int conta_th4=0;
	int conta_tl0=0;
	int conta_tl1=0;
	int conta_tl2=0;
	int conta_tl3=0;
	int conta_tl4=0;
	int conta_test=0;

	for(line=0;line<=786431;line++)
	{
		strcpy(&all_bits[line],"0");
	}
	// todos os mask bit th e test bit no buffer de saida
	for(line=0;line<=65535;line++)
	{
		if(line==0)
		{
			conta_test=0;
			conta_tl0=256;
			conta_tl1=512;
			conta_tl2=768;
			conta_tl3=1024;
			conta_tl4=1280;
			conta_th0=1536;
			conta_th1=1792;
			conta_th2=2048;
			conta_th3=2304;
			conta_th4=2560;
			conta_mask=2816;
			all_bits[conta_test]=test_bits[line];
			all_bits[conta_tl0]=matrix_low[line];
			all_bits[conta_tl1]=matrix_low[line+1];
			all_bits[conta_tl2]=matrix_low[line+2];
			all_bits[conta_tl3]=matrix_low[line+3];
			all_bits[conta_tl4]=matrix_low[line+4];
			all_bits[conta_th0]=matrix[line];
			all_bits[conta_th1]=matrix[line+1];
			all_bits[conta_th2]=matrix[line+2];
			all_bits[conta_th3]=matrix[line+3];
			all_bits[conta_th4]=matrix[line+4];
			all_bits[conta_mask]=mask_bits[line];
			//fprintf(stderr,"\n%d %c %d %c %d", conta_test,all_bits[conta_test],line,test_bits[line],line);
		}
		else if(line%256==0)
		{
			conta_test+=2817;
			conta_tl0+=2817;
			conta_tl1+=2817;
			conta_tl2+=2817;
			conta_tl3+=2817;
			conta_tl4+=2817;
			conta_th0+=2817;
			conta_th1+=2817;
			conta_th2+=2817;
			conta_th3+=2817;
			conta_th4+=2817;
			conta_mask+=2817;
			all_bits[conta_test]=test_bits[line];
			all_bits[conta_tl0]=matrix_low[(line)*5];
			all_bits[conta_tl1]=matrix_low[(line*5)+1];
			all_bits[conta_tl2]=matrix_low[(line*5)+2];
			all_bits[conta_tl3]=matrix_low[(line*5)+3];
			all_bits[conta_tl4]=matrix_low[(line*5)+4];
			all_bits[conta_th0]=matrix[(line)*5];
			all_bits[conta_th1]=matrix[(line*5)+1];
			all_bits[conta_th2]=matrix[(line*5)+2];
			all_bits[conta_th3]=matrix[(line*5)+3];
			all_bits[conta_th4]=matrix[(line*5)+4];
			all_bits[conta_mask]=mask_bits[line];
			//fprintf(stderr,"\n%d %c %d %c %d", conta_test,all_bits[conta_test],line,test_bits[line],line);
		}
		else
		{
			conta_test++;
			conta_tl0++;
			conta_tl1++;
			conta_tl2++;
			conta_tl3++;
			conta_tl4++;
			conta_th0++;
			conta_th1++;
			conta_th2++;
			conta_th3++;
			conta_th4++;
			conta_mask++;
			all_bits[conta_test]=test_bits[line];
			all_bits[conta_tl0]=matrix_low[(line)*5];
			all_bits[conta_tl1]=matrix_low[(line*5)+1];
			all_bits[conta_tl2]=matrix_low[(line*5)+2];
			all_bits[conta_tl3]=matrix_low[(line*5)+3];
			all_bits[conta_tl4]=matrix_low[(line*5)+4];
			all_bits[conta_th0]=matrix[(line)*5];
			all_bits[conta_th1]=matrix[(line*5)+1];
			all_bits[conta_th2]=matrix[(line*5)+2];
			all_bits[conta_th3]=matrix[(line*5)+3];
			all_bits[conta_th4]=matrix[(line*5)+4];
			all_bits[conta_mask]=mask_bits[line];
			//fprintf(stderr,"\n%d %c %d %c %d", conta_test,all_bits[conta_test],line,test_bits[line],line);
		}
	}
}


int write_eq_arquivo(const char* filename, char stream_out[786433])
{
	FILE *fp;
	int line=0;

	fp=fopen(filename,"w+");
	
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
		fprintf(fp,"%c",stream_out[line]);
	}
    fclose(fp);
	
	return 0;
}

void ascii_to_bin(char threshold[196865], char matrix[327680])
{
	char* token;
	char* token2;
	unsigned int buff;
	int line=0,cont=0,coluna=0;
	char change[256][1280];

	memset(matrix,'\0',sizeof(matrix));
	token = strtok(threshold, " ");
	buff=(31-(atoi(token)));
	token2=StrCastReverse(byte_to_binary(buff));
	//fprintf(stderr,"\ntoken %s buff %d token2 %s",token,buff,token2);
	strcat(matrix,StrReverse(token2));
	do
	{
		token = strtok(NULL, " ");
		if (token!=NULL)
		{
			buff=(31-(atoi(token)));
			token2=StrCastReverse(byte_to_binary(buff));
			//fprintf(stderr,"\ntoken %s buff %d token2 %s",token,buff,token2);
			strcat(matrix,StrReverse(token2));//StrReverse(token2)
		}
	}while(token!= NULL);

	cont=0;
	for(line=0;line<=255;line++)
	{
		for(coluna=0;coluna<=1279;coluna++)
		{
			change[line][coluna]=matrix[cont];
			cont++;
		}
	}

	cont=0;
	memset(matrix,'\0',sizeof(matrix));

	// permuta colunas
	for(line=0;line<=255;line++)
	{
		for(coluna=1279;coluna>=0;coluna--)
		{
			matrix[cont]=change[line][coluna];
			cont++;
		}
	}
}

void ascii_to_bin_31(char threshold[196865], char matrix[327680])
{
	char* token;
	char* token2;
	unsigned int buff;
	int line=0,cont=0,coluna=0;
	char change[256][1280];

	memset(matrix,'\0',sizeof(matrix));
	token = strtok(threshold, " ");
	buff=atoi(token);
	token2=StrCastReverse(byte_to_binary(buff));
	//fprintf(stderr,"\ntoken %s buff %d token2 %s",token,buff,token2);
	strcat(matrix,StrReverse(token2));
	do
	{
		token = strtok(NULL, " ");
		if (token!=NULL)
		{
			buff=atoi(token);
			token2=StrCastReverse(byte_to_binary(buff));
			//fprintf(stderr,"\ntoken %s buff %d token2 %s",token,buff,token2);
			strcat(matrix,StrReverse(token2));//StrReverse(token2)
		}
	}while(token!= NULL);

	cont=0;
	for(line=0;line<=255;line++)
	{
		for(coluna=0;coluna<=1279;coluna++)
		{
			change[line][coluna]=matrix[cont];
			cont++;
		}
	}

	cont=0;
	memset(matrix,'\0',sizeof(matrix));

	// permuta colunas
	for(line=0;line<=255;line++)
	{
		for(coluna=1279;coluna>=0;coluna--)
		{
			matrix[cont]=change[line][coluna];
			cont++;
		}
	}
}



