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
#include<arpa/inet.h>
#include<sys/socket.h>
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
    mem_aloc buff1[NPACK1];
	mem_aloc buff6[NPACK6];
	mem_aloc buff12[NPACK12];
	mem_aloc buff24[NPACK24];

	if (argc < 3) 
	{
         fprintf(stderr,"Error!!! Entre com o numero de bits, numero de imagens e caminho para salvar arquivo\n");
         return -1;
    }

	nbits = atoi(argv[1]);
	nimagens = atoi(argv[2]);
	snprintf(caminho,sizeof(caminho),"%s",argv[3]);
	
	printf("\33[2J");
	printf("\33[1;1H");

    for(conta_img=1;conta_img<=nimagens;conta_img++)
	{
    	if ((sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    	{
			fprintf(stderr,"Error open Socket!!!\n");
			return -1;
    	}
     
   	 	bzero(&si_me,sizeof(si_me));
    	si_me.sin_family = AF_INET;
    	si_me.sin_port = htons(PORT);
    	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    	if(bind(sock ,(struct sockaddr*)&si_me, sizeof(si_me)) == -1)
    	{
			fprintf(stderr,"Error on bind!!!\n");
			return -1;
    	}

    	printf("Waiting for data...\n");
	
		if(nbits==1)
		{
		   		for(conta_pacote=0;conta_pacote<=63;conta_pacote++)
    			{
					bzero(buff1[conta_pacote],sizeof(buff1[conta_pacote]));
		       		if ((recv_len = recvfrom(sock, buff1[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		        	{
	   					fprintf(stderr,"Error on recvfrom1()!!!\n");
	   					return -1;
		        	}
		    	}
		    	close(sock);
		}
		else if(nbits==6)
		{
		    	for(conta_pacote=0;conta_pacote<=383;conta_pacote++)
    			{
					bzero(buff6[conta_pacote],sizeof(buff6[conta_pacote]));
		        	if ((recv_len = recvfrom(sock, buff6[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		        	{
	   					fprintf(stderr,"Error on recvfrom6()!!!\n");
	   					return -1;
		        	}
		    	}
		    	close(sock);
		}
		else if(nbits==12)
		{
		    	for(conta_pacote=0;conta_pacote<=767;conta_pacote++)
    			{
					bzero(buff12[conta_pacote],sizeof(buff12[conta_pacote]));
		        	if ((recv_len = recvfrom(sock, buff12[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		        	{
	   					fprintf(stderr,"Error on recvfrom12()!!!\n");
	   					return -1;
		        	}
		    	}
		    	close(sock);
		}
		else if(nbits==24)
		{
		    	for(conta_pacote=0;conta_pacote<=1536;conta_pacote++)
    			{
					printf("packet %d\n",conta_pacote+1);
					bzero(buff24[conta_pacote],sizeof(buff24[conta_pacote]));
		        	if ((recv_len = recvfrom(sock, buff24[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		        	{
	   					fprintf(stderr,"Error on recvfrom24()!!!\n");
	   					return -1;
		        	}
		    	}
		    	close(sock);
		}
		//printf("packet %d\n",conta_pacote+1);

		//altera o nome do arquivo toda vez
    	strcpy(arquivo,caminho);
		snprintf(packet,sizeof(packet),"%d",conta_img);
    	strcat(arquivo,packet);
    	strcat(arquivo,".dat");

    	fp=fopen(arquivo,"w+");
	
    	if(fp==NULL)
    	{    
        	 fprintf(stderr,"Error open file %s\n",caminho);
        	 return -1;
    	}
		if(nbits==1)
		{
    		for(i=0;i<=63;i++)
    		{
      		  for(j=0;j<=256;j++)
      		  {
        		    if(j>0)
					{
						fprintf(fp,"%x",(buff1[i][j] & 0x000000FF) >> 0);
	    	    		fprintf(fp,"%x",(buff1[i][j] & 0x0000FF00) >> 8);
						fprintf(fp,"%x",(buff1[i][j] & 0x00FF0000) >> 16);
						fprintf(fp,"%x",(buff1[i][j] & 0xFF000000) >> 24);
					}
        	    	if (j==64|j==128|j==192|j==256)
					{	
						fprintf(fp,"\n");
					}
    			}
    		}
		}
		else if (nbits==6)
		{
			for(i=0;i<=383;i++)
    		{
      		  for(j=0;j<=256;j++)
      		  {
        		    if(j>0)
					{
						fprintf(fp,"%x",(buff6[i][j] & 0x000000FF) >> 0);
	    	    		fprintf(fp,"%x",(buff6[i][j] & 0x0000FF00) >> 8);
						fprintf(fp,"%x",(buff6[i][j] & 0x00FF0000) >> 16);
						fprintf(fp,"%x",(buff6[i][j] & 0xFF000000) >> 24);
					}
        	    	if (j==256)
					{	
						fprintf(fp,"\n");
					}
    			}
    		}
		}
		else if (nbits==12)
		{
			for(i=0;i<=767;i++)
    		{
      		  for(j=0;j<=256;j++)
      		  {
        		    if(j>0)
					{
						fprintf(fp,"%x",(buff12[i][j] & 0x000000FF) >> 0);
	    	    		fprintf(fp,"%x",(buff12[i][j] & 0x0000FF00) >> 8);
						fprintf(fp,"%x",(buff12[i][j] & 0x00FF0000) >> 16);
						fprintf(fp,"%x",(buff12[i][j] & 0xFF000000) >> 24);
					}
        	    	if (j==256)
					{	
						fprintf(fp,"\n");
					}
    			}
    		}
		}
		else if (nbits==24)
		{
			for(i=0;i<=767;i++)
    		{
      		  for(j=0;j<=256;j++)
      		  {
        		    if(j>0)
					{
						fprintf(fp,"%x",(buff24[i][j] & 0x000000FF) >> 0);
	    	    		fprintf(fp,"%x",(buff24[i][j] & 0x0000FF00) >> 8);
						fprintf(fp,"%x",(buff24[i][j] & 0x00FF0000) >> 16);
						fprintf(fp,"%x",(buff24[i][j] & 0xFF000000) >> 24);
					}
        	    	if (j==256)
					{	
						fprintf(fp,"\n");
					}
    			}
    		}
			fprintf(fp,"\n");
			for(i=769;i<=1536;i++)
    		{
      		  for(j=0;j<=256;j++)
      		  {
        		    if(j>0)
					{
						fprintf(fp,"%x",(buff24[i][j] & 0x000000FF) >> 0);
	    	    		fprintf(fp,"%x",(buff24[i][j] & 0x0000FF00) >> 8);
						fprintf(fp,"%x",(buff24[i][j] & 0x00FF0000) >> 16);
						fprintf(fp,"%x",(buff24[i][j] & 0xFF000000) >> 24);
					}
        	    	if (j==256)
					{	
						fprintf(fp,"\n");
					}
    			}
    		}
		}
    	fclose(fp);
	}

	printf("enjoy!\n\n");
    return 0;
}

