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
#include <stdlib.h>
#include <string.h>
#include "cgivars.h"
#include "htmllib.h"
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/net_utils.h"
#include "../utils/reg.h"
#include "../utils/interface_uc.h"

#define BUFFER 16

int template_page(char **postvars, char **getvars, int form_method) 
{
	char callback[300];
	int i=0;	
	int write_flag = FALSE;
	omr_parameters_t  omr_param = {"OMR_PARAMETERS",/* LABEL */
                                   "7", 			/* M */
                                   "0",	  			/* CRW_SRW */
                			       "0",				/* POLARITTY */
               				       "0",	    		/* PS */
				                   "0",				/* DISC CSM SPM */
				                   "0",				/* ENABLE TP */
				                   "0", 			/* COUNTL */
				                   "0", 			/* COLUM N BLOCK */
   				                   "0",			    /* COLUM BLOCK SEL */
   				                   "0",     	    /* ROW BLOCK */
   				                   "0",   	        /* ROW BLOCK SEL */
	   				               "0",     	    /* EQUALIZATION */
   					               "0",   	        /* COLOUR MODE */
   					               "0",   	        /* CSM SPM */
   					               "0",   	        /* INFO HEADER */
   					               "0",     	    /* GAIN MODE */
   					               "00000",         /* SENSE DAC */
   					               "00000",         /* EXT DAC */
   					               "0",    	      	/* EXT BG SEL */
								   "001.000000",    /* AQU TIME */
								   "1",             /* AQU COUNT */
								   "001.000",       /* AQU GAP */
								   "0"              /* READ COUNTER */
								   "0"              /* PULSE_PERIOD */
								   "0"              /* NPULSES */
    	                           };
	
	if(read_omrfile(OMR_FILE,&omr_param) <0)
	{
		fprintf(stderr,"File %s not found\n",OMR_FILE);		
	}
	
	if(form_method == GET) 
	{	  
		for (i = 0; getvars[i]; i += 2) 
		{
			/// Main
			if (strncmp(getvars[i], "aqtime",BUFFER)==0) 
			{
    	        strncpy(omr_param.TIME, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "aqcount",BUFFER)==0) 
			{
                strncpy(omr_param.COUNTER, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "aqgap",BUFFER)==0) 
			{
                strncpy(omr_param.GAP, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "readcount",BUFFER)==0) 
			{
                strncpy(omr_param.READCOUNT, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "opmode",BUFFER)==0) 
			{
                strncpy(omr_param.MODE, getvars[i+1],BUFFER);
			}				
			else if (strncmp(getvars[i], "crw_srw",BUFFER)==0) 
			{
                strncpy(omr_param.CRW_SRW, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "pol",BUFFER)==0)
			{
				strncpy(omr_param.POLARITY, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "output",BUFFER)==0) 
			{
				strncpy(omr_param.PS, getvars[i+1],BUFFER);
			}				
			else if (strncmp(getvars[i], "disc_csm_spm",BUFFER)==0) 
			{
			    strncpy(omr_param.DISC_CSM_SPM, getvars[i+1],BUFFER);
			}
            else if (strncmp(getvars[i], "enable_tp",BUFFER)==0) 
			{
				strncpy(omr_param.ENABLE_TP, getvars[i+1],BUFFER);
			}
            else if (strncmp(getvars[i], "count_l",BUFFER)==0) 
			{
				strncpy(omr_param.COUNTL, getvars[i+1],BUFFER);
			}							
			else if (strncmp(getvars[i], "columnblock",BUFFER)==0) 
			{
				strncpy(omr_param.COLUMNBLOCK, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "columblocksel",BUFFER)==0) 
			{
				strncpy(omr_param.COLUMBLOCKSEL, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "rowblock",BUFFER)==0) 
			{
				strncpy(omr_param.ROWBLOCK, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "rowblocksel",BUFFER)==0) 
			{
				strncpy(omr_param.ROWBLOCKSEL, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "equalization",BUFFER)==0) 
			{
				strncpy(omr_param.EQUALIZATION, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "colourmode",BUFFER)==0) 
			{
				strncpy(omr_param.COLOURMODE, getvars[i+1],BUFFER);
			}	
			else if (strncmp(getvars[i], "csm_spm",BUFFER)==0) 
			{
				strncpy(omr_param.CSM_SPM, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "infoheader",BUFFER)==0) 
			{
				strncpy(omr_param.INFOHEADER, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "gainmode",BUFFER)==0) 
			{
				strncpy(omr_param.GAINMODE, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "tpulse_period",BUFFER)==0) 
			{
				strncpy(omr_param.PULSE_PERIOD, getvars[i+1],BUFFER);
			}
			else if (strncmp(getvars[i], "tp_npulses",BUFFER)==0) 
			{
				strncpy(omr_param.NPULSES, getvars[i+1],BUFFER);
			}		
				
            else if (strncmp(getvars[i], "read",BUFFER)==0)
			{
				if(response_callback(&callback)==0)
				{
					printf("%s",callback);
				}
			} 
            else if (strncmp(getvars[i], "write",BUFFER)==0) 
			{
				write_flag=TRUE;					
			}
		}
	}
	if(write_flag==TRUE)
	{
		validate_omr_param(&omr_param);
	}

	return 0;
}


int validate_omr_param(omr_parameters_t* param)
{
	double ftime;
	double gap;
	int readcount=0;
	int aqcount=1;
    int mode=0;
	int crw_srw=0;
	int polarity=0;
	int ps=0;
    int disc_csm_spm=0;
    int enable_tp=0;
	int countl=0;
	int columnblock=0;
	int columblocksel=0;
	int rowblock=0;
	int rowblocksel=0;
	int equalization=0;
	int colourmode=0;
	int csm_spm=0;
	int infoheader=0;
	int gainmode=0;
	int sensedac=0;
	int extdac=0;
	int extbgsel=0;
	int pulse_period=0;
	int npulses=0;

    omr_parameters_t interface = {  "OMR_PARAMETERS", /* LABEL */
                                    "7",			  /* M */
                                    "0",	     	  /* CRW_SRW */
                			        "0",			  /* POLARITTY */
               				        "0",			  /* PS */
				                    "0",		      /* DISC CSM SPM */
				                    "0",			  /* ENABLE TP */
				                    "0",			  /* COUNTL */
				                    "0",			  /* COLUM N BLOCK */
   				                    "0",		      /* COLUM BLOCK SEL */
   				                    "0",    	      /* ROW BLOCK */
   				                    "0",   	          /* ROW BLOCK SEL */
   				                    "0",     	      /* EQUALIZATION */
   				                    "0",   	          /* COLOUR MODE */
   				                    "0",   	          /* CSM SPM */
   				                    "0",   	          /* INFO HEADER */
   				                    "0",    	      /* GAIN MODE */
   				                    "00000",   	      /* SENSE DAC */
   				                    "00000",   	      /* EXT DAC */
   				                    "0",   	          /* EXT BG SEL */
									"001.000000",     /* AQU TIME */
								    "1",              /* AQU COUNT */
							  	    "001.000",        /* AQU GAP */
									"0"               /* READ COUNTER */
									"0"               /* PULSE_PERIOD */
		    						"0"               /* NPULSES */
                                    };
	
    ftime=atof(param->TIME);
	if (ftime<0.000001 || ftime>100.999999)
	{
		printf("!#ERROR=%f Invalid aqtime.!#",ftime);
        return -1;
	}
    else
    {
		snprintf(interface.TIME,sizeof(interface.TIME),"%0.6f",ftime);
	}
	aqcount=atoi(param->COUNTER);
	if(aqcount<1 || aqcount >16384)
    {
		printf("!#ERROR=%d Invalid aqcount.!#",aqcount);
        return -1;
	}
    else
    {
		sprintf(interface.COUNTER,"%d",aqcount);
	}
    gap=atof(param->GAP);

	if (gap<0.001 || gap>10.999)
	{
		printf("!#ERROR=%f Invalid GAP.!#",gap);
        return -1;
	}
    else
    {
		snprintf(interface.GAP,sizeof(interface.GAP),"%0.3f",gap);
	}

	readcount=atoi(param->READCOUNT);
	if(readcount<0 || readcount >2)
    {
		printf("!#ERROR=%d Invalid read counter.!#",readcount);
        return -1;
	}
    else
    {
		sprintf(interface.READCOUNT,"%d",readcount);
	}

    crw_srw=atoi(param->CRW_SRW);
	if(crw_srw>1 || crw_srw <0)
    {
		printf("!#ERROR=%d Invalid crw_srw Setting.!#",crw_srw);
		return -1;
	}
    else
    {
		sprintf(interface.CRW_SRW,"%d",crw_srw);
	}
	
	polarity=atoi(param->POLARITY);
	if(polarity>1 || polarity <0)
    {
		printf("!#ERROR=%d Invalid POLARITY Setting.!#",polarity);
		return -1;
	}
    else
    {
    	sprintf(interface.POLARITY,"%d",polarity);
	}
	
	ps=atoi(param->PS);
	if(ps <0 || ps >3)
    {
		printf("!#ERROR=%d Invalid PS.!#",ps);		
		return -1;
	}
    else
    {
    	sprintf(interface.PS,"%d",ps);
	}
	
	disc_csm_spm = atoi(param->DISC_CSM_SPM);
	if(disc_csm_spm<0 || disc_csm_spm >1)
    {
		printf("!#ERROR=%d Invalid DISC_CSM_SPM Setting.!#",disc_csm_spm);
		return -1;
	}
    else
    {
    	sprintf(interface.DISC_CSM_SPM,"%d",disc_csm_spm);
	}
	
	enable_tp = atoi(param->ENABLE_TP);
	if(enable_tp<0 || enable_tp >1)
    {
		printf("!#ERROR=%d Invalid ENABLE_TP Setting.!#",enable_tp);
		return -1;
	}
    else
    {
    	sprintf(interface.ENABLE_TP,"%d",enable_tp);
	}
	
	countl = atoi(param->COUNTL);
	if(countl<0 || countl >3){
		printf("!#ERROR=%d Invalid COUNTL !#",countl);
		return -1;
	}
    else
    {
    	sprintf(interface.COUNTL,"%d",countl);
	}

	mode=atoi(param->MODE);
	if(mode<0 || mode >7)
    {
		printf("!#ERROR=%d Invalid opmode.!#",mode);
        return -1;
	}
    else
    {
		if((mode==0)||(mode==1))
		{
			if(readcount==2)
			{
				sprintf(interface.MODE,"%d",0);
			}
			else
			{
				if(countl==3)
				{
					sprintf(interface.MODE,"%d",0);
					sprintf(interface.READCOUNT,"%d",0);
				}
				else
				{	
					sprintf(interface.MODE,"%d",readcount);
				}
			}
		}
		else
		{
			sprintf(interface.MODE,"%d",mode);
		}
	}
	columnblock = atoi(param->COLUMNBLOCK);
	if(columnblock<0 || columnblock >7)
    {
		printf("!#ERROR=%d Invalid COLUMNBLOCK Setting.!#",columnblock);
		return -1;
	}
    else
    {
    	sprintf(interface.COLUMNBLOCK,"%d",columnblock);
	}
	
	columblocksel = atoi(param->COLUMBLOCKSEL);
	if(columblocksel<0 || columblocksel >1)
    {
		printf("!#ERROR=%d Invalid COLUMBLOCKSEL Setting.!#",columblocksel);
		return -1;
	}
    else
    {
    	sprintf(interface.COLUMBLOCKSEL,"%d",columblocksel);
	}
	rowblock = atoi(param->ROWBLOCK);
	if(rowblock<0 || rowblock >7)
    {
		printf("!#ERROR=%d Invalid ROWBLOCK Setting.!#",rowblock);
		return -1;
	}
    else
    {
    	sprintf(interface.ROWBLOCK,"%d",rowblock);
	}
	
	rowblocksel = atoi(param->ROWBLOCKSEL);
	if(rowblocksel<0 || rowblocksel >1)
    {
		printf("!#ERROR=%d Invalid ROWBLOCKSEL Setting.!#",rowblocksel);
		return -1;
	}
    else
    {
    	sprintf(interface.ROWBLOCKSEL,"%d",rowblocksel);
	}
	equalization = atoi(param->EQUALIZATION);
	if(equalization<0 || equalization >1)
    {
		printf("!#ERROR=%d Invalid EQUALIZATION Setting.!#",equalization);
		return -1;
	}
    else
    {
    	sprintf(interface.EQUALIZATION,"%d",equalization);
	}
	
	colourmode = atoi(param->COLOURMODE);
	if(colourmode<0 || colourmode >1)
    {
		printf("!#ERROR=%d Invalid COLOURMODE Setting.!#",colourmode);
		return -1;
	}
    else
    {
    	sprintf(interface.COLOURMODE,"%d",colourmode);
	}
	
	csm_spm=atoi(param->CSM_SPM);
	if(csm_spm<0 || csm_spm >1)
    {
		printf("!#ERROR=%d Invalid CSM_SPM.!#",csm_spm);
		return -1;
	}
    else
    {	
    	sprintf(interface.CSM_SPM,"%d",csm_spm);
	}
	
	infoheader=atoi(param->INFOHEADER);
	if(infoheader<0 || infoheader >1)
    {
		printf("!#ERROR=%d Invalid INFOHEADER Setting.!#",infoheader);
		return -1;
	}
    else
    {
    	sprintf(interface.INFOHEADER,"%d",infoheader);
	}
	
	gainmode=atoi(param->GAINMODE);
	if(gainmode<0 || gainmode >3){
		printf("!#ERROR=%d Invalid GAINMODE Setting.!#",gainmode);
		return -1;
	}
    else
    {
    	sprintf(interface.GAINMODE,"%d",gainmode);
	}
    
    sensedac=atoi(param->SENSEDAC);
	if(sensedac<0 || sensedac >31){
		printf("!#ERROR=%d Invalid SENSEDAC.!#",sensedac);
		return -1;
	}
    else
    {
    	sprintf(interface.SENSEDAC,"%d",sensedac);
	}
	
	extdac=atoi(param->EXTDAC);
	if(extdac<0 || extdac >31){
		printf("!#ERROR=%d Invalid EXTDAC Setting.!#",extdac);
		return -1;
	}
    else
    {
    	sprintf(interface.EXTDAC,"%d",extdac);
	}
	
	extbgsel=atoi(param->EXTBGSEL);
	if(extbgsel<0 || extbgsel >1)
    {
		printf("!#ERROR=%d Invalid EXTBGSEL Setting.!#",extbgsel);
		return -1;
	}
    else
    {
    	sprintf(interface.EXTBGSEL,"%d",extbgsel);
	}

	pulse_period=atoi(param->PULSE_PERIOD);
	if(pulse_period<0 || pulse_period >236)
    {
		printf("!#ERROR=%d Invalid EXTBGSEL Setting.!#",pulse_period);
		return -1;
	}
    else
    {
    	sprintf(interface.PULSE_PERIOD,"%d",pulse_period);
	}

	npulses=atoi(param->NPULSES);
	if(npulses<0 || npulses >8191)
    {
		printf("!#ERROR=%d Invalid EXTBGSEL Setting.!#",npulses);
		return -1;
	}
    else
    {
    	sprintf(interface.NPULSES,"%d",npulses);
	}

    if(write_omrfile(OMR_FILE,&interface)){
		printf("!#ERROR=Cannot write on device.!#");
		return -1;
	}
	else
	{
		write_omr_param_device(&interface);		
	}

	if(mode>1)
	{
		success_callback("Settings Applied!");
	}
	
	return 0;
	
}

int response_callback(char* buffer){	
	if(buffer == NULL){
		return -1;
	}

    omr_parameters_t interface;

    read_omrfile(OMR_FILE,&interface);

	snprintf(buffer,300,"!#opmode=%s!#crw_srw=%s!#pol=%s!#output=%s!#disc_csm_spm=%s!#enable_tp=%s!#count_l=%s!#columnblock=%s!#columblocksel=%s!#rowblock=%s!#rowblocksel=%s!#equalization=%s!#colourmode=%s!#csm_spm=%s!#infoheader=%s!#gainmode=%s!#aqtime=%s!#aqcount=%s!#aqgap=%s!#readcount=%s!#tpulse_period=%s!#tp_npulses=%s!#",interface.MODE,interface.CRW_SRW,interface.POLARITY,interface.PS,interface.DISC_CSM_SPM,interface.ENABLE_TP,interface.COUNTL,interface.COLUMNBLOCK,interface.COLUMBLOCKSEL,interface.ROWBLOCK,interface.ROWBLOCKSEL,interface.EQUALIZATION,interface.COLOURMODE,interface.CSM_SPM,interface.INFOHEADER,interface.GAINMODE,interface.TIME,interface.COUNTER,interface.GAP,interface.READCOUNT,interface.PULSE_PERIOD,interface.NPULSES);

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
