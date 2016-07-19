/*MAIN FILE
--------------------------------------------------------------------------------
--!@brief Listen_UDP_port.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Programa que abre uma porta UDP e escuta aguar
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
Header*/
#include <stdio.h>
#include <string.h>
#include "cgivars.h"
#include "htmllib.h"
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/net_utils.h"
#include "../utils/reg.h"
#include "../utils/interface_uc.h"


int template_page(char **postvars, char **getvars, int form_method) {	
	char callback[100];
	int i=0;	
	int write_flag = FALSE;
	send_network_param_t send_param = { "TX_SETUP",         /* Label */
										"224.0.0.1",		/* Default IP */
	                                    "3000",     		/* Default port */
	                                    "01:00:5e:00:00:01" /* Default mac */
	                                  };

	host_network_param_t host_param = { "10.0.27.67",		/* Default IP */
	                                    "255.0.0.0",		/* Default Netmask */
	                                    "10.0.27.1",		/* Default Gateway */
	                                  };
	
	inetd_t inetd 					= { "58:50:76:dd:ee:ff",/* Host Mac */
					    				"58:50:76:dd:ee:ff",/* Host Mac */
									  };
	if(read_sendfile(SEND_FILE,&send_param) <0)
	{
		fprintf(stderr,"File %s not found\n",SEND_FILE);	
	}
	if (read_hostfile (HOST_FILE, &host_param) < 0)
	{
		fprintf (stderr, "File %s not found\n", HOST_FILE);
	}
	if(read_macfile(MAC_FILE,&inetd) <0)
	{
		fprintf(stderr,"File %s not found\n",MAC_FILE);	
	}

	if(form_method == GET) 
	{  
		for (i = 0; getvars[i]; i += 2) 
		{
			if (strncmp(getvars[i], "ip_tx_address",BUFFER)==0) 
			{
	            strncpy(send_param.ip_send, getvars[i+1],BUFFER);
			}
			if (strncmp(getvars[i], "port",BUFFER)==0) 
			{
	            strncpy(send_param.port_send, getvars[i+1],BUFFER);
			}				
			if (strncmp(getvars[i], "mac",BUFFER)==0) 
			{
	            strncpy(send_param.mac_send, getvars[i+1],sizeof(send_param.mac_send));
			}				
	
            if (strncmp(getvars[i], "read",BUFFER)==0) 
			{
				if(response_callback(&callback)==0)
				{
					printf("%s",callback);
				}
			} 
            if (strncmp(getvars[i], "write",BUFFER)==0) 
			{
				write_flag=TRUE;					
			}
		}
	}

	if(write_flag==TRUE)
	{
		validate_send_param(&send_param, &host_param, &inetd);
	}

	return 0;
}


int validate_send_param(send_network_param_t* param, host_network_param_t* param_host, inetd_t* param_mac_host)
{
    if (write_sendfile(SEND_FILE,param)==0){
	    if(write_send_param_device(param,param_host,param_mac_host)){
			printf("!#ERROR=Cannot write on device.!#");
			return -1;
		}
	}
	
	success_callback("Settings Applied!");

	return 0;
	
}

int response_callback(char *buffer){	
	if(buffer == NULL){
		return -1;
	}

    send_network_param_t interface;

    read_sendfile(SEND_FILE,&interface);

    snprintf(buffer,100,"!#ip_tx_address=%s!#port=%s!#mac=%s!#",interface.ip_send,interface.port_send,interface.mac_send);

	return 0;
	
}

int error_callback(char *msg){
	if(msg == NULL){
		return -1;
	}
	printf("!#ERROR=%s!#",msg);
	return 0;
}

int success_callback(char *msg){
	if(msg == NULL){
		return -1;
	}
	printf("!#SUCCESS=%s!#",msg);
	return 0;
}

int debug_callback(char *option,char *msg){
	if(msg == NULL){
		return -1;
	}
	printf("!#DEBUG=%s : %s!#",option,msg);
	return 0;
}
