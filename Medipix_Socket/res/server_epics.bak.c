/*CGI FILE
--------------------------------------------------------------------------------
--!@brief Server TCP
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Socket server TCP paramentro da porta passada como argumento
--!
--! DETAILS:      
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
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/interface_uc.h"
#include "../utils/reg.h"

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[20];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     int atualizar = FALSE;
     int write_omr = FALSE;
     int write_dac = FALSE;

     omr_parameters_t  omr_param = {"OMR PARAMETERS",/* LABEL */
                                   "000", 			/* M */
                                   "0",	  			/* CRW_SRW */
                			       "0",				/* POLARITTY */
               				       "00",			/* PS */
				                   "0",				/* DISC CSM SPM */
				                   "0",				/* ENABLE TP */
				                   "00",			/* COUNTL */
				                   "000",			/* COLUM N BLOCK */
   				                   "0",			    /* COLUM BLOCK SEL */
   				                   "000",     	    /* ROW BLOCK */
   				                   "0",   	        /* ROW BLOCK SEL */
	   				               "0",     	    /* EQUALIZATION */
   					               "0",   	        /* COLOUR MODE */
   					               "0",   	        /* CSM SPM */
   					               "0",   	        /* INFO HEADER */
   					               "00",    	    /* GAIN MODE */
   					               "00000",         /* SENSE DAC */
   					               "00000",         /* EXT DAC */
   					               "0"    	      	/* EXT BG SEL */
    	                           };

     dac_param_t	 dac_param =   {"050",			/*THRESHOLD 0*/
					               "050",	    	/*THRESHOLD 1*/
					               "050",  		    /*THRESHOLD 2*/
    	                           "050",			/*THRESHOLD 3*/
					               "050",		    /*THRESHOLD 4*/
    	                           "050",			/*THRESHOLD 5*/
					               "050",		    /*THRESHOLD 6*/
    	                           "050",			/*THRESHOLD 7*/
    	                           "050",			/*PREAMP*/
					               "050",		    /*IKRUM*/
					               "050",   	    /*SHAPER*/
    	                           "050",			/*DISC*/
					               "050",		    /*DISCLS*/
    	                           "050",			/*SHAPER_TEST*/
					               "050",		    /*DAC_DISCL*/
    	                           "050",			/*DAC_TEST*/
    	                           "050",			/*DAC_DISCH*/
					               "050",		    /*DELAY*/
					               "050",   	    /*TP_BUFFER_IN*/
    	                           "050",			/*TP_BUFFER_OUT*/
					               "050",		    /*RPZ*/
    	                           "050",			/*GND*/
					               "050",		    /*TP_REF*/
    	                           "050",			/*FBK*/
    	                           "050",			/*CAS*/
					               "050",		    /*TP_REFA*/
    	                           "050"			/*TP_REFB*/
	    	                       };

     if (argc < 2) {
         fprintf(stderr,"ERRO, entre com a porta\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0){ 
        perror("ERRO abrindo socket");
        exit(1);
        }
     fprintf(stderr,"Socket Aberto\n");
     memset((char *) &serv_addr,0, sizeof(serv_addr));//bzero
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
  
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        perror("ERRO on binding");
        exit(1);
        }
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
     if (newsockfd < 0){ 
        perror("ERRO on accept");
        exit(1);
        }
     fprintf(stderr,"Conexao aceita!\n");
     while(1){
     memset(buffer,0,20);
     n = read(newsockfd,buffer,20);
     if (n < 0){
        perror("ERRO lendo do socket");
        exit(1);
        }
     printf("Aqui esta sua mensagem: %s\n",buffer);

     char *token;
     char funcao[10];
     int valor;

     if(read_omrfile(OMR_FILE,&omr_param) <0)
     {
		fprintf(stderr,"File %s not found\n",OMR_FILE);		
     }

     if(read_dacfile(DAC_FILE,&dac_param) <0)
     {
		fprintf(stderr,"File %s not found\n",DAC_FILE);		
     }

     token=strtok(buffer," ");
     strcpy(funcao,token);
     token=strtok(NULL," ");
     valor=atoi(token);


     if (strcmp(funcao,"-modesel")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.MODE,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-reset")==0)
     {
       		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-execbit")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-start")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-stop")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-flatfieldcorrection")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-time")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-colormode")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.COLOURMODE,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-gainmode")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.GAINMODE,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-summode")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.CSM_SPM,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-readwrite")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.CRW_SRW,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-polarity")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.POLARITY,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-clockext")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-extbgap")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.EXTBGSEL,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-bias")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-discsel")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.DISC_CSM_SPM,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-statuseq")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-enabletp")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.ENABLE_TP,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-frames")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-ctrange")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.COUNTL,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-readports")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-extdac")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.EXTDAC,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-dacth0")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.THRESHOLD_0,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-dacth1")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.THRESHOLD_1,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-dacth2")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.THRESHOLD_2,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-dacth3")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.THRESHOLD_3,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-dacth4")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.THRESHOLD_4,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-dacth5")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.THRESHOLD_5,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-dacth6")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.THRESHOLD_6,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-dacth7")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.THRESHOLD_7,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-preamp")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.PREAMP,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-ikrum")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.IKRUM,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-shaper")==0)
     {
       		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.SHAPER,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-disc")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.DISC,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-discls")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.DISCLS,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-dacdiscl")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.DAC_DISCL,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-dacdisch")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.DAC_DISCH,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-delay")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.DELAY,10);
            atualizar=TRUE;
            write_dac=TRUE;  
     }
     else if (strcmp(funcao,"-tpbuffin")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.TP_BUFFER_IN,10);
            atualizar=TRUE;
            write_dac=TRUE; 
     }
     else if (strcmp(funcao,"-tpbuffout")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.TP_BUFFER_OUT,10);
            atualizar=TRUE;
            write_dac=TRUE; 
     }
     else if (strcmp(funcao,"-pzc")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.RPZ,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-gnd")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.GND,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-tpref")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.TP_REF,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-fbk")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.FBK,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-cas")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.CAS,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-tprefa")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.TP_REFA,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-tprefb")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,dac_param.TP_REFB,10);
            atualizar=TRUE;
            write_dac=TRUE;
     }
     else if (strcmp(funcao,"-maskbit")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-testbit")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-adjl")==0)
     {
     		printf("\n valor %d\n", valor);  
     }
     else if (strcmp(funcao,"-readout")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-adjh")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-colsel")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.COLUMBLOCKSEL,10);
            write_omr=TRUE;
            atualizar=TRUE;
     }
     else if (strcmp(funcao,"-rowsel")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.ROWBLOCKSEL,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-colblock")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.COLUMNBLOCK,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-rowblock")==0)
     {
     		printf("\n valor %d\n", valor);
            itoa(valor,omr_param.ROWBLOCK,10);
            atualizar=TRUE;
            write_omr=TRUE;
     }
     else if (strcmp(funcao,"-tpcharge")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-tpperiod")==0)
     {
     		printf("\n valor %d\n", valor);   
     }
     else if (strcmp(funcao,"-tpnpulses")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-tpspacing")==0)
     {
     		printf("\n valor %d\n", valor);  
     }
     else if (strcmp(funcao,"-eqalpha")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-eqenergy")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-eqacqtime")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-eqtarget")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-eqnloops")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else if (strcmp(funcao,"-eqtype")==0)
     {
     		printf("\n valor %d\n", valor);
     }
     else
     {
            atualizar=FALSE;
            write_omr=FALSE;
            write_dac=FALSE;
            printf("\n NAO LEU NENHUM\n");
	 }
     
     if (atualizar==TRUE)
     {
	     if(write_omr==TRUE)
    	 {
    	        //printf("\n VALIDANDO OMR\n");
				if(validate_omr_param(&omr_param)==0){
					//write_omrfile(OMR_FILE,&omr_param);
				}	
		 }
    	 if(write_dac==TRUE)
    	 {
            	//printf("\n VALIDANDO DAC\n");
				if(validate_dac_param(&dac_param)==0){
				//write_dacfile(DAC_FILE,&dac_param);
				}	
		 }
     }
 
     n = write(newsockfd,"Mensagem Recebida com Sucesso!",18);
     if (n < 0){
        perror("ERRO escrevendo no socket");
        exit(1);
        }
     }
     close(newsockfd);
     close(sockfd);
     return 0; 
}

int validate_omr_param(omr_parameters_t* param)
{
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

    omr_parameters_t interface = {  "OMR PARAMETERS", /* LABEL */
                                    "111",			  /* M */
                                    "0",	     	  /* CRW_SRW */
                			        "0",			  /* POLARITTY */
               				        "00",			  /* PS */
				                    "0",		      /* DISC CSM SPM */
				                    "0",			  /* ENABLE TP */
				                    "00",			  /* COUNTL */
				                    "000",			  /* COLUM N BLOCK */
   				                    "0",		      /* COLUM BLOCK SEL */
   				                    "000",   	      /* ROW BLOCK */
   				                    "0",   	          /* ROW BLOCK SEL */
   				                    "0",     	      /* EQUALIZATION */
   				                    "0",   	          /* COLOUR MODE */
   				                    "0",   	          /* CSM SPM */
   				                    "0",   	          /* INFO HEADER */
   				                    "00",   	      /* GAIN MODE */
   				                    "00000",   	      /* SENSE DAC */
   				                    "00000",   	      /* EXT DAC */
   				                    "0"   	          /* EXT BG SEL */
                                    };

    mode=atoi(param->MODE);
	if(mode<0 || mode >7)
    {
		printf("!#ERROR=%s Invalid opmode.!#",&mode);
        return -1;
	}
    else
    {
		itoa(mode,interface.MODE,10);
        printf("MODE=%s#\n",&interface.MODE);
	}
    crw_srw=atoi(param->CRW_SRW);
	if(crw_srw>1 || crw_srw <0)
    {
		printf("!#ERROR=%d Invalid Protocol Setting.!#",crw_srw);
		return -1;
	}
    else
    {
		itoa(crw_srw,interface.CRW_SRW,10);
        printf("crw_srw=%s#\n",&interface.CRW_SRW);
	}
	
	polarity=atoi(param->POLARITY);
	if(polarity>1 || polarity <0)
    {
		printf("!#ERROR=%d Invalid POLARITY Setting.!#",polarity);
		return -1;
	}
    else
    {
		itoa(polarity,interface.POLARITY,10);
        printf("POLARITY=%s#\n",&interface.POLARITY);
	}
	
	ps=atoi(param->PS);
	if(ps <0 || ps >3)
    {
		printf("!#ERROR= %d Invalid PS.!#",ps);		
		return -1;
	}
    else
    {
		itoa(ps,interface.PS,10);
        printf("PS=%s#\n",&interface.PS);
	}
	
	disc_csm_spm = atoi(param->DISC_CSM_SPM);
	if(disc_csm_spm<0 || disc_csm_spm >1)
    {
		printf("!#ERROR=%d Invalid DISC_CSM_SPM Setting.!#",disc_csm_spm);
		return -1;
	}
    else
    {
		itoa(disc_csm_spm,interface.DISC_CSM_SPM,10);
        printf("DISC_CSM_SPM=%s#\n",&interface.DISC_CSM_SPM);
	}
	
	enable_tp = atoi(param->ENABLE_TP);
	if(enable_tp<0 || enable_tp >1)
    {
		printf("!#ERROR= %d Invalid ENABLE_TP Setting.!#",enable_tp);
		return -1;
	}
    else
    {
		itoa(enable_tp,interface.ENABLE_TP,10);
        printf("ENABLE_TP=%s#\n",&interface.ENABLE_TP);
	}
	
	countl = atoi(param->COUNTL);
	if(countl<0 || countl >3){
		printf("!#ERROR=[%d] Invalid COUNTL !#",countl);
		return -1;
	}
    else
    {
		itoa(countl,interface.COUNTL,10);
        printf("COUNTL=%s#\n",&interface.COUNTL);
	}
		
	columnblock = atoi(param->COLUMNBLOCK);
	if(columnblock<0 || columnblock >7)
    {
		printf("!#ERROR=%d Invalid COLUMNBLOCK Setting.!#",columnblock);
		return -1;
	}
    else
    {
		itoa(columnblock,interface.COLUMNBLOCK,10);	
        printf("COLUMNBLOCK=%s#\n",&interface.COLUMNBLOCK);
	}
	
	columblocksel = atoi(param->COLUMBLOCKSEL);
	if(columblocksel<0 || columblocksel >1)
    {
		printf("!#ERROR= %d Invalid COLUMBLOCKSEL Setting.!#",columblocksel);
		return -1;
	}
    else
    {
		itoa(columblocksel,interface.COLUMBLOCKSEL,10);
        printf("COLUMBLOCKSEL=%s#\n",&interface.COLUMBLOCKSEL);
	}
	rowblock = atoi(param->ROWBLOCK);
	if(rowblock<0 || rowblock >7)
    {
		printf("!#ERROR=%d Invalid ROWBLOCK Setting.!#",rowblock);
		return -1;
	}
    else
    {
		itoa(rowblock,interface.ROWBLOCK,10);
        printf("ROWBLOCK=%s#\n",&interface.ROWBLOCK);
	}
	
	rowblocksel = atoi(param->ROWBLOCKSEL);
	if(rowblocksel<0 || rowblocksel >1)
    {
		printf("!#ERROR= %d Invalid ROWBLOCKSEL Setting.!#",rowblocksel);
		return -1;
	}
    else
    {
		itoa(rowblocksel,interface.ROWBLOCKSEL,10);
        printf("ROWBLOCKSEL=%s#\n",&interface.ROWBLOCKSEL);
	}
	equalization = atoi(param->EQUALIZATION);
	if(equalization<0 || equalization >1)
    {
		printf("!#ERROR=%d Invalid EQUALIZATION Setting.!#",equalization);
		return -1;
	}
    else
    {
		itoa(equalization,interface.EQUALIZATION,10);
        printf("EQUALIZATION=%s#\n",&interface.EQUALIZATION);
	}
	
	colourmode = atoi(param->COLOURMODE);
	if(colourmode<0 || colourmode >1)
    {
		printf("!#ERROR= %d Invalid COLOURMODE Setting.!#",colourmode);
		return -1;
	}
    else
    {
		itoa(colourmode,interface.COLOURMODE,10);
        printf("COLOURMODE=%s#\n",&interface.COLOURMODE);
	}
	
	csm_spm=atoi(param->CSM_SPM);
	if(csm_spm<0 || csm_spm >1)
    {
		printf("!#ERROR=%d Invalid CSM_SPM.!#",csm_spm);
		return -1;
	}
    else
    {
		itoa(csm_spm,interface.CSM_SPM,10);
        printf("CSM_SPM=%s#\n",&interface.CSM_SPM);
	}
	
	infoheader=atoi(param->INFOHEADER);
	if(infoheader<0 || infoheader >1)
    {
		printf("!#ERROR=%d Invalid INFOHEADER Setting.!#",infoheader);
		return -1;
	}
    else
    {
		itoa(infoheader,interface.INFOHEADER,10);
        printf("INFOHEADER=%s#\n",&interface.INFOHEADER);
	}
	
	gainmode=atoi(param->GAINMODE);
	if(gainmode<0 || gainmode >3){
		printf("!#ERROR=%d Invalid GAINMODE Setting.!#",gainmode);
		return -1;
	}
    else
    {
		itoa(gainmode,interface.GAINMODE,10);
        printf("GAINMODE=%s#\n",&interface.GAINMODE);
	}
    
    sensedac=atoi(param->SENSEDAC);
	if(sensedac<0 || sensedac >31){
		printf("!#ERROR=%d Invalid SENSEDAC.!#",sensedac);
		return -1;
	}
    else
    {
		itoa(sensedac,interface.SENSEDAC,10);
        printf("SENSEDAC=%s#\n",&interface.SENSEDAC);
	}
	
	extdac=atoi(param->EXTDAC);
	if(extdac<0 || extdac >31){
		printf("!#ERROR=%d Invalid EXTDAC Setting.!#",extdac);
		return -1;
	}
    else
    {
		itoa(extdac,interface.EXTDAC,10);
        printf("EXTDAC=%s#\n",&interface.EXTDAC);
	}
	
	extbgsel=atoi(param->EXTBGSEL);
	if(extbgsel<0 || extbgsel >1)
    {
		printf("!#ERROR=%d Invalid EXTBGSEL Setting.!#",extbgsel);
		return -1;
	}
    else
    {
		itoa(extbgsel,interface.EXTBGSEL,10);
        printf("EXTBGSEL=%s#\n",&interface.EXTBGSEL);
	}


    /*if(write_omr_param_device(&interface)){
		printf("!#ERROR=Cannot write on device.!#");
		return -1;
	}else{
		printf("\n ESCREVENDO\n");
	}*/

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
		printf("!#ERROR=%d Invalid threshold.!#",threshold_0);
		return -1;
	}
	threshold_1=atoi(param->THRESHOLD_1);
	if(threshold_1<0 || threshold_1>511){
		printf("!#ERROR=%d Invalid threshold.!#",threshold_1);
		return -1;
	}
    threshold_2=atoi(param->THRESHOLD_2);
	if(threshold_2<0 || threshold_2>511){
		printf("!#ERROR=%d Invalid threshold.!#",threshold_2);
		return -1;
	}
    threshold_3=atoi(param->THRESHOLD_3);
	if(threshold_3<0 || threshold_3>511){
		printf("!#ERROR=%d Invalid threshold.!#",threshold_3);
		return -1;
	}
	threshold_4=atoi(param->THRESHOLD_4);
	if(threshold_4<0 || threshold_4>511){
		printf("!#ERROR=%d Invalid threshold.!#",threshold_4);
		return -1;
	}
    threshold_5=atoi(param->THRESHOLD_5);
	if(threshold_5<0 || threshold_5>511){
		printf("!#ERROR=%d Invalid threshold.!#",threshold_5);
		return -1;
	}
    threshold_6=atoi(param->THRESHOLD_6);
	if(threshold_6<0 || threshold_6>511){
		printf("!#ERROR=%d Invalid threshold.!#",threshold_6);
		return -1;
	}
    threshold_7=atoi(param->THRESHOLD_7);
	if(threshold_7<0 || threshold_7>511){
		printf("!#ERROR=%d Invalid threshold.!#",threshold_7);
		return -1;
	}
    preamp=atoi(param->PREAMP);
	if(preamp<0 || preamp>255){
		printf("!#ERROR=%d Invalid threshold.!#",preamp);
		return -1;
	}
	ikrum=atoi(param->IKRUM);
	if(ikrum<0 || ikrum>255){
		printf("!#ERROR=%d Invalid threshold.!#",ikrum);
		return -1;
	}
    shaper=atoi(param->SHAPER);
	if(shaper<0 || shaper>255){
		printf("!#ERROR=%d Invalid threshold.!#",shaper);
		return -1;
	}
    disc=atoi(param->DISC);
	if(disc<0 || disc>255){
		printf("!#ERROR=%d Invalid threshold.!#",disc);
		return -1;
	}
	discls=atoi(param->DISCLS);
	if(discls<0 || discls>255){
		printf("!#ERROR=%d Invalid threshold.!#",discls);
		return -1;
	}
    shaper_test=atoi(param->SHAPER_TEST);
	if(shaper_test<0 || shaper_test>255){
		printf("!#ERROR=%d Invalid threshold.!#",shaper_test);
		return -1;
	}
    dac_discl=atoi(param->DAC_DISCL);
	if(dac_discl<0 || dac_discl>255){
		printf("!#ERROR=%d Invalid threshold.!#",dac_discl);
		return -1;
	}
    dac_test=atoi(param->DAC_TEST);
	if(dac_test<0 || dac_test>255){
		printf("!#ERROR=%d Invalid threshold.!#",dac_test);
		return -1;
	}
    dac_disch=atoi(param->DAC_DISCH);
	if(dac_disch<0 || dac_disch>255){
		printf("!#ERROR=%d Invalid threshold.!#",dac_disch);
		return -1;
	}
	delay=atoi(param->DELAY);
	if(delay<0 || delay>255){
		printf("!#ERROR=%d Invalid threshold.!#",delay);
		return -1;
	}
    tp_bufferin=atoi(param->TP_BUFFER_IN);
	if(tp_bufferin<0 || tp_bufferin>255){
		printf("!#ERROR=%d Invalid threshold.!#",tp_bufferin);
		return -1;
	}
    tp_bufferout=atoi(param->TP_BUFFER_OUT);
	if(tp_bufferout<0 || tp_bufferout>255){
		printf("!#ERROR=%d Invalid threshold.!#",tp_bufferout);
		return -1;
	}
	rpz=atoi(param->RPZ);
	if(rpz<0 || rpz>255){
		printf("!#ERROR=%d Invalid threshold.!#",rpz);
		return -1;
	}
    gnd=atoi(param->GND);
	if(gnd<0 || gnd>255){
		printf("!#ERROR=%d Invalid threshold.!#",gnd);
		return -1;
	}
    tp_ref=atoi(param->TP_REF);
	if(tp_ref<0 || tp_ref>255){
		printf("!#ERROR=%d Invalid threshold.!#",tp_ref);
		return -1;
	}
    fbk=atoi(param->FBK);
	if(fbk<0 || fbk>255){
		printf("!#ERROR=%d Invalid threshold.!#",fbk);
		return -1;
	}
    cas=atoi(param->CAS);
	if(cas<0 || cas>255){
		printf("!#ERROR=%d Invalid threshold.!#",cas);
		return -1;
	}
    tp_refa=atoi(param->TP_REFA);
	if(tp_refa<0 || tp_refa>511){
		printf("!#ERROR=%d Invalid threshold.!#",tp_refa);
		return -1;
	}
    tp_refb=atoi(param->TP_REFB);
	if(tp_refb<0 || tp_refb>511){
		printf("!#ERROR=%d Invalid threshold.!#",tp_refb);
		return -1;
	}

	/*if(write_dac_param_device(param)){
		printf("!#ERROR=Cannot write on device.!#");
		return -1;
	}else{
		
	}*/

	return 0;
	
}
