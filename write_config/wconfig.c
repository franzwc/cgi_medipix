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

int main(int argc, char *argv[])
{
    FILE *fp;
    int i,j;
    int conta_pacote=0;

	char buff[786433];
	char buff2[786433];
	
	if (argc < 5) 
	{
         fprintf(stderr,"Error!!! Entre com os parametros\n");
         return -1;
    }

	printf("\33[2J");
	printf("\33[1;1H");

    fp=fopen("/home/franz/altera/Interface/cgi_medipix/send_eq_udp/equalize.dat","w+");
	
    if(fp==NULL)
    {    
         fprintf(stderr,"Error open file \n");
         return -1;
    }

	int a=1;

	// Toda a mascara
	for(j=1;j<=786432;j++)
    {
		if(a<=3071)
		{
			a++;
		}
		else
		{
			a=1;
		}
		if ((a>=1)&(a<=257))
		{
			sprintf(&buff[j],"%d",0); //mask bit
		}
		else if ((a>=258)&(a<=513))
		{
			sprintf(&buff[j],"%d",0);// tl 0
		}
		else if ((a>=514)&(a<=769))
		{
			sprintf(&buff[j],"%d",0);// tl 1
		}
		else if ((a>=770)&(a<=1025))
		{
			sprintf(&buff[j],"%d",0);// tl 2
		}
		else if ((a>=1026)&(a<=1281))
		{
			sprintf(&buff[j],"%d",0);// tl 3
		}
		else if ((a>=1282)&(a<=1537))
		{
			sprintf(&buff[j],"%d",0);// tl 4
		}
		else if ((a>=1538)&(a<=1793))
		{
			sprintf(&buff[j],"%s",argv[1]);// th 0
		}
		else if ((a>=1794)&(a<=2049))
		{
			sprintf(&buff[j],"%s",argv[2]);// th 1
		}
		else if ((a>=2050)&(a<=2305))
		{
			sprintf(&buff[j],"%s",argv[3]);// th 2
		}
		else if ((a>=2306)&(a<=2561))
		{
			sprintf(&buff[j],"%s",argv[4]);// th 3
		}
		else if ((a>=2562)&(a<=2817))
		{
			sprintf(&buff[j],"%s",argv[5]);// th 4
		}
		else if ((a>=2818)&(a<=3072))
		{
			sprintf(&buff[j],"%d",0); //test bit
		}
		else
		{
			sprintf(&buff[j],"%d",0);
		}
   	}

	i=1;

	for (j=786432;j>=1;j--)
	{
		sprintf(&buff2[i],"%c",buff[j]);
		i++;
	}
	for(j=1;j<=786432;j++)
	{
		fprintf(fp,"%c",buff2[j]);	
	   	if (j%3072==0)
		{	
			fprintf(fp,"\n");
		}
	}
    fclose(fp);
	printf("enjoy!\n\n");
    return 0;
}

