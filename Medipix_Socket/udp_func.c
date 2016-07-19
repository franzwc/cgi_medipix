/*C FILE
--------------------------------------------------------------------------------
--!@brief udp_func.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Funcoes importantes
--!
--! DETAILS:      
--!
--!- Project Name: udp_func
--!- Module Name: udp_func.c
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 07/10/2014     
--!- Version: 1.0.0 (out/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "udp_func.h"
#include <sys/socket.h>
#include <netinet/in.h>


int validate_omr_param(omr_parameters_t param)
{
	float ftime,gap;
	int time,mode,nimages;

    mode=atoi(param.MODE);
    ftime=atof(param.TIME);
	nimages=atoi(param.COUNTER);
	gap=atof(param.GAP);
		
	//time=(int) ((ftime+gap)*nimages*1000000);
	
	if (strcmp(param.READCOUNT,"2")==0)
	{
		//fprintf(stderr,"\nentrou");
		if (ftime>=1)
		{
			if (nimages==1)
			{
				time=(int) (((ftime)*1000000)+100000);
			}
			else
			{
				time=(int) (((ftime+gap)*nimages*1000000)+150000);
			}
		}
		else
		{
			if (nimages==1)
			{
				time=(int) ((ftime*1000000)+100000);
			}
			else
			{	
				time=(int) (((ftime+gap)*nimages*1000000)+150000);
			}
		}
	}
	else
	{
		if (ftime>=1)
		{
			if (nimages==1)
			{
				time=(int) (((ftime)*1000000)+50000);
			}
			else
			{
				time=(int) (((ftime+gap)*nimages*1000000)+80000);
			}
		}
		else
		{
			if (nimages==1)
			{
				time=(int) ((ftime*1000000)+50000);
			}
			else
			{	
				time=(int) (((ftime+gap)*nimages*1000000)+80000);
			}
		}
	}
	

	//fprintf(stderr,"\ntime %d\n",time);	
	//escreve no arquivo
	if(write_omrfile(OMR_FILE,&param) <0)
	{
		//fprintf(stderr,"ERROR write file %s \n",OMR_FILE);
		return -1;
	}
    usleep(5);
	//escreve no device
    if(write_omr_param_device(&param))
	{
		//fprintf(stderr,"!#ERROR=Cannot write on device.!#");
		return -1;
	}

	if (mode==0 || mode==1)
	{
		usleep(time);
		//fprintf(stderr,"\nleitura tempo=%d us\n",time);
	}
	//else
	//{
		//usleep(50);
	//}
	
	usleep(50);

	return 0;
	
}

int validate_dac_param(dac_param_t param)
{
	//escreve no arquivo
	if(write_dacfile(DAC_FILE,&param) <0)
	{
		//fprintf(stderr,"ERROR write file %s \n",DAC_FILE);
		return -1;	
	}
    usleep(5);
	//escreve no device
	if(write_dac_param_device(&param))
	{
		//fprintf(stderr,"!#ERROR=Cannot write on device.!#");
		return -1;
	}

	return 0;
	
}

int validate_send_param (send_network_param_t send_param,host_network_param_t host_param, inetd_t inetd_param)
{
    //escreve no arquivo
	if(write_sendfile(SEND_FILE,&send_param) <0)
	{
		//fprintf(stderr,"ERROR write file %s \n",SEND_FILE);
		return -1;	
	}
    usleep(5);
	//escreve no device
	if(write_send_param_device(&send_param,&host_param,&inetd_param))
	{
		//fprintf(stderr,"!#ERROR=Cannot write on device.!#");
		return -1;
	}
	return 0;
}

int validate_host_param (host_network_param_t param)
{
	if(update_rc(&param) !=0)
	{
		//fprintf(stderr,"Error on update rc\n");
		return -1;
	}
	else
	{			
		write_hostfile (HOST_FILE, &param);
		usleep(10);

		if (setIPV4 (&param))
		{
			//fprintf (stderr,"!#ERROR=Device ERROR.!#");
			return -1;
		}
	}
	return 0;
}

void return_omr_udp(omr_parameters_t param, char buffer[150])
{
	memset(buffer,'\0',sizeof(buffer));
	strcat(buffer,"+");
	strcat(buffer,"OMR");
	strcat(buffer,"+");
	strcat(buffer,param.MODE);
	strcat(buffer,"+");
	strcat(buffer,param.CRW_SRW);
	strcat(buffer,"+");
	strcat(buffer,param.POLARITY);
	strcat(buffer,"+");
	strcat(buffer,param.PS);
	strcat(buffer,"+");
	strcat(buffer,param.DISC_CSM_SPM);
	strcat(buffer,"+");
	strcat(buffer,param.ENABLE_TP);
	strcat(buffer,"+");
	strcat(buffer,param.COUNTL);
	strcat(buffer,"+");
	strcat(buffer,param.COLUMNBLOCK);
	strcat(buffer,"+");
	strcat(buffer,param.COLUMBLOCKSEL);
	strcat(buffer,"+");
	strcat(buffer,param.ROWBLOCK);
	strcat(buffer,"+");
	strcat(buffer,param.ROWBLOCKSEL);
	strcat(buffer,"+");
	strcat(buffer,param.EQUALIZATION);
	strcat(buffer,"+");
	strcat(buffer,param.COLOURMODE);
	strcat(buffer,"+");
	strcat(buffer,param.CSM_SPM);
	strcat(buffer,"+");
	strcat(buffer,param.INFOHEADER);
	strcat(buffer,"+");
	strcat(buffer,param.GAINMODE);
	strcat(buffer,"+");
	strcat(buffer,param.SENSEDAC);
	strcat(buffer,"+");
	strcat(buffer,param.EXTDAC);
	strcat(buffer,"+");
	strcat(buffer,param.EXTBGSEL);
	strcat(buffer,"+");
	strcat(buffer,param.TIME);
	strcat(buffer,"+");
	strcat(buffer,param.COUNTER);
	strcat(buffer,"+");
	strcat(buffer,param.GAP);
	strcat(buffer,"+");
	strcat(buffer,param.READCOUNT);
	strcat(buffer,"+");
	int cont;
	for(cont=0;cont<=89;cont++)
	{
		strcat(buffer," ");
	}

	//printf("\n%s\n",buffer);
}
void return_dac_udp(dac_param_t param, char buffer[150])
{
	memset(buffer,'\0',sizeof(buffer));
	strcat(buffer,"+");
	strcat(buffer,"DAC");
	strcat(buffer,"+");
	strcat(buffer,param.THRESHOLD_0);
	strcat(buffer,"+");
	strcat(buffer,param.THRESHOLD_1);
	strcat(buffer,"+");
	strcat(buffer,param.THRESHOLD_2);
	strcat(buffer,"+");
	strcat(buffer,param.THRESHOLD_3);
	strcat(buffer,"+");
	strcat(buffer,param.THRESHOLD_4);
	strcat(buffer,"+");
	strcat(buffer,param.THRESHOLD_5);
	strcat(buffer,"+");
	strcat(buffer,param.THRESHOLD_6);
	strcat(buffer,"+");
	strcat(buffer,param.THRESHOLD_7);
	strcat(buffer,"+");
	strcat(buffer,param.PREAMP);
	strcat(buffer,"+");
	strcat(buffer,param.IKRUM);
	strcat(buffer,"+");
	strcat(buffer,param.SHAPER);
	strcat(buffer,"+");
	strcat(buffer,param.DISC);
	strcat(buffer,"+");
	strcat(buffer,param.DISCLS);
	strcat(buffer,"+");
	strcat(buffer,param.SHAPER_TEST);
	strcat(buffer,"+");
	strcat(buffer,param.DAC_DISCL);
	strcat(buffer,"+");
	strcat(buffer,param.DAC_TEST);
	strcat(buffer,"+");
	strcat(buffer,param.DAC_DISCH);
	strcat(buffer,"+");
	strcat(buffer,param.DELAY);
	strcat(buffer,"+");
	strcat(buffer,param.TP_BUFFER_IN);
	strcat(buffer,"+");
	strcat(buffer,param.TP_BUFFER_OUT);
	strcat(buffer,"+");
	strcat(buffer,param.RPZ);
	strcat(buffer,"+");
	strcat(buffer,param.GND);
	strcat(buffer,"+");
	strcat(buffer,param.TP_REF);
	strcat(buffer,"+");
	strcat(buffer,param.FBK);
	strcat(buffer,"+");
	strcat(buffer,param.CAS);
	strcat(buffer,"+");
	strcat(buffer,param.TP_REFA);
	strcat(buffer,"+");
	strcat(buffer,param.TP_REFB);
	strcat(buffer,"+");
	int cont;
	for(cont=0;cont<=36;cont++)
	{
		strcat(buffer," ");
	}

	//printf("\n%s\n",buffer);
}

void return_network_udp(send_network_param_t send_param, host_network_param_t host_param, char buffer[150])
{
	memset(buffer,'\0',sizeof(buffer));
	strcat(buffer,"+");
	strcat(buffer,"SEND");
	strcat(buffer,"+");
	strcat(buffer,send_param.ip_send);
	strcat(buffer,"+");
	strcat(buffer,send_param.port_send);
	strcat(buffer,"+");
	strcat(buffer,send_param.mac_send);
	strcat(buffer,"+");
	strcat(buffer,"HOST");
	strcat(buffer,"+");
	strcat(buffer,host_param.ip_address);
	strcat(buffer,"+");
	strcat(buffer,host_param.mask);
	strcat(buffer,"+");
	strcat(buffer,host_param.gateway);
	strcat(buffer,"+");
	int cont;
	for(cont=0;cont<=74;cont++)
	{
		strcat(buffer," ");
	}

	//printf("\n%s\n",buffer);
}

