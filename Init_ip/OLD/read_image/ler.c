/*C FILE
--------------------------------------------------------------------------------
--!@brief LER.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Funçoes Globais DO PROGRAMA PACKET RECEIVE
--!
--! DETAILS:      
--!
--!- Project Name: global
--!- Module Name: global.c
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
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include"ler.h"

int read_image(const char* filename, char linha[257], int n_linha)
{
  FILE *fp;
  typedef char buffer[257];
  buffer aie;
  char recebe[257];
  int line=0;
  fp = fopen(filename,"r+");
  if(fp==NULL)
  {
      fprintf(stderr,"Error on opening file %s.\n",filename);
      return -EIO;
  }
  
  while(fgets(aie,sizeof(aie),fp) != NULL)
  {  	
  	aie[strlen(aie)]='\0';
	if (line==n_linha)
	{
		strncpy(recebe,aie,sizeof(recebe));
	}
  	line++;
  }  
  fclose(fp);
  usleep(100);
  //fprintf(stderr,"%s\n",&recebe);
  strncpy(linha,recebe,sizeof(recebe));
  return 0;
}

