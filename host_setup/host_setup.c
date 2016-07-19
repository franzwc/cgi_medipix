/*HOST SETUP CGI FILE
--------------------------------------------------------------------------------
--!@brief CGI FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! HOST SETUP CGI PARA UCLINUX
--!
--! DETAILS:      
--!
--!- Project Name: host_setup              
--!- Module Name: host_setup.c
--!- Tools: jedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 22/01/2014     
--!- Version: 1.0.0 (jan/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cgivars.h"
#include "htmllib.h"
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/net_utils.h"

int template_page (char **postvars, char **getvars, int form_method)
{
	char callback[100];
	int i = 0;
	int write_flag = FALSE;
	host_network_param_t host_param = { "10.0.27.67",		/* Default IP */
	                                    "255.0.0.0",		/* Default Netmask */
	                                    "10.0.27.1",		/* Default Gateway */
	                                  };

	if (read_hostfile (HOST_FILE, &host_param) < 0)
	{
		fprintf (stderr, "File %s not found\n", HOST_FILE);
	}

	if(form_method == GET) 
	{
		for (i = 0; getvars[i]; i += 2) 
		{
			if (strncmp (getvars[i], "ip_address", BUFFER) == 0)
			{
				strncpy (host_param.ip_address, getvars[i + 1], BUFFER);
			}
			if (strncmp (getvars[i], "netmask", BUFFER) == 0)
			{
				strncpy (host_param.mask, getvars[i + 1], BUFFER);
			}
			if (strncmp (getvars[i], "gateway", BUFFER) == 0)
			{
				strncpy (host_param.gateway, getvars[i + 1], BUFFER);
			}
			if (strncmp (getvars[i], "read", BUFFER) == 0)
			{
				if (response_callback (&callback, &host_param) == 0)
				{
					printf ("%s", callback);
				}
			}
			if (strncmp (getvars[i], "write", BUFFER) == 0)
			{
				write_flag = TRUE;
			}
		}
	}
	if(write_flag==TRUE)
	{
		if (validate_host_param (&host_param) == 0)
		{
			if(update_rc(&host_param) !=0)
			{
				fprintf(stderr,"Error on update rc\n");
				return -1;
			}
			else
			{
				write_hostfile (HOST_FILE, &host_param);
				success_callback ("Settings Applied!");
				usleep(100);
				if (setIPV4 (&host_param))
				{
					printf ("!#ERROR=Device ERROR.!#");
					return -1;
				}
			}
		}
	}
	return 0;
}


int validate_host_param (const host_network_param_t * param)
{
	if (!isValidIpAddress (param->ip_address))
	{
		fprintf (stderr,"!#ERROR=%s Invalid IP Address.!#", param->ip_address);
		return -1;
	}
	if (!isValidIpAddress (param->mask))
	{
		fprintf (stderr,"!#ERROR=%s Invalid Netmask.!#", param->mask);
		return -1;
	}
	if (!isValidIpAddress (param->gateway))
	{
		fprintf (stderr,"!#ERROR=%s Invalid gateway.!#", param->gateway);
		return -1;
	}

	return 0;
}

int response_callback (char *buffer, const host_network_param_t * host_param)
{
	if (buffer == NULL || host_param == NULL)
	{
		return -1;
	}
	snprintf (buffer, 100, "!#ip_address=%s!#netmask=%s!#gateway=%s!# ",
	          host_param->ip_address, host_param->mask, host_param->gateway);

	return 0;
}

int error_callback (char *msg)
{
	if (msg == NULL)
	{
		return -1;
	}
	fprintf (stderr,"!#ERROR=%s!#", msg);
	return 0;
}

int success_callback (char *msg)
{
	if (msg == NULL)
	{
		return -1;
	}
	printf ("!#SUCCESS=%s!#", msg);
	return 0;
}

int debug_callback (char *option, char *msg)
{
	if (msg == NULL)
	{
		return -1;
	}
	fprintf (stderr,"!#DEBUG=%s : %s!#", option, msg);
	return 0;
}
