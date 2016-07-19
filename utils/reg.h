#ifndef REG_H_
#define REG_H_
/*HEADER FILE
--------------------------------------------------------------------------------
--!@brief REG HEADER FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! HEADER DO REG.C
--!
--! DETAILS:      
--!
--!- Project Name: reg
--!- Module Name: reg.h
--!- Tools: jedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 22/01/2014     
--!- Version: 1.0.0 (jan/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#include "interface_uc.h"
#include "global.h"

int write_omr_param_device(const omr_parameters_t *interface);
int write_dac_param_device(const dac_param_t *interface);
int write_ctpr_param_device(char *interface);
int write_send_param_device(const send_network_param_t* param, const host_network_param_t* param_host,  const inetd_t* param_mac_host);

#endif
