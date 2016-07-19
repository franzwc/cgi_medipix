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
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/interface_uc.h"
#include "../utils/reg.h"

int main()
{
	 omr_parameters_t omr_param;
	 dac_param_t dac_param;
	 send_network_param_t send_param;
	 host_network_param_t host_param;
	 inetd_t inetd;

	// lendo arquivos gravados em disco
	printf("\nReading Saved Config");
	if(read_omrfile(OMR_FILE,&omr_param)<0)
	{
		printf("File %s not found\n",OMR_FILE);
		return -1;
	}
	if(read_dacfile(DAC_FILE,&dac_param)<0)
	{
 		printf("File %s not found\n",DAC_FILE);
   		return -1;
	}
	if(read_sendfile(SEND_FILE,&send_param)<0)
	{
		printf("File %s not found\n",SEND_FILE);
   		return -1;
	}
	if(read_hostfile (HOST_FILE, &host_param)<0)
	{
		fprintf (stderr, "File %s not found\n", HOST_FILE);
	}
	if(read_macfile(MAC_FILE,&inetd)<0)
	{
		printf("File %s not found\n",MAC_FILE);	
   		return -1;
	}
	//printf("\nLoading to Medipix...\n");
	//usleep(50);
	// aplicando parametros
	strcpy(omr_param.MODE,"7");
	write_omr_param_device(&omr_param);
	usleep(50);
	write_dac_param_device(&dac_param);
	usleep(50);
	write_send_param_device(&send_param, &host_param, &inetd);
	usleep(50);
	printf("\nInit Complete!!!\n");
	return 0;
}


