/*MAIN FILE
--------------------------------------------------------------------------------
--!@brief Listen_UDP_port.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Programa que abre uma porta UDP e aguarda chegada de pacotes e grava em 
--! arquivo texto
--!
--! DETAILS:      
--!
--!- Project Name: Listen_UDP_port
--!- Module Name: Listen_UDP_port.c
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 08/05/2014     
--!- Version: 1.0.0 (mai/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER "224.0.0.1"
#define BUFLEN 1024
#define PORT 8888

#define BASE 2
#define DIGITS 8

void ascii_to_bin(char input, char output[DIGITS]);

typedef unsigned char tdados[BUFLEN];


int main(void)
{
	char ascii;
	char out[DIGITS];
	strcpy(&ascii,"15");
	ascii_to_bin(ascii,out);
	fprintf(stderr,"binario %s\n",out);

    return 0;
}

void ascii_to_bin(char input, char output[DIGITS])
{
   int i, remainder;

   char digitsArray[2] = "01";

   for (i=DIGITS;i>0;i--)
   {
      remainder = input%BASE;
      input = input/BASE;
      output[i-1] = digitsArray[remainder];
   }
   output[DIGITS] = '\0'; 
}
