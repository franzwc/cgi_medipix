#ifndef _PERSIST_H_
#define _PERSIST_H_
/*HEADER FILE
--------------------------------------------------------------------------------
--!@brief PERSIST HEADER FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! HEADER DO PERSIST.C
--!
--! DETAILS:      
--!
--!- Project Name: persist
--!- Module Name: persit.h
--!- Tools: jedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 22/01/2014     
--!- Version: 1.0.0 (jan/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#include "global.h"
#include "interface_uc.h"

int write_sendfile(const char* filename,send_network_param_t* param);
int read_sendfile(const char* filename,send_network_param_t* param);
int write_dacfile(const char* filename,dac_param_t* param);
int read_dacfile(const char* filename,dac_param_t* param);
int write_omrfile(const char* filename,omr_parameters_t* param);
int read_omrfile(const char* filename,omr_parameters_t* param);
int write_hostfile(const char* filename,host_network_param_t* param);
int read_hostfile(const char* filename, host_network_param_t* param);
int read_macfile(const char* filename, inetd_t* param);
int write_macfile(const char* filename,inetd_t* param);
int read_dhcpfile(char *mac_gateway);
int read_rcfile( host_network_param_t *host_param,  inetd_t *inetd_param);
int write_rcfile(const host_network_param_t *host_param,const  inetd_t *inetd_param);
int update_rc(const host_network_param_t *host_param);

#endif
