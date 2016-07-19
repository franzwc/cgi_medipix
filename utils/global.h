#ifndef _GLOBAL_H_
#define _GLOBAL_H_
/*HEADER FILE
--------------------------------------------------------------------------------
--!@brief GLOBAL HEADER FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! HEADER COM AS STRUCTS DE IP E MAC DO HOST
--!
--! DETAILS:      
--!
--!- Project Name: global
--!- Module Name: global.c
--!- Tools: jedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 22/01/2014     
--!- Version: 1.0.0 (jan/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#define TRUE   0
#define FALSE -1

#define 	LEN	16

#define MAC_FILE	"/home/mac_config.dat"
#define HOST_FILE	"/home/host_config.dat"
#define OMR_FILE 	"/home/omr_config.dat"
#define DAC_FILE    "/home/dac_config.dat"
#define SEND_FILE   "/home/send_config.dat"
#define EPICS_FILE  "/home/epics_config.dat"
#define RC_FILE		"/etc/rc"

typedef struct equalization
{
  char pixel [128] [3072];
}equalization_t;

typedef struct host_network_param
{
  char ip_address[LEN];
  char mask[LEN];
  char gateway[LEN];
}host_network_param_t;

typedef struct send_network_param
{
  char label[LEN];
  char ip_send[LEN];
  char port_send[LEN];
  char mac_send[21];
}send_network_param_t;

typedef struct inetd
{
  char host_mac_address_host[21];
  char host_mac_address_stream[21];  
} inetd_t;

#endif
