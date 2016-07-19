/*C FILE
--------------------------------------------------------------------------------
--!@brief PERSIST C FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! FUNCOES DE ESCRITA E LEITURA DE PARAMETROS GRAVADOS EM TEXTO
--!
--! DETAILS:      
--!
--!- Project Name: persist
--!- Module Name: persist.c
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
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "global.h"
#include "persist.h"
#include "interface_uc.h"

#define	MAXLEN 	20



int write_sendfile(const char* filename,send_network_param_t* param)
{
  FILE *fp;
  int i=0;
  fp=fopen(filename,"w+");
  if(fp==NULL)
  {    
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  } 
  fprintf(fp,"TX_SETUP\n");
  fprintf(fp,"%s\n",param->ip_send);
  fprintf(fp,"%s\n",param->port_send);
  fprintf(fp,"%s\n",param->mac_send);
  
  fclose(fp);
  return 0;  
}

int read_sendfile(const char* filename,send_network_param_t* param)
{
  FILE *fp;
  char buffer[MAXLEN];
  int line=0;
  fp = fopen(filename,"r+");
  if(fp==NULL)
  {
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  }
  
  while(fgets(buffer,sizeof(buffer),fp) != NULL)
  {  	
  	buffer[strlen(buffer)-1]='\0';  	
  	switch(line)
    {
    case 0:
        break;
  	case 1:  		
  		strncpy(param->ip_send,buffer,sizeof(param->ip_send));
  		break;
  	case 2:
  		strncpy(param->port_send,buffer,sizeof(param->port_send));
  		break;
  	case 3:
  		strncpy(param->mac_send,buffer,sizeof(param->mac_send));
  		break;  		
  	default:
  		break;
  	}
  	line++;
  }  
  fclose(fp);
  usleep(100);
  return 0;
}


int write_dacfile(const char* filename,dac_param_t* param)
{
  FILE *fp;
  int i=0;
  fp=fopen(filename,"w+");
  if(fp==NULL)
  {    
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  } 
  fprintf(fp,"DACS_PARAMETERS\n");
  fprintf(fp,"%s\n",param->THRESHOLD_0);
  fprintf(fp,"%s\n",param->THRESHOLD_1);
  fprintf(fp,"%s\n",param->THRESHOLD_2);
  fprintf(fp,"%s\n",param->THRESHOLD_3);
  fprintf(fp,"%s\n",param->THRESHOLD_4);
  fprintf(fp,"%s\n",param->THRESHOLD_5);
  fprintf(fp,"%s\n",param->THRESHOLD_6);
  fprintf(fp,"%s\n",param->THRESHOLD_7);
  fprintf(fp,"%s\n",param->PREAMP);
  fprintf(fp,"%s\n",param->IKRUM);
  fprintf(fp,"%s\n",param->SHAPER);
  fprintf(fp,"%s\n",param->DISC);
  fprintf(fp,"%s\n",param->DISCLS);
  fprintf(fp,"%s\n",param->SHAPER_TEST);
  fprintf(fp,"%s\n",param->DAC_DISCL);
  fprintf(fp,"%s\n",param->DAC_TEST);
  fprintf(fp,"%s\n",param->DAC_DISCH);
  fprintf(fp,"%s\n",param->DELAY);
  fprintf(fp,"%s\n",param->TP_BUFFER_IN);
  fprintf(fp,"%s\n",param->TP_BUFFER_OUT);
  fprintf(fp,"%s\n",param->RPZ);
  fprintf(fp,"%s\n",param->GND);
  fprintf(fp,"%s\n",param->TP_REF);
  fprintf(fp,"%s\n",param->FBK);
  fprintf(fp,"%s\n",param->CAS);
  fprintf(fp,"%s\n",param->TP_REFA);
  fprintf(fp,"%s\n",param->TP_REFB);
  
  fclose(fp);
  return 0;  
}

int read_dacfile(const char* filename,dac_param_t* param)
{
  FILE *fp;
  char buffer[MAXLEN];
  int line=0;
  fp = fopen(filename,"r+");
  if(fp==NULL)
  {
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  }
  
  while(fgets(buffer,sizeof(buffer),fp) != NULL)
  {  	
  	buffer[strlen(buffer)-1]='\0';  	
  	switch(line)
    {
    case 0:
        break;
  	case 1:  		
  		strncpy(param->THRESHOLD_0,buffer,sizeof(param->THRESHOLD_0));
  		break;
  	case 2:
  		strncpy(param->THRESHOLD_1,buffer,sizeof(param->THRESHOLD_1));
  		break;
  	case 3:
  		strncpy(param->THRESHOLD_2,buffer,sizeof(param->THRESHOLD_2));
  		break;
  	case 4:
  		strncpy(param->THRESHOLD_3,buffer,sizeof(param->THRESHOLD_3));
  		break;
  	case 5:
  		strncpy(param->THRESHOLD_4,buffer,sizeof(param->THRESHOLD_4));
  		break;
  	case 6:
  		strncpy(param->THRESHOLD_5,buffer,sizeof(param->THRESHOLD_5));
  		break;
  	case 7:
  		strncpy(param->THRESHOLD_6,buffer,sizeof(param->THRESHOLD_6));
  		break;
  	case 8:
  		strncpy(param->THRESHOLD_7,buffer,sizeof(param->THRESHOLD_7));
  		break;
    case 9:
  		strncpy(param->PREAMP,buffer,sizeof(param->PREAMP));
 		break;
    case 10:
  		strncpy(param->IKRUM,buffer,sizeof(param->IKRUM));
  		break;
    case 11:
  		strncpy(param->SHAPER,buffer,sizeof(param->SHAPER));
  		break;
  	case 12:
  		strncpy(param->DISC,buffer,sizeof(param->DISC));
  		break;
  	case 13:
  		strncpy(param->DISCLS,buffer,sizeof(param->DISCLS));
  		break;
  	case 14:
  		strncpy(param->SHAPER_TEST,buffer,sizeof(param->SHAPER_TEST));
  		break;
  	case 15:
  		strncpy(param->DAC_DISCL,buffer,sizeof(param->DAC_DISCL));
  		break;
  	case 16:
  		strncpy(param->DAC_TEST,buffer,sizeof(param->DAC_TEST));
  		break;
  	case 17:
  		strncpy(param->DAC_DISCH,buffer,sizeof(param->DAC_DISCH));
  		break;
  	case 18:
  		strncpy(param->DELAY,buffer,sizeof(param->DELAY));
  		break;
  	case 19:
  		strncpy(param->TP_BUFFER_IN,buffer,sizeof(param->TP_BUFFER_IN));
  		break;
    case 20:
  		strncpy(param->TP_BUFFER_OUT,buffer,sizeof(param->TP_BUFFER_OUT));
  		break;
  	case 21:
  		strncpy(param->RPZ,buffer,sizeof(param->RPZ));
  		break;
  	case 22:
  		strncpy(param->GND,buffer,sizeof(param->GND));
  		break;
  	case 23:
  		strncpy(param->TP_REF,buffer,sizeof(param->TP_REF));
  		break;
    case 24:
  		strncpy(param->FBK,buffer,sizeof(param->FBK));
  		break;
  	case 25:
  		strncpy(param->CAS,buffer,sizeof(param->CAS));
  		break;
  	case 26:
  		strncpy(param->TP_REFA,buffer,sizeof(param->TP_REFA));
  		break;
  	case 27:
  		strncpy(param->TP_REFB,buffer,sizeof(param->TP_REFB));
  		break;
  		
  	default:
  		break;
  	}
  	line++;
  }  
  fclose(fp);
  usleep(100);
  return 0;
}

int write_omrfile(const char* filename,omr_parameters_t* param)
{
  FILE *fp;
  int i=0;
  fp = fopen(filename,"w+");
  if(fp==NULL)
  {    
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  } 
  fprintf(fp,"OMR_PARAMETERS\n");
  fprintf(fp,"%s\n",param->MODE);
  fprintf(fp,"%s\n",param->CRW_SRW);
  fprintf(fp,"%s\n",param->POLARITY);
  fprintf(fp,"%s\n",param->PS);
  fprintf(fp,"%s\n",param->DISC_CSM_SPM);
  fprintf(fp,"%s\n",param->ENABLE_TP);
  fprintf(fp,"%s\n",param->COUNTL);
  fprintf(fp,"%s\n",param->COLUMNBLOCK);
  fprintf(fp,"%s\n",param->COLUMBLOCKSEL);
  fprintf(fp,"%s\n",param->ROWBLOCK);
  fprintf(fp,"%s\n",param->ROWBLOCKSEL);
  fprintf(fp,"%s\n",param->EQUALIZATION);
  fprintf(fp,"%s\n",param->COLOURMODE);
  fprintf(fp,"%s\n",param->CSM_SPM);
  fprintf(fp,"%s\n",param->INFOHEADER);
  fprintf(fp,"%s\n",param->GAINMODE);
  fprintf(fp,"%s\n",param->SENSEDAC);
  fprintf(fp,"%s\n",param->EXTDAC);
  fprintf(fp,"%s\n",param->EXTBGSEL);
  fprintf(fp,"%s\n",param->TIME);
  fprintf(fp,"%s\n",param->COUNTER);
  fprintf(fp,"%s\n",param->GAP);
  fprintf(fp,"%s\n",param->READCOUNT);
  fprintf(fp,"%s\n",param->PULSE_PERIOD);
  fprintf(fp,"%s\n",param->NPULSES);

  fclose(fp);
  return 0;  
}

int read_omrfile(const char* filename,omr_parameters_t* param)
{
  FILE *fp;
  char buffer[MAXLEN];
  int line=0;
  fp = fopen(filename,"r+");
  if(fp==NULL)
  {
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  }
  
  while(fgets(buffer,sizeof(buffer),fp) != NULL)
  {  	
  	buffer[strlen(buffer)-1]='\0';  	
  	switch(line)
    {
    case 0:
   		strncpy(param->LABEL,"OMR_PARAMETERS",sizeof(param->LABEL));
  	case 1:  		
  		strncpy(param->MODE,buffer,sizeof(param->MODE));
  		break;
  	case 2:
  		strncpy(param->CRW_SRW,buffer,sizeof(param->CRW_SRW));
  		break;
  	case 3:
  		strncpy(param->POLARITY,buffer,sizeof(param->POLARITY));
  		break;
  	case 4:
  		strncpy(param->PS,buffer,sizeof(param->PS));
  		break;
  	case 5:
  		strncpy(param->DISC_CSM_SPM,buffer,sizeof(param->DISC_CSM_SPM));
  		break;
  	case 6:
  		strncpy(param->ENABLE_TP,buffer,sizeof(param->ENABLE_TP));
  		break;
  	case 7:
  		strncpy(param->COUNTL,buffer,sizeof(param->COUNTL));
  		break;
  	case 8:
  		strncpy(param->COLUMNBLOCK,buffer,sizeof(param->COLUMNBLOCK));
  		break;
    case 9:
  		strncpy(param->COLUMBLOCKSEL,buffer,sizeof(param->COLUMBLOCKSEL));
 		break;
    case 10:
  		strncpy(param->ROWBLOCK,buffer,sizeof(param->ROWBLOCK));
  		break;
    case 11:
  		strncpy(param->ROWBLOCKSEL,buffer,sizeof(param->ROWBLOCKSEL));
  		break;
  	case 12:
  		strncpy(param->EQUALIZATION,buffer,sizeof(param->EQUALIZATION));
  		break;
  	case 13:
  		strncpy(param->COLOURMODE,buffer,sizeof(param->COLOURMODE));
  		break;
  	case 14:
  		strncpy(param->CSM_SPM,buffer,sizeof(param->CSM_SPM));
  		break;
  	case 15:
  		strncpy(param->INFOHEADER,buffer,sizeof(param->INFOHEADER));
  		break;
  	case 16:
  		strncpy(param->GAINMODE,buffer,sizeof(param->GAINMODE));
  		break;
  	case 17:
  		strncpy(param->SENSEDAC,buffer,sizeof(param->SENSEDAC));
  		break;
  	case 18:
  		strncpy(param->EXTDAC,buffer,sizeof(param->EXTDAC));
  		break;
  	case 19:
  		strncpy(param->EXTBGSEL,buffer,sizeof(param->EXTBGSEL));
  		break;
	case 20:
  		strncpy(param->TIME,buffer,sizeof(param->TIME));
  		break;
	case 21:
  		strncpy(param->COUNTER,buffer,sizeof(param->COUNTER));
  		break;
	case 22:
  		strncpy(param->GAP,buffer,sizeof(param->GAP));
  		break;
	case 23:
  		strncpy(param->READCOUNT,buffer,sizeof(param->READCOUNT));
  		break;
	case 24:
  		strncpy(param->PULSE_PERIOD,buffer,sizeof(param->PULSE_PERIOD));
  		break;
	case 25:
  		strncpy(param->NPULSES,buffer,sizeof(param->NPULSES));
  		break;
  		
  	default:
  		break;
  	}
  	line++;
  }  
  fclose(fp);
  usleep(100);
  return 0;
}


int write_hostfile(const char* filename,host_network_param_t* param)
{
  FILE *fp;
  int i=0;
  fp = fopen(filename,"w+");
  if(fp==NULL)
  {
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  }
  
  fprintf(fp,"%s\n",param->ip_address);
  fprintf(fp,"%s\n",param->mask);
  fprintf(fp,"%s\n",param->gateway);  
  printf("%s\n",param->ip_address);
  printf("%s\n",param->mask);
  printf("%s\n",param->gateway);
  fclose(fp);
  return 0;  
}

int read_hostfile(const char* filename, host_network_param_t* param)
{
  FILE *fp;
  char buffer[MAXLEN];
  int line=0;
    fp = fopen(filename,"r+");
  if(fp==NULL)
  {
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  }
  
  while(fgets(buffer,sizeof(buffer),fp) != NULL)
  {
  	buffer[strlen(buffer)-1]='\0';  	
  	switch(line)
    {
  	case 0:  		
  		strncpy(param->ip_address,buffer,sizeof(param->ip_address));
  		break;
  	case 1:
  		strncpy(param->mask,buffer,sizeof(param->mask));
  		break;
  	case 2:
  		strncpy(param->gateway,buffer,sizeof(param->gateway));
  		break;  	
  	default:
  		break;
  	}
  	line++;
  }  
  fclose(fp);
  return 0;
}


int write_macfile(const char* filename,inetd_t* param)
{
  FILE *fp;
  int i=0;
  fp = fopen(filename,"w+");
  if(fp==NULL)
  {
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  }
  
  fprintf(fp,"%s\n",param->host_mac_address_host);
  fprintf(fp,"%s\n",param->host_mac_address_stream);  
  fclose(fp);
  return 0;  
}

int read_macfile(const char* filename, inetd_t* param)
{
  FILE *fp;
  char buffer[MAXLEN];
  int line=0;
    fp = fopen(filename,"r+");
  if(fp==NULL)
  {
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  }
  
  while(fgets(buffer,sizeof(buffer),fp) != NULL)
  {
  	buffer[strlen(buffer)-1]='\0';  	
  	switch(line)
    {
  	case 0:  		
  		strncpy(param->host_mac_address_host,buffer,sizeof(param->host_mac_address_host));
  		break;
  	case 1:
  		strncpy(param->host_mac_address_stream,buffer,sizeof(param->host_mac_address_stream));
  		break;  	
  	default:
  		break;
    }
  	line++;
  }
  fclose(fp);
  return 0;  
}

int read_dhcpfile(char *mac_gateway)
{
  FILE *fp;
  char buffer[30];
  int line=0;
  fp = fopen("/etc/dhcpc/dhcpcd-eth0.info","r+");
  if(fp==NULL)
  {
      fprintf(stderr,"Error on opening file /etc/dhcpc/dhcpcd-eth0.info.\n");
      return -EIO;
  }
  
  while(fgets(buffer,sizeof(buffer),fp) != NULL)
  {  	
  	buffer[strlen(buffer)-1]='\0';  	
  	switch(line)
    {
		case 0:
  			break;
		case 1:
  			break;
		case 2:
  			break;
		case 3:
  			break;
		case 4:
  			break;
		case 5:
  			break;
		case 6:
  			break;
		case 7:
  			break;
		case 8:
  			break;
		case 9:
  			break;
		case 10:
  			break;
    	case 11:
  			strcpy(mac_gateway,buffer);	
			//fprintf(stderr,"%s\n",mac_gateway);		
  			break;
		case 12:
  			break;
  		
  		default:
  			break;
  	}
  	line++;
  }  
  fclose(fp);
  usleep(100);
  return 0;
}

int read_rcfile( host_network_param_t *host_param,  inetd_t *inetd_param)
{
 	FILE *fp;
 	char buffer[MAXLEN];
 	int line=0;
 	char filename[]="/etc/rc";
 	fp = fopen(filename,"r+");
 	if(fp==NULL)
     {
 	    fprintf(stderr,"Error on opening file %s.\n",filename);
 	    return -EIO;
 	}
	if(host_param == NULL && inetd_param == NULL)
    {
		return -1;
	}
	while(fgets(buffer,sizeof(buffer),fp) != NULL)
    {
		buffer[strlen(buffer)-1]='\0';  	
		switch(line)
        {
		case 0:
			if(inetd_param != NULL)
				//strncpy(inetd_param->hostname,buffer,sizeof(inetd_param->hostname));
		break;
		
		case 4:
			break;
		}
	}
}

int write_rcfile(const host_network_param_t *host_param,  const inetd_t *inetd_param)
{
 	FILE *fp;
 	char buffer[MAXLEN];
 	int line=0;
 	char filename[]="/etc/rc";
 	fp = fopen(filename,"w+");
 	if(fp==NULL)
     {
 	    fprintf(stderr,"Error on opening file %s.\n",filename);
 	    return -EIO;
 	}
	if(host_param == NULL && inetd_param == NULL)
    {
		fprintf(stderr,"Null pointer\n");
		return -1;
	}
	
	fprintf(fp,"hostname Medipix Controller 1.0\n");
	fprintf(fp,"ifconfig eth0 hw ether %s\n",inetd_param-> host_mac_address_host);	
	fprintf(fp,"dhcpcd eth0\n");
	//fprintf(fp,"ifconfig eth0 %s netmask %s\n", host_param->ip_address, host_param->mask);
	fprintf(fp,"mount -t proc proc /proc -o noexec,nosuid,nodev\n");
	fprintf(fp,"mount -t devpts devpts /dev/pts -o noexec,nosuid\n");
	fprintf(fp,"mount -t sysfs sysfs /sys -o noexec,nosuid,nodev\n");
	fprintf(fp,"ifconfig lo 127.0.0.1\n");
	fprintf(fp,"route add -net 127.0.0.0 netmask 255.0.0.0 lo\n");
	fprintf(fp,"route add default gw %s eth0\n", host_param->gateway);
	fprintf(fp,"./home/init_medipix\n");
	fprintf(fp,"./home/server_epics 4000&\n");
	fprintf(fp,"./home/read_mac\n");
	fprintf(fp,"boa -d&\n");	
	fprintf(fp,"cat /etc/motd\n");
	fclose(fp);
	return 0;

}

int update_rc(const host_network_param_t *host_param)
{
	inetd_t	inetd_param;
	
	if(read_macfile(MAC_FILE,&inetd_param) !=0)
    {
			fprintf(stderr,"Error on opening mac file\n");
        	return -1;
    }
	if(write_rcfile(host_param,&inetd_param)!=0)
    {
			fprintf(stderr,"Error on write rc file\n");
		    return -1;
	}
	return 0;
}

