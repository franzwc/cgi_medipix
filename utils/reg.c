/*C FILE
--------------------------------------------------------------------------------
--!@brief REG FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! FUNÇOES PARA ESCRITA E LEITURA DOS PARAMETROS NO HARDWARE
--!
--! DETAILS:      
--!
--!- Project Name: reg
--!- Module Name: reg.c
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
#include "reg.h"
#include "interface_uc.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>

#define	CTS_NX_EN		50
#define	CTS_CR_EN		256
#define DEV_IO_ON		263
#define DEV_IO_OFF		264

#define IORD(address, offset) (*(volatile unsigned *)(((address)| 0x80000000)+4*(offset)))
#define IOWR(address, offset, value) (*(volatile unsigned *)(((address)|0x80000000)+4*(offset)))=(value)

int write_omr_param_device(const omr_parameters_t* param)
{
    int fd;
	char cts[265];
    int wr_count;
	float gap;
	double ftime;

	ftime=atof(param->TIME);
	gap=atof(param->GAP);

	//fprintf(stderr,"string %s\n\n", param->TIME);
	//fprintf(stderr,"time %010.6f\n\n", ftime);  %03s

    // CTS
    memset(cts, 0x00, 265);
    snprintf(cts, sizeof(cts), "\n\nOMR_PARAMETERS%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%010.6f%05s%07.3f%s%03s%04s\n\n", param->MODE, param->CRW_SRW,param->POLARITY,param->PS,param->DISC_CSM_SPM,param->ENABLE_TP,param->COUNTL,param->COLUMNBLOCK,param->COLUMBLOCKSEL,param->ROWBLOCK,param->ROWBLOCKSEL,param->EQUALIZATION,param->COLOURMODE,param->CSM_SPM,param->INFOHEADER,param->GAINMODE,"00","00","0",ftime,param->COUNTER,gap,param->READCOUNT,param->PULSE_PERIOD,param->NPULSES);


//    snprintf(cts, sizeof(cts), "\n\nOMR_PARAMETERS%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%010.6f%03s%07.3f%s%03s%04s\n\n", param->MODE, param->CRW_SRW,param->POLARITY,param->PS,param->DISC_CSM_SPM,param->ENABLE_TP,param->COUNTL,param->COLUMNBLOCK,param->COLUMBLOCKSEL,param->ROWBLOCK,param->ROWBLOCKSEL,param->EQUALIZATION,param->COLOURMODE,param->CSM_SPM,param->INFOHEADER,param->GAINMODE,"00","00","0",ftime,param->COUNTER,gap,param->READCOUNT,param->PULSE_PERIOD,param->NPULSES);

	/*fprintf(stderr,"OMR LABEL %s\n", param->LABEL);
	fprintf(stderr,"OMR MODE %s\n", param->MODE);
	fprintf(stderr,"OMR CRW_SRW %s\n", param->CRW_SRW);
	fprintf(stderr,"OMR POLARITY %s\n", param->POLARITY);
	fprintf(stderr,"OMR PS %s\n", param->PS);
	fprintf(stderr,"OMR DISC_CSM_SPM %s\n", param->DISC_CSM_SPM);
	fprintf(stderr,"OMR ENABLE_TP %s\n", param->ENABLE_TP);
	fprintf(stderr,"OMR COUNTL %s\n", param->COUNTL);
	fprintf(stderr,"OMR COLUMNBLOCK %s\n", param->COLUMNBLOCK);
	fprintf(stderr,"OMR COLUMBLOCKSEL %s\n", param->COLUMBLOCKSEL);
	fprintf(stderr,"OMR ROWBLOCK %s\n", param->ROWBLOCK);
	fprintf(stderr,"OMR ROWBLOCKSEL %s\n", param->ROWBLOCKSEL);
	fprintf(stderr,"OMR EQUALIZATION %s\n", param->EQUALIZATION);
	fprintf(stderr,"OMR COLOURMODE %s\n", param->COLOURMODE);
	fprintf(stderr,"OMR CSM_SPM %s\n", param->CSM_SPM);
	fprintf(stderr,"OMR INFOHEADER %s\n", param->INFOHEADER);
	fprintf(stderr,"OMR GAINMODE %s\n", param->GAINMODE);
	fprintf(stderr,"OMR ftime %f\n", ftime);
	fprintf(stderr,"OMR READ COUNTER %s\n", param->READCOUNT);*/


	// write to device
	if ((fd = open("/dev/medipix", O_RDWR)) == -1) {
		printf("Error! Failed to open MEDIPIX DEV!\n");
		return -1;
	}
    usleep(100);
	ioctl(fd, CTS_CR_EN, 0);
	lseek(fd, 0, SEEK_SET);
	wr_count = write(fd, cts, 265);
    usleep(100);
    close(fd);

  return 0;
}

int write_dac_param_device(const dac_param_t* param)
{
    int fd;
	char cts[265];
    int wr_count;
    // CTS
    memset(cts, 0x00, 265);
    snprintf(cts, sizeof(cts), "\n\nDAC%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s%03s\n\n", param->THRESHOLD_0,param->THRESHOLD_1,param->THRESHOLD_2,param->THRESHOLD_3,param->THRESHOLD_4,param->THRESHOLD_5,param->THRESHOLD_6,param->THRESHOLD_7,param->PREAMP,param->IKRUM,param->SHAPER,param->DISC,param->DISCLS,param->SHAPER_TEST,param->DAC_DISCL,param->DAC_TEST,param->DAC_DISCH,param->DELAY,param->TP_BUFFER_IN,param->TP_BUFFER_OUT,param->RPZ,param->GND,param->TP_REF,param->FBK,param->CAS,param->TP_REFA,param->TP_REFB);

	/*printf("DAC THRESHOLD_0 %s\n", param->THRESHOLD_0);
	printf("DAC THRESHOLD_1 %s\n", param->THRESHOLD_1);
	printf("DAC THRESHOLD_2 %s\n", param->THRESHOLD_2);
	printf("DAC THRESHOLD_3 %s\n", param->THRESHOLD_3);
	printf("DAC THRESHOLD_4 %s\n", param->THRESHOLD_4);
	printf("DAC THRESHOLD_5 %s\n", param->THRESHOLD_5);
	printf("DAC THRESHOLD_6 %s\n", param->THRESHOLD_6);
	printf("DAC THRESHOLD_7 %s\n", param->THRESHOLD_7);
	printf("DAC PREAMP %s\n", param->PREAMP);
	printf("DAC IKRUM %s\n", param->IKRUM);
	printf("DAC SHAPER %s\n", param->SHAPER);
	printf("DAC DISC %s\n", param->DISC);
	printf("DAC DISCLS %s\n", param->DISCLS);
	printf("DAC SHAPER_TEST %s\n", param->SHAPER_TEST);
	printf("DAC DAC_DISCL %s\n", param->DAC_DISCL);
	printf("DAC DAC_TEST %s\n", param->DAC_TEST);
	printf("DAC DAC_DISCH %s\n", param->DAC_DISCH);
	printf("DAC DELAY %s\n", param->DELAY);
	printf("DAC TP_BUFFER_IN %s\n", param->TP_BUFFER_IN);
	printf("DAC TP_BUFFER_OUT %s\n", param->TP_BUFFER_OUT);
	printf("DAC RPZ %s\n", param->RPZ);
	printf("DAC GND %s\n", param->GND);
	printf("DAC TP_REF %s\n", param->TP_REF);
	printf("DAC FBK %s\n", param->FBK);
	printf("DAC CAS %s\n", param->CAS);
	printf("DAC TP_REFA %s\n", param->TP_REFA);
	printf("DAC TP_REFB %s\n", param->TP_REFB);*/

	// write to device
	if ((fd = open("/dev/medipix", O_RDWR)) == -1) {
		printf("Error! Failed to open MEDIPIX DEV!\n");
		return -1;
	}
    usleep(100);
	ioctl(fd, CTS_CR_EN, 0);
	lseek(fd, 0, SEEK_SET);
	wr_count = write(fd, cts, 265);
    usleep(100);
    close(fd);

  return 0;
}

int write_ctpr_param_device(char *interface)
{
    int fd;
	char cts[265];
    int wr_count;
    // CTS
    memset(cts, 0x00, 265);
    snprintf(cts, sizeof(cts), "\n\nCT%s\n\n", interface);

	//fprintf(stderr,"%s",cts);
	// write to device
	if ((fd = open("/dev/medipix", O_RDWR)) == -1) {
		printf("Error! Failed to open MEDIPIX DEV!\n");
		return -1;
	}
    usleep(100);
	ioctl(fd, CTS_CR_EN, 0);
	lseek(fd, 0, SEEK_SET);
	wr_count = write(fd, cts, 265);
    usleep(100);
    close(fd);

  return 0;
}

int write_send_param_device(const send_network_param_t* param, const host_network_param_t* param_host, const inetd_t* param_mac_host)
{
    int fd;
	char cts[265];
    int wr_count;
    char aux[4];
    int IP1=0;
    int IP2=0;
    int IP3=0;
    int IP4=0;
    int port=0; 
    int MAC1=0;
    int MAC2=0;
    int MAC3=0;
    int MAC4=0;
    int MAC5=0;
    int MAC6=0;
	int HOST_IP1=0;
    int HOST_IP2=0;
    int HOST_IP3=0;
    int HOST_IP4=0;
    int HOST_port=0; 
    int HOST_MAC1=0;
    int HOST_MAC2=0;
    int HOST_MAC3=0;
    int HOST_MAC4=0;
    int HOST_MAC5=0;
    int HOST_MAC6=0;
    char* token;

    // divide a mensagem em tokens
	token=(char *)strtok(param->ip_send,".");
    IP1=atoi(token);
    token=(char *)strtok(NULL,".");
	IP2=atoi(token);
    token=(char *)strtok(NULL,".");
	IP3=atoi(token);
    token=(char *)strtok(NULL,".");
	IP4=atoi(token);

    port=atoi(param->port_send);

    // divide a mensagem em tokens
	token=(char *)strtok(param->mac_send,":");    
    MAC1=(int)strtol(token,NULL,16);
    token=(char *)strtok(NULL,":");
	MAC2=(int)strtol(token,NULL,16);
    token=(char *)strtok(NULL,":");
	MAC3=(int)strtol(token,NULL,16);
    token=(char *)strtok(NULL,":");
	MAC4=(int)strtol(token,NULL,16);
    token=(char *)strtok(NULL,":");
	MAC5=(int)strtol(token,NULL,16);
    token=(char *)strtok(NULL,":");
	MAC6=(int)strtol(token,NULL,16);

	// divide a mensagem em tokens
	token=(char *)strtok(param_host->ip_address,".");
    HOST_IP1=atoi(token);
    token=(char *)strtok(NULL,".");
	HOST_IP2=atoi(token);
    token=(char *)strtok(NULL,".");
	HOST_IP3=atoi(token);
    token=(char *)strtok(NULL,".");
	HOST_IP4=atoi(token);

    // divide a mensagem em tokens
	token=(char *)strtok(param_mac_host->host_mac_address_host,":");    
    HOST_MAC1=(int)strtol(token,NULL,16);
    token=(char *)strtok(NULL,":");
	HOST_MAC2=(int)strtol(token,NULL,16);
    token=(char *)strtok(NULL,":");
	HOST_MAC3=(int)strtol(token,NULL,16);
    token=(char *)strtok(NULL,":");
	HOST_MAC4=(int)strtol(token,NULL,16);
    token=(char *)strtok(NULL,":");
	HOST_MAC5=(int)strtol(token,NULL,16);
    token=(char *)strtok(NULL,":");
	HOST_MAC6=(int)strtol(token,NULL,16);

    // CTS
    memset(cts, 0x00, 265);
    snprintf(cts, sizeof(cts), "\n\nTX_SETUP%03d%03d%03d%03d%05d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d\n\n",IP1,IP2,IP3,IP4,port,MAC1,MAC2,MAC3,MAC4,MAC5,MAC6,HOST_IP1,HOST_IP2,HOST_IP3,HOST_IP4,HOST_MAC1,HOST_MAC2,HOST_MAC3,HOST_MAC4,HOST_MAC5,HOST_MAC6);

    //fprintf(stderr,"\n\n%s\n%d\n%d\n%d\n%d\n%02x\n%02x\n%02x\n%02x\n%02x\n%02x\n%d\n%d\n%d\n%d\n%d\n%02x\n%02x\n%02x\n%02x\n%02x\n%02x\n\n", param->label, IP1, IP2, IP3, IP4, MAC1, MAC2, MAC3, MAC4, MAC5, MAC6, port,HOST_IP1,HOST_IP2,HOST_IP3,HOST_IP4,HOST_MAC1,HOST_MAC2,HOST_MAC3,HOST_MAC4,HOST_MAC5,HOST_MAC6);

	// write to device
	if ((fd = open("/dev/medipix", O_RDWR)) == -1) {
		printf("Error! Failed to open MEDIPIX DEV!\n");
		return -1;
	}
    usleep(100);
	ioctl(fd, CTS_CR_EN, 0);
	lseek(fd, 0, SEEK_SET);
	wr_count = write(fd, cts, 265);
    usleep(100);
    close(fd);

  return 0;
}

