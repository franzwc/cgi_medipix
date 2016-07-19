/*MAIN FILE
--------------------------------------------------------------------------------
--!@brief Listen_UDP_port.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Programa que abre uma porta UDP e escuta aguar
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
Header*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char tdados[3073];

int main(void) {	
		
	FILE *fp;
	tdados eq[255];
	int tamanho;
	int line=0;

	fp = fopen("equalize.dat","r");
	if(fp==NULL)
  	{
    	fprintf(stderr,"Error on opening file.\n");
      	return -1;
  	}
	while(!feof(fp))
	{
		memset(eq[line],'\0',sizeof(tdados));
		tamanho=fread(eq[line],sizeof(unsigned char),sizeof(tdados),fp);
		//fprintf(stderr,"\neq%d %s\n",line,eq[line]);
		line++;
	}
  	fclose(fp);

	fprintf(stderr,"\neq%d %s\n",0,eq[0]);

	//fprintf(stderr,"\nbuffer%s\n",buffer);

	//fprintf(stderr,"\neq line[%d] %s\n",0,eq[0]);

	/*fp = fopen("/dev/ttyS0","w+");
 	if(fp==NULL)
     {
 	    fprintf(stderr,"Error opening serial.\n");
 	    return -1;
 	 }

	fprintf(fp,"%s",eq[0]);

	fclose(fp);*/

	return 0;
}


