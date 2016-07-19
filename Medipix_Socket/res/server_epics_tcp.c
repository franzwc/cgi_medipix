/*CGI FILE
--------------------------------------------------------------------------------
--!@brief Server TCP
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Socket server TCP paramentro da porta passada como argumento
--!
--! DETAILS:      bloco abre um socket para conexao TCP que recebe dados do 
--!               epics
--!
--!- Project Name: tcpserver
--!- Module Name: server.c
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 27/02/2014     
--!- Version: 1.0.0 (fev/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/interface_uc.h"
#include "../utils/reg.h"

// estado de gravaçao dos paramentros
typedef enum { write_omr, 
               write_dac,
               none
             } STATUS;


int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[20];
     struct sockaddr_in serv_addr, cli_addr;
     int res;
     char *token;
     char funcao[10];
     int valor;
	 float time;
	 int capture=0;

     STATUS status=none;
	 omr_parameters_t omr_param = { "OMR PARAMETERS", /* LABEL*/
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
									"001.000",		  /* AQU TIME */
									"1",              /* AQU COUNT */
							  	    "001.000"         /* AQU GAP */
                                    };

	 dac_param_t dac_param      = { "060",			      /*THRESHOLD 0*/
				               		"060",	    		  /*THRESHOLD 1*/
		 			                "000",       		  /*THRESHOLD 2*/
                               		"000",				  /*THRESHOLD 3*/
				               		"000",	    		  /*THRESHOLD 4*/
                               		"000",				  /*THRESHOLD 5*/
				               		"000",	    		  /*THRESHOLD 6*/
                               		"000",				  /*THRESHOLD 7*/
	                               	"100",				  /*PREAMP*/
				               		"005",	    		  /*IKRUM*/
				               		"125",       		  /*SHAPER*/
                               		"125",				  /*DISC*/
				               		"100",	    		  /*DISCLS*/
		                            "100",				  /*SHAPER_TEST*/
					               	"061",	    		  /*DAC_DISCL*/
                               		"100",				  /*DAC_TEST*/
                               		"067",				  /*DAC_DISCH*/
						            "030",	    		  /*DELAY*/
				               		"128",       		  /*TP_BUFFER_IN*/
                               		"004",				  /*TP_BUFFER_OUT*/
				               		"255",	    		  /*RPZ*/
                               		"141",				  /*GND*/
				               		"120",	    		  /*TP_REF*/
                               		"177",				  /*FBK*/
                               		"187",				  /*CAS*/
				               		"260",	    		  /*TP_REFA*/
                               		"263"				  /*TP_REFB*/
	                         	    };

     if (argc < 2)
	 {
     	 fprintf(stderr,"ERRO, entre com a porta\n");
         return -1;
     }
	 if(read_omrfile(OMR_FILE,&omr_param) <0)
     {
	 	 fprintf(stderr,"File %s not found\n",OMR_FILE);
         return -1;
     }
     usleep(100);
	 if(read_dacfile(DAC_FILE,&dac_param) <0)
     {
		 fprintf(stderr,"File %s not found\n",DAC_FILE);
         return -1;
     }
	 usleep(100);
 
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
	 {
         fprintf(stderr,"ERRO abrindo socket!!!\n");
         return -1;
     }

     fprintf(stderr,"Socket Aberto\n");

     memset((char *) &serv_addr,0, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	 {
         fprintf(stderr,"ERRO on binding!!!\n");
         return -1;
     }

     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);

     if (newsockfd < 0)
     { 
         fprintf(stderr,"ERRO on accept!!!\n");
         return -1;
     }

     fprintf(stderr,"Conexao aceita!\n");
     //depois de aceita a conexao entra em loop infinito

     while(1)
     {
            // aloca e zera o buffer
     		memset(buffer,'\0',sizeof(buffer));

     		res = read(newsockfd,buffer,sizeof(buffer));
     		if (res < 0)
			{
		        fprintf(stderr,"ERRO lendo do socket\n");
				close(newsockfd);
			    close(sockfd);
                return -1;
	        }

		    fprintf(stderr,"Aqui esta sua mensagem: %s\n",buffer);

	     	token=strtok(buffer," ");
     		strcpy(funcao,token);
			usleep(100);
			// procura qual dado foi alterado faz a validaçao
            if (strcmp(funcao,"-modesel")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
                if(valor<0 || valor >7)
    			{
					printf("!#ERROR=%s Invalid opmode.!#",&valor);
			        status=none;
				}
			    else
    			{
					itoa(valor,omr_param.MODE,10);
					capture=0;
    	        	status=write_omr;
				}
    		}
     		else if (strcmp(funcao,"-reset")==0)
     		{
       			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-execbit")==0)
     		{
     			printf("valor %d\n", valor);
     		}
		    else if (strcmp(funcao,"-acquire")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
       			if (valor==1)
				{
                	capture=1;
  	        		status=write_omr;
				}
				else
				{
					status=none;
				}

     		}
     		else if (strcmp(funcao,"-stop")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-flatfieldcorrection")==0)
	     	{
     			printf("valor %d\n", valor);
		    }
     		else if (strcmp(funcao,"-time")==0)
     		{
     			token=strtok(NULL," ");
	     		time=atof(token);
                if(time<0.001 || time >100.999)
    			{
					printf("!#ERROR=%s Invalid time.!#",&time);
			        status=none;
				}
			    else
    			{
					snprintf(omr_param.TIME,10,"%0.3f",time);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-colormode")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor >1)
			    {
					printf("!#ERROR= %d Invalid COLOURMODE Setting.!#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.COLOURMODE,10);
                    capture=0;
					status=write_omr;
				}
	     	}
     		else if (strcmp(funcao,"-gainmode")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor >3)
				{
					printf("!#ERROR=%d Invalid GAINMODE Setting.!#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.GAINMODE,10);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-summode")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor >1)
			    {
					printf("!#ERROR=%d Invalid CSM_SPM Setting.!#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.CSM_SPM,10);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-readwrite")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor>1 || valor <0)
    			{
					printf("!#ERROR=%d Invalid Protocol Setting.!#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.CRW_SRW,10);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-polarity")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
                if(valor>1 || valor <0)
    			{
					printf("!#ERROR=%d Invalid POLARITY Setting.!#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.POLARITY,10);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-clockext")==0)
     		{
		   		printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-extbgap")==0)
	     	{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor >1)
				{
					printf("!#ERROR=%d Invalid EXTBGSEL Setting.!#",valor);
					status=none;
				}
				else
				{
					itoa(valor,omr_param.EXTBGSEL,10);
                    capture=0;
    		       	status=write_omr;
				}
		    }
     		else if (strcmp(funcao,"-bias")==0)
     		{
		   		printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-discsel")==0)
		    {
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-statuseq")==0)
	     	{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-enabletp")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor >1)
			    {
					printf("!#ERROR= %d Invalid ENABLE_TP Setting.!#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.ENABLE_TP,10);
                    capture=0;
    	    	    status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-frames")==0)
		    {
     			printf("valor %d\n", valor);
		    }
     		else if (strcmp(funcao,"-ctrange")==0)
	     	{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor >3)
				{
					printf("!#ERROR=[%d] Invalid COUNTL !#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.COUNTL,10);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-readports")==0)
     		{
	     		printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-extdac")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor >31)
                {
					printf("!#ERROR=%d Invalid EXTDAC Setting.!#",valor);
					status=none;
				}
                else
                {
					itoa(valor,omr_param.EXTDAC,10);
                    capture=0;
   	        		status=write_omr;
				}
     		}
		    else if (strcmp(funcao,"-dacth0")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>511)
                {
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
                else
                {
	            	snprintf(dac_param.THRESHOLD_0,sizeof(dac_param.THRESHOLD_0),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth1")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>511)
                {
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
                else
                {
					snprintf(dac_param.THRESHOLD_1,sizeof(dac_param.THRESHOLD_1),"%03d",valor);
            		status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth2")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>511)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.THRESHOLD_2,sizeof(dac_param.THRESHOLD_2),"%03d",valor);
            		status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth3")==0)
		    {
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>511)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.THRESHOLD_3,sizeof(dac_param.THRESHOLD_3),"%03d",valor);
            		status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth4")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>511)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.THRESHOLD_4,sizeof(dac_param.THRESHOLD_4),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth5")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>511)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.THRESHOLD_5,sizeof(dac_param.THRESHOLD_5),"%03d",valor);
	            	status=write_dac;
				}
     		}
	     	else if (strcmp(funcao,"-dacth6")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>511)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.THRESHOLD_6,sizeof(dac_param.THRESHOLD_6),"%03d",valor);
	    	        status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth7")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>511)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.THRESHOLD_7,sizeof(dac_param.THRESHOLD_7),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-preamp")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.PREAMP,sizeof(dac_param.PREAMP),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-ikrum")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.IKRUM,sizeof(dac_param.IKRUM),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-shaper")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.SHAPER,sizeof(dac_param.SHAPER),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-disc")==0)
		    {
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.DISC,sizeof(dac_param.DISC),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-discls")==0)
		    {
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.DISCLS,sizeof(dac_param.DISCLS),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacdiscl")==0)
		    {
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.DAC_DISCL,sizeof(dac_param.DAC_DISCL),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacdisch")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.DAC_DISCH,sizeof(dac_param.DAC_DISCH),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-delay")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.DELAY,sizeof(dac_param.DELAY),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-tpbuffin")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.TP_BUFFER_IN,sizeof(dac_param.TP_BUFFER_IN),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-tpbuffout")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.TP_BUFFER_OUT,sizeof(dac_param.TP_BUFFER_OUT),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-pzc")==0)
		    {
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.RPZ,sizeof(dac_param.RPZ),"%03d",valor);
    	        	status=write_dac;
				}
     		}
		    else if (strcmp(funcao,"-gnd")==0)
		    {
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.GND,sizeof(dac_param.GND),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-tpref")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.TP_REF,sizeof(dac_param.TP_REF),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-fbk")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.FBK,sizeof(dac_param.FBK),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-cas")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>255)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.CAS,sizeof(dac_param.CAS),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-tprefa")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>511)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.TP_REFA,sizeof(dac_param.TP_REFA),"%03d",valor);
	    	        status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-tprefb")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor>511)
				{
					printf("!#ERROR=%d Invalid threshold.!#",valor);
					status=none;
				}
				else
				{
					snprintf(dac_param.TP_REFB,sizeof(dac_param.TP_REFB),"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-maskbit")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-testbit")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-adjl")==0)
     		{
     			printf("valor %d\n", valor);  
     		}
     		else if (strcmp(funcao,"-readout")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-adjh")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-colsel")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor >1)
			    {
					printf("!#ERROR= %d Invalid COLUMBLOCKSEL Setting.!#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.COLUMBLOCKSEL,10);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-rowsel")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
                if(valor<0 || valor >1)
			    {
					printf("!#ERROR= %d Invalid ROWBLOCKSEL Setting.!#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.ROWBLOCKSEL,10);
                    capture=0;
			        status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-colblock")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor >7)
			    {
					printf("!#ERROR=%d Invalid COLUMNBLOCK Setting.!#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.COLUMNBLOCK,10);
                    capture=0;
	            	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-rowblock")==0)
     		{
				token=strtok(NULL," ");
	     		valor=atoi(token);
				if(valor<0 || valor >7)
			    {
					printf("!#ERROR=%d Invalid ROWBLOCK Setting.!#",valor);
					status=none;
				}
			    else
			    {
					itoa(valor,omr_param.ROWBLOCK,10);
                    capture=0;
	    	        status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-tpcharge")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-tpperiod")==0)
     		{
     			printf("valor %d\n", valor);   
     		}
		    else if (strcmp(funcao,"-tpnpulses")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-tpspacing")==0)
     		{
     			printf("valor %d\n", valor);  
	     	}
     		else if (strcmp(funcao,"-eqalpha")==0)
		    {
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-eqenergy")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-eqacqtime")==0)
     		{
	     		printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-eqtarget")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-eqnloops")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-eqtype")==0)
     		{
     			printf("valor %d\n", valor);
     		}
     		else
     		{
            	status=none;
            	//printf("OPCAO NAO ENCONTRADA\n");
	 		}
     		// verifica se algum dado foi alterado e passa para gravaçao
     		switch(status)
     		{
	 			case 0:                   
						  if(capture==1)
						  {
							  strcpy(omr_param.MODE,"0");
						  }
						  else
						  {
	   	  					  strcpy(omr_param.MODE,"7");
						  }
                          validate_omr_param(omr_param);
            	          break;
	            case 1:
					      strcpy(omr_param.MODE,"4");
                          validate_dac_param(dac_param);
                          break;
    	        default:
    	                  printf("nada\n");
                          break;
     		}
            // responde que o dado foi recebido com sucesso
     		res = write(newsockfd,"Mensagem Recebida com Sucesso!",18);
     		if (res < 0)
            {
		        fprintf(stderr,"ERRO escrevendo no socket!!!\n");
				close(newsockfd);
			    close(sockfd);
                return -1;
        	}
     }
     close(newsockfd);
     close(sockfd);
     return 0; 
}

int validate_omr_param(omr_parameters_t param)
{
	float ftime;
	int mode;

    mode=atoi(param.MODE);
    ftime=atof(param.TIME)*1000;

	//escreve no arquivo
	if(write_omrfile(OMR_FILE,&param) <0)
	{
		fprintf(stderr,"ERROR write file %s \n",OMR_FILE);
		return -1;
	}
    usleep(100);
	//escreve no device
    if(write_omr_param_device(&param))
	{
		printf("!#ERROR=Cannot write on device.!#");
		return -1;
	}
	else
	{

	}
	if (mode==0 || mode==1)
	{
		fprintf(stderr,"leitura modo=%d tempo=%fus\n",mode,ftime);
		usleep(ftime);
	}
	return 0;
	
}

int validate_dac_param(dac_param_t param)
{
    usleep(100);
	//escreve no arquivo
	if(write_dacfile(DAC_FILE,&param) <0)
	{
		fprintf(stderr,"ERROR write file %s \n",DAC_FILE);
		return -1;	
	}
    usleep(100);

	if(write_dac_param_device(&param)){
		printf("!#ERROR=Cannot write on device.!#");
		return -1;
	}else{
		
	}

	return 0;
	
}
