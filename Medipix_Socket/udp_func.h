/*HEADER FILE
--------------------------------------------------------------------------------
--!@brief udp_func.h
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Funcoes importantes
--!
--! DETAILS:      
--!
--!- Project Name: udp_func
--!- Module Name: udp_func.h
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 07/10/2014     
--!- Version: 1.0.0 (out/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
*/
#ifndef _UDP_FUNC_H
#define _UDP_FUNC_H

#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/interface_uc.h"
#include "../utils/reg.h"
#include "../utils/net_utils.h"

// estado de gravaçao dos paramentros
typedef enum { write_omr, 
               write_dac,
			   write_send,
			   write_host,
			   read_omr,
			   read_dac,
			   read_network,
			   write_ctpr,
               none
             } STATUS;

int send_msg_udp(int port, int ip, char msg[150]);
void return_omr_udp(omr_parameters_t param, char buffer[150]);
void return_dac_udp(dac_param_t param, char buffer[150]);
void return_network_udp(send_network_param_t param, host_network_param_t host_param, char buffer[150]);
int validate_omr_param(omr_parameters_t param);
int validate_dac_param(dac_param_t param);
int validate_send_param (send_network_param_t send_param ,host_network_param_t host_param, inetd_t inetd_param);
int validate_host_param (host_network_param_t param);

#endif
