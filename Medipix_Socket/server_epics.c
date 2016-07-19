/*CGI FILE
--------------------------------------------------------------------------------
--!@brief Server UDP
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Socket server UDP paramentro da porta passada como argumento
--!
--! DETAILS:      bloco abre um socket para conexao UDP que recebe dados do 
--!               epics
--!
--!- Project Name: server_epics
--!- Module Name: server_epics.c
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 07/10/2014     
--!- Version: 1.0.0 (out/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "udp_func.h"

int main(int argc, char *argv[])
{
     struct sockaddr_in Rxsock_addr, Txsock_addr;
     int Rxsockfd, portno, valor, recv_len, slen = sizeof(Txsock_addr);
     char buffer[100], funcao[10], udp_buffer[150], exit[150], ip[16], mac[18];
     char *token;
	 float time;
	 int capture=0;
	 int i=0;

     STATUS status=none;
	 omr_parameters_t omr_param;
	 dac_param_t dac_param;
	 send_network_param_t send_param;
	 host_network_param_t host_param;
	 inetd_t inetd_param;
	 char ctpr_buff[256];

     if (argc < 2)
	 {
     	 //fprintf(stderr,"ERROR!, entre com a porta\n");
         return -1;
     }
	 // iniciando socket
     if ((Rxsockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	 {
         //fprintf(stderr,"ERROR!, abrindo socket!!!\n");
         return -1;
     }

     memset(&Rxsock_addr,'\0', sizeof(Rxsock_addr));
     portno = atoi(argv[1]);
	 Rxsock_addr.sin_family = AF_INET;
     Rxsock_addr.sin_port = htons(portno);
     Rxsock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

     if (bind(Rxsockfd, (struct sockaddr *) &Rxsock_addr,sizeof(Rxsock_addr)) < 0)
	 {
         //fprintf(stderr,"ERROR!, on binding!!!\n");
         return -1;
     }

     fprintf(stderr,"\nSocket Start!\nWaiting for command!!\n");
     //depois de aceita a conexao entra em loop infinito
     while(1)
     {
            // aloca e zera o buffer
     		memset(buffer,'\0',sizeof(buffer));

     		if ((recv_len = recvfrom(Rxsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &Txsock_addr, &slen)) < 0)
			{
		        //fprintf(stderr,"ERROR!, lendo socket\n");
				close(Rxsockfd);
                return -1;
	        }
			else
			{
				// lendo arquivos gravados em disco
				if(read_omrfile(OMR_FILE,&omr_param) <0)
     			{
	 	 			//fprintf(stderr,"File %s not found\n",OMR_FILE);
         			return -1;
	     		}
		 		if(read_dacfile(DAC_FILE,&dac_param) <0)
    	 		{
			 		//fprintf(stderr,"File %s not found\n",DAC_FILE);
    	     		return -1;
    	 		}
				if(read_sendfile(SEND_FILE,&send_param) <0)
    	 		{
			 		//fprintf(stderr,"File %s not found\n",SEND_FILE);
    	     		return -1;
    	 		}
				if(read_hostfile(HOST_FILE,&host_param) <0)
    	 		{
			 		//fprintf(stderr,"File %s not found\n",HOST_FILE);
    	     		return -1;
    	 		}
			    if(read_macfile(MAC_FILE,&inetd_param) <0)
    	 		{
			 		//fprintf(stderr,"File %s not found\n",HOST_FILE);
    	     		return -1;
    	 		}
			}
			//fprintf(stderr,"txip: %x\n",Txsock_addr.sin_addr.s_addr);
			//fprintf(stderr,"rxip: %x\n",Rxsock_addr.sin_addr.s_addr);
		    //fprintf(stderr,"Aqui esta sua mensagem: %s\n",buffer);

	     	token=strtok(buffer," ");
     		strcpy(funcao,token);
			if ((strcmp(funcao,"-time")==0)||(strcmp(funcao,"-gap")==0))
			{
				token=strtok(NULL," ");
     			time=atof(token);
			}
			else if((strcmp(funcao,"-send_ip")==0)||(strcmp(funcao,"-host_ip")==0)||(strcmp(funcao,"-host_net")==0))
			{
				token=strtok(NULL," ");
     			snprintf(ip,16,"%s",token);
			}
			else if(strcmp(funcao,"-send_mac")==0)
			{
				token=strtok(NULL," ");
     			snprintf(mac,18,"%s",token);
			}
			else
			{
				token=strtok(NULL," ");
     			valor=atoi(token);
			}
			
     		// procura qual dado foi alterado faz a validaçao
     		if (strcmp(funcao,"-reset")==0)
     		{
				sendto(Rxsockfd, "Rebooting System!", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
				capture=0;
				status=none;
     		}
			else if (strcmp(funcao,"-readomr")==0)
     		{
     			capture=0;
    	        status=read_omr;
     		}
			else if (strcmp(funcao,"-readdac")==0)
     		{
     			capture=0;
    	        status=read_dac;
     		}
			else if (strcmp(funcao,"-readnetwork")==0)
     		{
     			capture=0;
    	        status=read_network;
     		}
     		else if (strcmp(funcao,"-execbit")==0)
     		{
     			//fprintf(stderr,"valor %d\n", valor);
     		}
		    else if (strcmp(funcao,"-acquire")==0)
     		{
       			if (valor==1)
				{
                	capture=1;
  	        		status=write_omr;
				}
				else
				{
				    capture=0;
					status=none;
				}

     		}
     		else if (strcmp(funcao,"-stop")==0)
     		{
     			//fprintf(stderr,"valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-flatfieldcorrection")==0)
	     	{
     			sendto(Rxsockfd, "Nao se aplica", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                capture=0;
				status=none;
		    }
     		else if (strcmp(funcao,"-time")==0)
     		{
                if(time<0.001 || time >100.999)
    			{
					//fprintf(stderr,"!#ERROR!=[%f] Invalid time.!#\n",time);
			        status=none;
				}
			    else
    			{
					sprintf(omr_param.TIME,"%0.3f",time);
                    capture=0;
    	        	status=write_omr;
				}
     		}
			else if (strcmp(funcao,"-frames")==0)
		    {
     			if(valor<1 || valor >255)
    			{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid number of aquisitions.!#\n",valor);
			        status=none;
				}
			    else
    			{
					sprintf(omr_param.COUNTER,"%d",valor);
                    capture=0;
    	        	status=write_omr;
				}
		    }
			else if (strcmp(funcao,"-gap")==0)
		    {
     			if(time<0.001 || time >10.999)
    			{
					//fprintf(stderr,"!#ERROR!=[%f] Invalid value of gap.!#\n",time);
			        status=none;
				}
			    else
    			{
					sprintf(omr_param.GAP,"%0.3f",time);
                    capture=0;
    	        	status=write_omr;
				}
		    }
			else if (strcmp(funcao,"-readcounter")==0)
     		{
     			if(valor<0 || valor >2)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid Read Counter Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.READCOUNT,"%d",valor);
                    capture=0;
					status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-colormode")==0)
     		{
				if(valor<0 || valor >1)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid COLOURMODE Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.COLOURMODE,"%d",valor);
                    capture=0;
					status=write_omr;
				}
	     	}
     		else if (strcmp(funcao,"-gainmode")==0)
     		{
				if(valor<0 || valor >3)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid GAINMODE Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.GAINMODE,"%d",valor);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-summode")==0)
     		{
				if(valor<0 || valor >1)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid CSM_SPM Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.CSM_SPM,"%d",valor);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-readwrite")==0)
     		{
				if(valor>1 || valor <0)
    			{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid Protocol Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.CRW_SRW,"%d",valor);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-polarity")==0)
     		{
                if(valor>1 || valor <0)
    			{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid POLARITY Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.POLARITY,"%d",valor);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-clockext")==0)
     		{
		   		//fprintf(stderr,"valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-extbgap")==0)
	     	{
				if(valor<0 || valor >1)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid EXTBGSEL Setting.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(omr_param.EXTBGSEL,"%d",valor);
                    capture=0;
    		       	status=write_omr;
				}
		    }
     		else if (strcmp(funcao,"-bias")==0)
     		{
		   		sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                capture=0;
				status=none;
     		}
     		else if (strcmp(funcao,"-discsel")==0)
		    {
     			if(valor<0 || valor >1)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid EXTBGSEL Setting.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(omr_param.DISC_CSM_SPM,"%d",valor);
                    capture=0;
    		       	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-statuseq")==0)
	     	{
	     			sendto(Rxsockfd, "Nao se aplica", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                    capture=0;
					status=none;
     		}
     		else if (strcmp(funcao,"-enabletp")==0)
     		{
				if(valor<0 || valor >1)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid ENABLE_TP Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.ENABLE_TP,"%d",valor);
                    capture=0;
    	    	    status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-ctrange")==0)
	     	{
				if(valor<0 || valor >3)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid COUNTL !#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.COUNTL,"%d",valor);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-readports")==0)
     		{
	     		//fprintf(stderr,"valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-extdac")==0)
     		{
				if(valor<0 || valor >31)
                {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid EXTDAC Setting.!#\n",valor);
					status=none;
				}
                else
                {
					sprintf(omr_param.EXTDAC,"%d",valor);
                    capture=0;
   	        		status=write_omr;
				}
     		}
		    else if (strcmp(funcao,"-dacth0")==0)
     		{
				if(valor<0 || valor>511)
                {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
                else
                {
	            	sprintf(dac_param.THRESHOLD_0,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth1")==0)
     		{
				if(valor<0 || valor>511)
                {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
                else
                {
					sprintf(dac_param.THRESHOLD_1,"%03d",valor);
            		status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth2")==0)
     		{
				if(valor<0 || valor>511)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.THRESHOLD_2,"%03d",valor);
            		status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth3")==0)
		    {
				if(valor<0 || valor>511)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.THRESHOLD_3,"%03d",valor);
            		status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth4")==0)
     		{
				if(valor<0 || valor>511)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.THRESHOLD_4,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth5")==0)
     		{
				if(valor<0 || valor>511)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.THRESHOLD_5,"%03d",valor);
	            	status=write_dac;
				}
     		}
	     	else if (strcmp(funcao,"-dacth6")==0)
     		{
				if(valor<0 || valor>511)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.THRESHOLD_6,"%03d",valor);
	    	        status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacth7")==0)
     		{
				if(valor<0 || valor>511)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.THRESHOLD_7,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-preamp")==0)
     		{
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.PREAMP,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-ikrum")==0)
     		{
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.IKRUM,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-shaper")==0)
     		{
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.SHAPER,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-disc")==0)
		    {
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.DISC,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-discls")==0)
		    {
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.DISCLS,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacdiscl")==0)
		    {
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.DAC_DISCL,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-dacdisch")==0)
     		{
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.DAC_DISCH,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-delay")==0)
     		{
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.DELAY,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-tpbuffin")==0)
     		{
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.TP_BUFFER_IN,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-tpbuffout")==0)
     		{
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.TP_BUFFER_OUT,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-rpz")==0)
		    {
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.RPZ,"%03d",valor);
    	        	status=write_dac;
				}
     		}
		    else if (strcmp(funcao,"-gnd")==0)
		    {
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.GND,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-tpref")==0)
     		{
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.TP_REF,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-fbk")==0)
     		{
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.FBK,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-cas")==0)
     		{
				if(valor<0 || valor>255)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.CAS,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-tprefa")==0)
     		{
				if(valor<0 || valor>511)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.TP_REFA,"%03d",valor);
	    	        status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-tprefb")==0)
     		{
				if(valor<0 || valor>511)
				{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
				else
				{
					sprintf(dac_param.TP_REFB,"%03d",valor);
	            	status=write_dac;
				}
     		}
     		else if (strcmp(funcao,"-maskbit")==0)
     		{
     			//fprintf(stderr,"valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-testbit")==0)
     		{
     			//fprintf(stderr,"valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-adjl")==0)
     		{
     			//fprintf(stderr,"valor %d\n", valor);  
     		}
     		else if (strcmp(funcao,"-readout")==0)
     		{
     			//fprintf(stderr,"valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-adjh")==0)
     		{
     			//fprintf(stderr,"valor %d\n", valor);
     		}
     		else if (strcmp(funcao,"-colsel")==0)
     		{
				if(valor<0 || valor >1)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid COLUMBLOCKSEL Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.COLUMBLOCKSEL,"%d",valor);
                    capture=0;
    	        	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-rowsel")==0)
     		{
                if(valor<0 || valor >1)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid ROWBLOCKSEL Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.ROWBLOCKSEL,"%d",valor);
                    capture=0;
			        status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-colblock")==0)
     		{
				if(valor<0 || valor >7)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid COLUMNBLOCK Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.COLUMNBLOCK,"%d",valor);
                    capture=0;
	            	status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-rowblock")==0)
     		{
				if(valor<0 || valor >7)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid ROWBLOCK Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.ROWBLOCK,"%d",valor);
                    capture=0;
	    	        status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-tpcharge")==0)
     		{
     			sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                capture=0;
				status=none;
     		}
     		else if (strcmp(funcao,"-tpperiod")==0)
     		{
     			//sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                //capture=0;
				//status=none;
				if(valor<0 || valor >236)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid ROWBLOCK Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.PULSE_PERIOD,"%d",valor);
                    capture=0;
	    	        status=write_omr;
				}
     		}
		    else if (strcmp(funcao,"-tpnpulses")==0)
     		{
     			//sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                //capture=0;
				//status=none;
				if(valor<0 || valor >8192)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid ROWBLOCK Setting.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(omr_param.NPULSES,"%d",valor);
                    capture=0;
	    	        status=write_omr;
				}
     		}
     		else if (strcmp(funcao,"-tpspacing")==0)
     		{
     			sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                capture=0;
				status=none;
	     	}
     		else if (strcmp(funcao,"-eqalpha")==0)
		    {
     			sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                capture=0;
				status=none;
     		}
     		else if (strcmp(funcao,"-eqenergy")==0)
     		{
     			sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                capture=0;
				status=none;
     		}
     		else if (strcmp(funcao,"-eqacqtime")==0)
     		{
     			sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                capture=0;
				status=none;
     		}
     		else if (strcmp(funcao,"-eqtarget")==0)
     		{
     			sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                capture=0;
				status=none;
     		}
     		else if (strcmp(funcao,"-eqnloops")==0)
     		{
     			sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                capture=0;
				status=none;
     		}
     		else if (strcmp(funcao,"-eqtype")==0)
     		{
     			sendto(Rxsockfd, "ainda sem funcao", sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
                capture=0;
				status=none;
     		}
		 	else if (strcmp(funcao,"-ctpr")==0)
     		{
				if(valor<0 || valor>3)
                {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid threshold.!#\n",valor);
					status=none;
				}
                else
                {
	            	switch(valor)
					{
						case 0:
								memset(ctpr_buff,'0',sizeof(ctpr_buff));
								status=write_ctpr;
								break;
						case 1:
								memset(ctpr_buff,'1',sizeof(ctpr_buff));
								status=write_ctpr;
								break;
						case 2:
								for(i=0;i<256;i++)
								{
									if(i%2==0)
									{
										ctpr_buff[i]='0';
									}
									else
									{
										ctpr_buff[i]='1';
									}
								}
								status=write_ctpr;
								break;
						case 3:
								for(i=0;i<256;i++)
								{
									if(i%2==0)
									{
										ctpr_buff[i]='1';
									}
									else
									{
										ctpr_buff[i]='0';
									}
								}
								status=write_ctpr;
								break;
				    }
				}
     		}
			else if (strcmp(funcao,"-host_ip")==0)
     		{
				if(isValidIpAddress(ip)==1)
				{
					sprintf(host_param.ip_address,"%s",ip);
					status=write_host;
				}
				else
				{
					//fprintf(stderr,"!#ERROR!=[%s] Invalid IP.!#\n", ip);
					status=none;
				}
     		}
			else if (strcmp(funcao,"-host_net")==0)
     		{
                if(isValidIpAddress(ip)==1)
				{
					sprintf(host_param.mask,"%s",ip);
					status=write_host;
				}
				else
				{
					//fprintf(stderr,"!#ERROR!=[%s] Invalid IP.!#\n", ip);
					status=none;
				}
     		}
			else if (strcmp(funcao,"-send_ip")==0)
     		{
                if(isValidIpAddress(ip)==1)
				{
					sprintf(send_param.ip_send,"%s",ip);
					status=write_send;
				}
				else
				{
					//fprintf(stderr,"!#ERROR!=[%s] Invalid IP.!#\n", ip);
					status=none;
				}
     		}
			else if (strcmp(funcao,"-send_port")==0)
     		{
                if(valor<1 || valor >65536)
			    {
					//fprintf(stderr,"!#ERROR!=[%d] Invalid PORT.!#\n",valor);
					status=none;
				}
			    else
			    {
					sprintf(send_param.port_send,"%d",valor);
	            	status=write_send;
				}
     		}
			else if (strcmp(funcao,"-send_mac")==0)
     		{
				if(isValidMacAddress(mac)==1)
				{
					sprintf(send_param.mac_send,"%s",mac);
					status=write_send;
				}
				else
				{
					//fprintf(stderr,"!#ERROR!=[%s] Invalid MAC.!#\n", mac);
					status=none;
				}
     		}
			else if (strcmp(funcao,"-modesel")==0)
     		{
                if(valor<0 || valor >7)
    			{
					//fprintf(stderr,"!#ERROR!=[%d] Invalid opmode.!#\n",valor);
			        status=none;
				}
			    else
    			{
					if(valor==0)
					{
						sprintf(omr_param.MODE,"%d",0);
						sprintf(omr_param.READCOUNT,"%d",0);
					}
					else if(valor==1)
					{
						sprintf(omr_param.MODE,"%d",1);
						sprintf(omr_param.READCOUNT,"%d",1);
					}
					else if(valor==6)
					{
						sprintf(omr_param.MODE,"%d",6);
    	        		status=read_dac;
					}
					else
					{		
						sprintf(omr_param.MODE,"%d",valor);
						status=write_omr;
					}
					capture=0;					
				}
    		}
     		else
     		{
            	status=none;
	 		}
			// verifica se algum dado foi alterado e passa para gravaçao
     		switch(status)
     		{
	 			case 0:                   
						  if(capture==1)
						  {
						  		if(strcmp(omr_param.COUNTL,"3")==0)
								{
									strcpy(omr_param.MODE,"0");
									//strcpy(omr_param.READCOUNT,"0");
								}
								else
								{
									if(strcmp(omr_param.READCOUNT,"1")==0)
									{
										strcpy(omr_param.MODE,"1");
									}
									else
									{
										strcpy(omr_param.MODE,"0");
									}
								}
								capture=0;
						  }
						  else
						  {
								strcpy(omr_param.MODE,"7");
								capture=0;
						  }
                          validate_omr_param(omr_param);
						  return_omr_udp(omr_param, udp_buffer);
						  if(strcmp(omr_param.MODE,"7")==0)
						  {
							  sendto(Rxsockfd, udp_buffer, sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
						  }
						  else
						  {
							  sendto(Rxsockfd, "Flawless Victory", 16, 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
						  }
						  status=none;
            	          break;
	            case 1:
					      strcpy(omr_param.MODE,"4");
                          validate_dac_param(dac_param);
						  return_dac_udp(dac_param, udp_buffer);
						  sendto(Rxsockfd, udp_buffer, sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
						  status=none;
                          break;
				case 2:
						  validate_send_param(send_param,host_param,inetd_param);
						  return_network_udp(send_param, host_param, udp_buffer);
  		  				  sendto(Rxsockfd, udp_buffer, sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
						  status=none;
                          break;
				case 3:
						  validate_host_param(host_param);
						  return_network_udp(send_param, host_param, udp_buffer);
  		  				  sendto(Rxsockfd, udp_buffer, sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
						  status=none;
                          break;
				case 4:
                          strcpy(omr_param.MODE,"7");
						  return_omr_udp(omr_param, udp_buffer);
						  memset(exit,'\0',sizeof(exit));
						  strcpy(exit, udp_buffer);
  		  				  sendto(Rxsockfd, udp_buffer, sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
						  status=none;
                          break;
				case 5:
                          strcpy(omr_param.MODE,"6");
						  return_dac_udp(dac_param, udp_buffer);
						  memset(exit,'\0',sizeof(exit));
						  strcpy(exit, udp_buffer);
  		  				  sendto(Rxsockfd, udp_buffer, sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
						  status=none;
                          break;
				case 6:
  		  				  return_network_udp(send_param, host_param, udp_buffer);
  		  				  sendto(Rxsockfd, udp_buffer, sizeof(udp_buffer), 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
						  status=none;
                          break;
				case 7:
  		  				  if(write_ctpr_param_device(ctpr_buff))
						  {
						  	//printf("!#ERROR=Cannot write on device.!#\n");
						  }
						  sendto(Rxsockfd, "CTPR Dispatch", 16, 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
						  status=none;
                          break;
    	        default:
    	                  //fprintf(stderr,"opcao nao encontrada!!!\n");
  		  				  sendto(Rxsockfd, "Invalid Option", 16, 0 , (struct sockaddr *) &Txsock_addr, sizeof(Txsock_addr));
						  status=none;
                          break;
     		}
     }
     close(Rxsockfd);

     return 0; 
}


