#ifndef NET_UTILS_H_
#define NET_UTILS_H
/*HEADER FILE
--------------------------------------------------------------------------------
--!@brief NET UTILS HEADER FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! HEADER DO NET UTILS 
--!
--! DETAILS:      
--!
--!- Project Name: net_utils
--!- Module Name: net_utils.c
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
/*
 * Retorna se IP é valido 1 para valido 0 para nao valido
 */ 
int isValidIpAddress(const char *ipAddress);
int isValidMacAddress(const char* mac);
int split_ip_address(const char* ipAddress,int *array);
int setIPv4(const char *interface , const char *ipAddress,const char *mask);
int setIPAddress(char *interface);

#endif
