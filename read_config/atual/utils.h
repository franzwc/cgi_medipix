/*HEADER FILE
--------------------------------------------------------------------------------
--!@brief utils.h
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Funcoes importantes
--!
--! DETAILS:      
--!
--!- Project Name: utils
--!- Module Name: utils.h
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 08/05/2014     
--!- Version: 1.0.0 (mai/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
*/
#ifndef _UTILS_H
#define _UTILS_H

char *byte_to_binary(int x);
char* StrReverse(char* str);
char* StrCastReverse(char* str);
int read_file(const char* filename,char matrix[327680], int str_lenght);
void cast_mask_test_bit(char matrix[327680], char mt_bits[65536]);
void cast_threshold_bit(char matrix[327680], char threshold[196865]);
void write_out_stream(char matrix[327680], char mask_bits[65536], char test_bits[65536], char all_bits[786433]);
int write_eq_arquivo(const char* filename, char stream_out[786433]);
void ascii_to_bin(char threshold[196865], char matrix[327680]);

#endif
