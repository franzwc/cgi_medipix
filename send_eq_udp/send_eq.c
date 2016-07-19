/*MAIN FILE
--------------------------------------------------------------------------------
--!@brief Listen_UDP_port.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Programa que abre uma porta UDP e envia para placa 
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
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER "224.0.0.1"
#define BUFLEN 1024
#define PORT 8888

typedef unsigned char tdados[BUFLEN];

int main(void)
{
	FILE *fp;
    tdados eq[769];
    struct sockaddr_in si_other;
    int sock, slen=sizeof(si_other);
	int tamanho;
	int line=0;

	// lendo arquivo 
	fp = fopen("equalize.dat","r");
	if(fp==NULL)
  	{
    	fprintf(stderr,"Error on opening file.\n");
      	return -1;
  	}
	while(!feof(fp))
	{
		memset(eq[line],'\0',sizeof(tdados));
		tamanho=fread(eq[line],sizeof(unsigned char),sizeof(tdados),fp);
		//eq[(sizeof eq)-1] = 0;
		//fprintf(stderr,"\neq%d %s\n",line,eq[line]);
		line++;
	}
  	fclose(fp); 

	//fprintf(stderr,"\neq%d %s\n",0,eq[0]);

	//envia pela ethernet
    if ( (sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        return -1;
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        return -1;
    }
    line=0;
	for(line=0;line<=768;line++)
	{    
    	//send the message
    	if (sendto(sock, eq[line], BUFLEN , 0 , (struct sockaddr *) &si_other, slen)==-1)
    	{
        	return -1;
    	}
		usleep(1);
		//fprintf(stderr,"\neq%d %s\n",0,eq[0]);
    }     
    close(sock);
    return 0;
}

