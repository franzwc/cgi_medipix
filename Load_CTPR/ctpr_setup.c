#include <stdio.h>
#include <string.h>
#include "cgivars.h"
#include "htmllib.h"
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/net_utils.h"
#include "../utils/reg.h"
#include "../utils/interface_uc.h"

#define BUFFR 270

unsigned int ctpr[8];

int template_page(char **postvars, char **getvars, int form_method) {
	int i=0;
	int write_flag=FALSE;
	char callback[270];
	char buff[270];
	if(form_method == GET) {	
		for (i = 0; getvars[i]; i += 2) {
			    if (strncmp(getvars[i], "ctpr",BUFFR)==0) {
					strncpy(buff, getvars[i+1],BUFFR);
				}				

				else if (strncmp(getvars[i], "read",BUFFR)==0) {					
					if(response_callback(&callback)==0){
						printf("%s",callback);
					}
				
				}
				else if (strncmp(getvars[i], "write",BUFFR)==0) {
					write_flag=TRUE;					
				}
		}
		if(write_flag==TRUE){
			if(validate_param(buff)==0){

			}	
		}
	}

	return 0;
}


int validate_param(char str_buffer[270]){
	
	int int_buffer[8], a=0, cont=0;
	char char_buff[256];

	for(a=0;a<=255;a++)
	{
		strcpy(&char_buff[a],&str_buffer[a]);
	}

	//fprintf(stderr,"%s\n",char_buff);

	if(write_ctpr_param_device(char_buff)){
		printf("!#ERROR=Cannot write on device.!#\n");
		return -1;
	}
	//printf("%010d %010d %d %d %d %d %d %d",ctpr[0],ctpr[1],ctpr[2],ctpr[3],ctpr[4],ctpr[5],ctpr[6],ctpr[7]);
	success_callback("Settings Applied!");

	return 0;
}

int response_callback(char *buffer){
	if(buffer == NULL){
		return -1;
	}
    

    sprintf(buffer,"!#ctpr_0=%d!#ctpr_1=%d!#ctpr_2=%d!#ctpr_3=%d!#ctpr_4=%d!#ctpr_5=%d!#ctpr_6=%d!#ctpr_7=%d!#",ctpr[0],ctpr[1],ctpr[2],ctpr[3],ctpr[4],ctpr[5],ctpr[6],ctpr[7]);

	return 0;
}

int success_callback(char *msg){
	if(msg == NULL){
		return -1;
	}
	printf("!#SUCCESS=%s!#",msg);
	return 0;
}

int error_callback(char *msg){
	if(msg == NULL){
		return -1;
	}
	printf("!#ERROR=%s!#",msg);
	return 0;
}

int debug_callback(char *option,char *msg){
	if(msg == NULL){
		return -1;
	}
	printf("!#DEBUG=%s : %s!#",option,msg);
	return 0;
}
