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

	// lendo arquivos gravados em disco
	printf("\nReading Saved Config");
	if(read_omrfile(OMR_FILE,&omr_param)<0)
	{
		printf("File %s not found\n",OMR_FILE);
		return -1;
	}
	//printf("\nLoading to Medipix...\n");
	//usleep(50);
	// aplicando parametros
	strcpy(omr_param.MODE,"0");
	write_omr_param_device(&omr_param);
	usleep(50);
	printf("\nInit Complete!!!\n");
	return 0;
}


