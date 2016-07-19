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
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include"global.h"
#include"decode.h"

int main(void)
{
    struct sockaddr_in si_me, si_other;
    int sock, slen = sizeof(si_other) , recv_len;
    FILE *fp;
    int conta_pacote=0;
    int i,j; 
	int cont=0;   
    mem_aloc buff[NPACK];
 
    if ((sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
		fprintf(stderr,"Error open Socket");
		return 0;
    }
     
    bzero(&si_me,sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    if(bind(sock ,(struct sockaddr*)&si_me, sizeof(si_me)) == -1)
    {
		fprintf(stderr,"Error on bind");
		return 0;
    }

    printf("\33[2J");
	printf("\33[1;1H");
    printf("Waiting for data...\n");

    for(conta_pacote=0;conta_pacote<=63;conta_pacote++)
    {
		bzero(buff[conta_pacote],sizeof(buff[conta_pacote]));
        if ((recv_len = recvfrom(sock, buff[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
	    	fprintf(stderr,"Error on recvfrom()");
	    	return 0;
        }
		printf("\33[2;1H");
		printf("packet %d\n",conta_pacote+1);
    }
    close(sock);

	//Generate6BitTable();
	//Generate12BitTable();

    fp=fopen(DATA_FILE,"w+");
	
    if(fp==NULL)
    {    
         fprintf(stderr,"Error on opening file %s.\n",DATA_FILE);
         return 0;
    } 
    for(i=0;i<=63;i++)
    {
        for(j=0;j<=256;j++)
        {
            if (i==0)
			{
	        	if(j>4)
				{
					fprintf(fp,"%x",(buff[i][j] & 0x000000FF) >> 0);
	        		fprintf(fp,"%x",(buff[i][j] & 0x0000FF00) >> 8);
					fprintf(fp,"%x",(buff[i][j] & 0x00FF0000) >> 16);
					fprintf(fp,"%x",(buff[i][j] & 0xFF000000) >> 24);
				}
    	        if (j==68|j==132|j==196)
				{	
					fprintf(fp,"\n");
				}
			}
			if (i>=1)
			{
	        	if(j>4)
				{
					fprintf(fp,"%x",(buff[i][j] & 0x000000FF) >> 0);
	        		fprintf(fp,"%x",(buff[i][j] & 0x0000FF00) >> 8);
					fprintf(fp,"%x",(buff[i][j] & 0x00FF0000) >> 16);
					fprintf(fp,"%x",(buff[i][j] & 0xFF000000) >> 24);
				}
    	        if (j==((cont+1)*4)|j==(((cont+1)*4)+64)|j==(((cont+1)*4)+128)|j==(((cont+1)*4)+192))
				{	
					fprintf(fp,"\n");
				}
			}
			
    	}
		
		cont++;
		if (cont>16)
		{
			cont=1;
		}
    }
    fclose(fp);
	printf("enjoy!\n\n");
    return 0;
}

