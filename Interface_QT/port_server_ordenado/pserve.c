/*MAIN FILE
--------------------------------------------------------------------------------
--!@brief pserve.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Programa que abre uma porta UDP e aguarda chegada de pacotes e grava 
--! a imagem decodificada
--!
--! DETAILS:      
--!
--!- Project Name: pserve
--!- Module Name: pserve.c
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 08/05/2014     
--!- Version: 1.0.0 (mai/2014)
--!- Version: 2.0.0 (fev/2015)
--------------------------------------------------------------------------------
-- LNLS - DET - 2015
--------------------------------------------------------------------------------
-- ENTRADAS => numero de bits de aquisicao, numero de imagens , nome e caminho pra salvar sem a extensao
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include <math.h>
#include"global.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in si_me, si_other;
    FILE *fp;
    int sock, slen = sizeof(si_other) , recv_len;
    int i,j;
    int conta_img=1,conta_pacote=0;
	int nimagens=1,nbits=0;
	char caminho[100]="\0";
	char arquivo[200]="\0";
	char packet[3]="\0";

	if (argc < 3) 
	{
         printf("Error!!! Entre com o numero de bits, numero de imagens e caminho para salvar arquivo\n");
         return -1;
    }

	nbits = atoi(argv[1]);
	nimagens = atoi(argv[2]);
	snprintf(caminho,sizeof(caminho),"%s",argv[3]);

    	if ((sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    	{
			printf("Error open Socket!!!\n");
			return -1;
    	}
     
   	 	bzero(&si_me,sizeof(si_me));
    	si_me.sin_family = AF_INET;
    	si_me.sin_port = htons(PORT);
    	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    	if(bind(sock ,(struct sockaddr*)&si_me, sizeof(si_me)) == -1)
    	{
			printf("Error on bind!!!\n");
			return -1;
    	}

    	fprintf(stdout,"Waiting for Data Stream...\n");
/**************************************************************************************************
*	socket aberto a espera dos pacotes
***************************************************************************************************
*	recebe da rede pacotes de 1bit
**************************************************************************************************/
		if(nbits==0)
		{
		   	for(conta_pacote=0;conta_pacote<=64;conta_pacote++)
    		{
				bzero(buff1[conta_pacote],sizeof(buff1[conta_pacote]));
		    	if ((recv_len = recvfrom(sock, buff1[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		       	{
	   				printf("Error on recvfrom1()!!!\n");
	   				return -1;
		       	}
				printf("%d Packets\n",conta_pacote);
		    }
		    close(sock);
		}
/**************************************************************************************************
*	recebe da rede pacotes de 6bits
**************************************************************************************************/
		else if(nbits==2)
		{
		   	for(conta_pacote=0;conta_pacote<=384;conta_pacote++)
    		{
				bzero(buff6[conta_pacote],sizeof(buff6[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff6[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		       	{
	   				printf("Error on recvfrom6()!!!\n");
	   				return -1;
		       	}
				printf("%d Packets\n",conta_pacote);
		   	}
		   	close(sock);
		}
/**************************************************************************************************
*	recebe da rede pacotes de 12bits
**************************************************************************************************/
		else if(nbits==1)
		{
		   	for(conta_pacote=0;conta_pacote<=768;conta_pacote++)
    		{
				bzero(buff12[conta_pacote],sizeof(buff12[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff12[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		       	{
	   				printf("Error on recvfrom12()!!!\n");
	   				return -1;
		       	}
				printf("%d Packets\n",conta_pacote);
		   	}
		   	close(sock);
		}
/**************************************************************************************************
*	recebe da rede pacotes de 24bits
**************************************************************************************************/
		else if(nbits==3)
		{
		   	for(conta_pacote=0;conta_pacote<=1537;conta_pacote++)
    		{
				//printf("packet %d\n",conta_pacote+1);
				bzero(buff24[conta_pacote],sizeof(buff24[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff24[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		       	{
	   				printf("Error on recvfrom24()!!!\n");
	   				return -1;
		       	}
				printf("%d Packets\n",conta_pacote);
		   	}
		   	close(sock);
		}
/**************************************************************************************************
*	recebe dois contadores de 12bits
**************************************************************************************************/
		else if(nbits==4)
		{
		   	for(conta_pacote=0;conta_pacote<=1537;conta_pacote++)
    		{
				//printf("packet %d\n",conta_pacote+1);
				bzero(buff24[conta_pacote],sizeof(buff24[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff24[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		       	{
	   				printf("Error on recvfrom12()!!!\n");
	   				return -1;
		       	}
				printf("%d Packets\n",conta_pacote);
		   	}
		   	close(sock);
		}
/**************************************************************************************************
*	socket fechado dados recebidos
**************************************************************************************************/
	printf("Enjoy!!!\n");
/**************************************************************************************************
*	executado com sucesso .....enjoy babe
**************************************************************************************************/
    return 0;
}


