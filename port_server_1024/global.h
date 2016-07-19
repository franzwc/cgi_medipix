/*Header FILE
--------------------------------------------------------------------------------
--!@brief GLOBAL.H
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! CABEÇALHO GLOBAL DO PROGRAMA PACKET RECEIVE
--!
--! DETAILS:      
--!
--!- Project Name: global
--!- Module Name: global.h
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 08/05/2014     
--!- Version: 1.0.0 (mai/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define BUFLEN  257							//Max length of buffer
#define NPACK1  65							//Number of packets for 1x1bit
#define NPACK6  385							//Number of packets for 1x6bit
#define NPACK12 769							//Number of packets for 1x12bit
#define NPACK24 1537     					//Number of packets for 1x24bit
#define PORT    3000  						//The port on which to listen for incoming data

typedef int mem_aloc[BUFLEN];

#endif
