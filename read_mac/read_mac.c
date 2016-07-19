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
#include <string.h>
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/interface_uc.h"
#include "../utils/reg.h"

int main()
{
	char *mac;
	char *pch;
	send_network_param_t send_param;
	host_network_param_t host_param;
	inetd_t inetd;

	// lendo arquivos gravados em disco
	printf("\nReading Saved Config\n");
	if(read_sendfile(SEND_FILE,&send_param)<0)
	{
		printf("File %s not found\n",SEND_FILE);
   		return -1;
	}
	if(read_hostfile (HOST_FILE, &host_param)<0)
	{
		printf ("File %s not found\n", HOST_FILE);
	}
	if(read_macfile(MAC_FILE,&inetd)<0)
	{
		printf("File %s not found\n",MAC_FILE);	
   		return -1;
	}
	if(read_dhcpfile(mac)<0)
	{
		printf("File /etc/dhcpc/dhcpcd-eth0.info not found\n");
        return -1;
	}
	pch=strtok(mac,"=");
	pch=strtok(NULL," ");

	strcpy(send_param.mac_send,pch);
	//fprintf(stderr,"%s\n",send_param.mac_send);
	//printf("\nLoading to Medipix...\n");
	// aplicando parametros
	if (write_sendfile(SEND_FILE,&send_param)==0)
	{
	    if(write_send_param_device(&send_param, &host_param, &inetd) < 0)
		{
			printf("!#ERROR=Cannot write on device.!#");
			return -1;
		}
	}
	usleep(50);
	printf("Search Gateway Mac Complete!!!\n");
	return 0;
}


