#include <stdio.h>
#include <string.h>
#include "cgivars.h"
#include "htmllib.h"
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/net_utils.h"
#include "../utils/reg.h"
#include "../utils/interface_uc.h"

#define BUFFER 16

int template_page(char **postvars, char **getvars, int form_method) {
	int i=0;
	int write_flag=FALSE;
	char callback[100];
	dac_param_t	 dac_param = { "090",		/*THRESHOLD 0*/
				               "000",	    /*THRESHOLD 1*/
				               "000",       /*THRESHOLD 2*/
                               "000",		/*THRESHOLD 3*/
				               "000",	    /*THRESHOLD 4*/
                               "000",		/*THRESHOLD 5*/
				               "000",	    /*THRESHOLD 6*/
                               "000",		/*THRESHOLD 7*/
                               "100",		/*PREAMP*/
				               "005",	    /*IKRUM*/
				               "125",       /*SHAPER*/
                               "125",		/*DISC*/
				               "100",	    /*DISCLS*/
                               "100",		/*SHAPER_TEST*/
				               "061",	    /*DAC_DISCL*/
                               "100",		/*DAC_TEST*/
                               "067",		/*DAC_DISCH*/
				               "030",	    /*DELAY*/
				               "128",       /*TP_BUFFER_IN*/
                               "004",		/*TP_BUFFER_OUT*/
				               "255",	    /*RPZ*/
                               "141",		/*GND*/
				               "120",	    /*TP_REF*/
                               "177",		/*FBK*/
                               "187",		/*CAS*/
				               "260",	    /*TP_REFA*/
                               "263"		/*TP_REFB*/
	                         };
	
	if(read_dacfile(DAC_FILE,&dac_param) <0){
		printf("File %s not found\n",DAC_FILE);		
	}
	
	
	if(form_method == GET) {	
		for (i = 0; getvars[i]; i += 2) {
			    if (strncmp(getvars[i], "threshold_0",BUFFER)==0) {
					strncpy(dac_param.THRESHOLD_0, getvars[i+1],BUFFER);	
				}				
				else if (strncmp(getvars[i], "threshold_1",BUFFER)==0) {
					strncpy(dac_param.THRESHOLD_1, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "threshold_2",BUFFER)==0) {
					strncpy(dac_param.THRESHOLD_2, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "threshold_3",BUFFER)==0) {
					strncpy(dac_param.THRESHOLD_3, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "threshold_4",BUFFER)==0) {
					strncpy(dac_param.THRESHOLD_4, getvars[i+1],BUFFER);
				}
                else if (strncmp(getvars[i], "threshold_5",BUFFER)==0) {
					strncpy(dac_param.THRESHOLD_5, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "threshold_6",BUFFER)==0) {
					strncpy(dac_param.THRESHOLD_6, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "threshold_7",BUFFER)==0) {
					strncpy(dac_param.THRESHOLD_7, getvars[i+1],BUFFER);
				}
                else if (strncmp(getvars[i], "preamp",BUFFER)==0) {
					strncpy(dac_param.PREAMP, getvars[i+1],BUFFER);	
				}				
				else if (strncmp(getvars[i], "ikrum",BUFFER)==0) {
					strncpy(dac_param.IKRUM, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "shaper",BUFFER)==0) {
					strncpy(dac_param.SHAPER, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "disc",BUFFER)==0) {
					strncpy(dac_param.DISC, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "discls",BUFFER)==0) {
					strncpy(dac_param.DISCLS, getvars[i+1],BUFFER);
				}
                else if (strncmp(getvars[i], "shaper_test",BUFFER)==0) {
					strncpy(dac_param.SHAPER_TEST, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "dac_discl",BUFFER)==0) {
					strncpy(dac_param.DAC_DISCL, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "dac_test",BUFFER)==0) {
					strncpy(dac_param.DAC_TEST, getvars[i+1],BUFFER);
				}
                else if (strncmp(getvars[i], "dac_disch",BUFFER)==0) {
					strncpy(dac_param.DAC_DISCH, getvars[i+1],BUFFER);	
				}				
				else if (strncmp(getvars[i], "delay",BUFFER)==0) {
					strncpy(dac_param.DELAY, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "tp_bufferin",BUFFER)==0) {
					strncpy(dac_param.TP_BUFFER_IN, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "tp_bufferout",BUFFER)==0) {
					strncpy(dac_param.TP_BUFFER_OUT, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "rpz",BUFFER)==0) {
					strncpy(dac_param.RPZ, getvars[i+1],BUFFER);
				}
                else if (strncmp(getvars[i], "gnd",BUFFER)==0) {
					strncpy(dac_param.GND, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "tp_ref",BUFFER)==0) {
					strncpy(dac_param.TP_REF, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "fbk",BUFFER)==0) {
					strncpy(dac_param.FBK, getvars[i+1],BUFFER);
				}
                else if (strncmp(getvars[i], "cas",BUFFER)==0) {
					strncpy(dac_param.CAS, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "tp_refa",BUFFER)==0) {
					strncpy(dac_param.TP_REFA, getvars[i+1],BUFFER);
				}
				else if (strncmp(getvars[i], "tp_refb",BUFFER)==0) {
					strncpy(dac_param.TP_REFB, getvars[i+1],BUFFER);
				}

				else if (strncmp(getvars[i], "read",BUFFER)==0) {					
					if(response_callback(&callback)==0){
						printf("%s",callback);
					}
				
				}
				else if (strncmp(getvars[i], "write",BUFFER)==0) {
					write_flag=TRUE;					
				}
		}
		if(write_flag==TRUE){
			if(validate_dac_param(&dac_param)==0){
				write_dacfile(DAC_FILE,&dac_param);
			}	
		}
	}

	return 0;
}


int validate_dac_param(const dac_param_t *param){
	int threshold_0=0;
	int threshold_1=0;
	int threshold_2=0;
    int threshold_3=0;
	int threshold_4=0;
	int threshold_5=0;
	int threshold_6=0;
	int threshold_7=0;
    int preamp=0;
	int ikrum=0;
	int shaper=0;
    int disc=0;
	int discls=0;
	int shaper_test=0;
	int dac_discl=0;
	int dac_test=0;
    int dac_disch=0;
	int delay=0;
	int tp_bufferin=0;
    int tp_bufferout=0;
	int rpz=0;
	int gnd=0;
	int tp_ref=0;
	int fbk=0;
    int cas=0;
	int tp_refa=0;
	int tp_refb=0;

	threshold_0=atoi(param->THRESHOLD_0);
	if(threshold_0<0 || threshold_0>511){
		printf("!#ERROR=%d Invalid threshold.!#\n",threshold_0);
		return -1;
	}
	threshold_1=atoi(param->THRESHOLD_1);
	if(threshold_1<0 || threshold_1>511){
		printf("!#ERROR=%d Invalid threshold.!#\n",threshold_1);
		return -1;
	}
    threshold_2=atoi(param->THRESHOLD_2);
	if(threshold_2<0 || threshold_2>511){
		printf("!#ERROR=%d Invalid threshold.!#\n",threshold_2);
		return -1;
	}
    threshold_3=atoi(param->THRESHOLD_3);
	if(threshold_3<0 || threshold_3>511){
		printf("!#ERROR=%d Invalid threshold.!#\n",threshold_3);
		return -1;
	}
	threshold_4=atoi(param->THRESHOLD_4);
	if(threshold_4<0 || threshold_4>511){
		printf("!#ERROR=%d Invalid threshold.!#\n",threshold_4);
		return -1;
	}
    threshold_5=atoi(param->THRESHOLD_5);
	if(threshold_5<0 || threshold_5>511){
		printf("!#ERROR=%d Invalid threshold.!#\n",threshold_5);
		return -1;
	}
    threshold_6=atoi(param->THRESHOLD_6);
	if(threshold_6<0 || threshold_6>511){
		printf("!#ERROR=%d Invalid threshold.!#\n",threshold_6);
		return -1;
	}
    threshold_7=atoi(param->THRESHOLD_7);
	if(threshold_7<0 || threshold_7>511){
		printf("!#ERROR=%d Invalid threshold.!#\n",threshold_7);
		return -1;
	}
    preamp=atoi(param->PREAMP);
	if(preamp<0 || preamp>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",preamp);
		return -1;
	}
	ikrum=atoi(param->IKRUM);
	if(ikrum<0 || ikrum>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",ikrum);
		return -1;
	}
    shaper=atoi(param->SHAPER);
	if(shaper<0 || shaper>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",shaper);
		return -1;
	}
    disc=atoi(param->DISC);
	if(disc<0 || disc>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",disc);
		return -1;
	}
	discls=atoi(param->DISCLS);
	if(discls<0 || discls>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",discls);
		return -1;
	}
    shaper_test=atoi(param->SHAPER_TEST);
	if(shaper_test<0 || shaper_test>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",shaper_test);
		return -1;
	}
    dac_discl=atoi(param->DAC_DISCL);
	if(dac_discl<0 || dac_discl>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",dac_discl);
		return -1;
	}
    dac_test=atoi(param->DAC_TEST);
	if(dac_test<0 || dac_test>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",dac_test);
		return -1;
	}
    dac_disch=atoi(param->DAC_DISCH);
	if(dac_disch<0 || dac_disch>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",dac_disch);
		return -1;
	}
	delay=atoi(param->DELAY);
	if(delay<0 || delay>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",delay);
		return -1;
	}
    tp_bufferin=atoi(param->TP_BUFFER_IN);
	if(tp_bufferin<0 || tp_bufferin>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",tp_bufferin);
		return -1;
	}
    tp_bufferout=atoi(param->TP_BUFFER_OUT);
	if(tp_bufferout<0 || tp_bufferout>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",tp_bufferout);
		return -1;
	}
	rpz=atoi(param->RPZ);
	if(rpz<0 || rpz>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",rpz);
		return -1;
	}
    gnd=atoi(param->GND);
	if(gnd<0 || gnd>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",gnd);
		return -1;
	}
    tp_ref=atoi(param->TP_REF);
	if(tp_ref<0 || tp_ref>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",tp_ref);
		return -1;
	}
    fbk=atoi(param->FBK);
	if(fbk<0 || fbk>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",fbk);
		return -1;
	}
    cas=atoi(param->CAS);
	if(cas<0 || cas>255){
		printf("!#ERROR=%d Invalid threshold.!#\n",cas);
		return -1;
	}
    tp_refa=atoi(param->TP_REFA);
	if(tp_refa<0 || tp_refa>511){
		printf("!#ERROR=%d Invalid threshold.!#\n",tp_refa);
		return -1;
	}
    tp_refb=atoi(param->TP_REFB);
	if(tp_refb<0 || tp_refb>511){
		printf("!#ERROR=%d Invalid threshold.!#\n",tp_refb);
		return -1;
	}
	if(write_dac_param_device(param)){
		printf("!#ERROR=Cannot write on device.!#\n");
		return -1;
	}

	success_callback("Settings Applied!");

	return 0;
}

int response_callback(char *buffer){
	if(buffer == NULL){
		return -1;
	}
    
    dac_param_t interface;

    read_dacfile(DAC_FILE,&interface);

    sprintf(buffer,"!#threshold_0=%s!#threshold_1=%s!#threshold_2=%s!#threshold_3=%s!#threshold_4=%s!#threshold_5=%s!#threshold_6=%s!#threshold_7=%s!#preamp=%s!#ikrum=%s!#shaper=%s!#disc=%s!#discls=%s!#shaper_test=%s!#dac_discl=%s!#dac_test=%s!#dac_disch=%s!#delay=%s!#tp_bufferin=%s!#tp_bufferout=%s!#rpz=%s!#gnd=%s!#tp_ref=%s!#fbk=%s!#cas=%s!#tp_refa=%s!#tp_refb=%s!#",interface.THRESHOLD_0,interface.THRESHOLD_1,interface.THRESHOLD_2,interface.THRESHOLD_3,interface.THRESHOLD_4,interface.THRESHOLD_5,interface.THRESHOLD_6,interface.THRESHOLD_7,interface.PREAMP,interface.IKRUM,interface.SHAPER,interface.DISC,interface.DISCLS,interface.SHAPER_TEST,interface.DAC_DISCL,interface.DAC_TEST,interface.DAC_DISCH,interface.DELAY,interface.TP_BUFFER_IN,interface.TP_BUFFER_OUT,interface.RPZ,interface.GND,interface.TP_REF,interface.FBK,interface.CAS,interface.TP_REFA,interface.TP_REFB);

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
