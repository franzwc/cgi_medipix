#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/reg.h"

int main()
{
	int p[2], backup,a;	
	char buf[100];
	char *pch;
	char mac[17];
	char command[50];
	send_network_param_t send_param = { "TX_SETUP",         /* Label */
	     								"224.0.0.1",		/* Default IP */
	                                    "3000",     		/* Default port */
	                                    "01:00:5e:00:00:01" /* Default mac */
	                                  };
	host_network_param_t host_param = { "10.0.27.67",		/* Default IP */
	                                    "255.255.255.0",    /* Default Netmask */
	                                    "10.0.27.1",		/* Default Gateway */
	                                  };

	if (read_hostfile (HOST_FILE, &host_param) < 0)
	{
	    fprintf (stderr, "File %s not found\n", HOST_FILE);
	}
	if(read_sendfile(SEND_FILE,&send_param) <0)
	{
		fprintf(stderr,"File %s not found\n",SEND_FILE);	
	}
	strcat(command,"ping ");
	strcat(command,host_param.gateway);
	strcat(command," -c 1");
	system (command);
	a=0;
	backup = dup(1);
	close(0);
	close(1);

	pipe(p);
	system ("arp -a");
	dup2(backup, 1);
	
	while (fgets(buf, 100, stdin))
	{
		pch=strstr(buf,host_param.gateway);
		if (pch!=NULL)
		{	
            strcpy(mac,pch);
			pch=strtok(mac," ");
			pch=strtok(NULL," ");
			pch=strtok(NULL," ");
			sprintf(mac,"%s",pch);
			fprintf(stderr,"%s\n",mac);
			sprintf(send_param.mac_send,"%s",mac);
			if (write_sendfile(SEND_FILE,&send_param)==0)
			{
			    if(write_send_param_device(&send_param))
				{
					fprintf(stderr,"!#ERROR=Cannot write on device.!#");
					return -1;
				}
			}
		}
		
	}
	
	

	
	return 0;
}
