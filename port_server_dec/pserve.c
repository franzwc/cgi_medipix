/*MAIN FILE
--------------------------------------------------------------------------------
--!@brief pserve.c
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Programa que abre uma porta UDP e aguarda chegada de pacotes e grava 
--! a imagem decodificada
--!
--! DETAILS:      
--!
--!- Project Name: pserve
--!- Module Name: pserve.c
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 08/05/2014     
--!- Version: 1.0.0 (mai/2014)
--!- Version: 2.0.0 (fev/2015)
--------------------------------------------------------------------------------
-- LNLS - DET - 2015
--------------------------------------------------------------------------------
-- ENTRADAS => numero de bits de aquisicao, numero de imagens , nome e caminho pra salvar sem a extensao
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include <math.h>
#include"global.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in si_me, si_other;
    FILE *fp;
    int sock, slen = sizeof(si_other) , recv_len;
    int i,j;
    int conta_img=1,conta_pacote=0;
	int nimagens=1,nbits=0;
	char caminho[100]="\0";
	char arquivo[200]="\0";
	char packet[3]="\0";

	char Image1 [786432];
	char Image1A [786432];
	char Image1B [786432];

	Generate6BitTable();
	Generate12BitTable();

	if (argc < 3) 
	{
         printf("Error!!! Entre com o numero de bits, numero de imagens e caminho para salvar arquivo\n");
         return -1;
    }

	nbits = atoi(argv[1]);
	nimagens = atoi(argv[2]);
	snprintf(caminho,sizeof(caminho),"%s",argv[3]);

    for(conta_img=1;conta_img<=nimagens;conta_img++)
	{
    	if ((sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    	{
			printf("Error open Socket!!!\n");
			return -1;
    	}
     
   	 	bzero(&si_me,sizeof(si_me));
    	si_me.sin_family = AF_INET;
    	si_me.sin_port = htons(PORT);
    	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    	if(bind(sock ,(struct sockaddr*)&si_me, sizeof(si_me)) == -1)
    	{
			printf("Error on bind!!!\n");
			return -1;
    	}

    	fprintf(stdout,"Waiting for Data Stream...\n");
/**************************************************************************************************
*	socket aberto a espera dos pacotes
***************************************************************************************************
*	recebe da rede pacotes de 1bit
**************************************************************************************************/
		if(nbits==0)
		{
		   	for(conta_pacote=0;conta_pacote<=11;conta_pacote++)
    		{
				bzero(buff1[conta_pacote],sizeof(buff1[conta_pacote]));
		    	if ((recv_len = recvfrom(sock, buff1[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		       	{
	   				printf("Error on recvfrom1()!!!\n");
	   				return -1;
		       	}
		    }
		    close(sock);
		}
/**************************************************************************************************
*	recebe da rede pacotes de 6bits
**************************************************************************************************/
		else if(nbits==2)
		{
		   	for(conta_pacote=0;conta_pacote<=63;conta_pacote++)
    		{
				bzero(buff6[conta_pacote],sizeof(buff6[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff6[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		       	{
	   				printf("Error on recvfrom6()!!!\n");
	   				return -1;
		       	}
		   	}
		   	close(sock);
		}
/**************************************************************************************************
*	recebe da rede pacotes de 12bits
**************************************************************************************************/
		else if(nbits==1)
		{
		   	for(conta_pacote=0;conta_pacote<=127;conta_pacote++)
    		{
				bzero(buff12[conta_pacote],sizeof(buff12[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff12[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		       	{
	   				printf("Error on recvfrom12()!!!\n");
	   				return -1;
		       	}
		   	}
		   	close(sock);
		}
/**************************************************************************************************
*	recebe da rede pacotes de 24bits
**************************************************************************************************/
		else if(nbits==3)
		{
		   	for(conta_pacote=0;conta_pacote<=255;conta_pacote++)
    		{
				//printf("packet %d\n",conta_pacote+1);
				bzero(buff24[conta_pacote],sizeof(buff24[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff24[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		       	{
	   				printf("Error on recvfrom24()!!!\n");
	   				return -1;
		       	}
		   	}
		   	close(sock);
		}
/**************************************************************************************************
*	recebe dois contadores de 12bits
**************************************************************************************************/
		else if(nbits==4)
		{
		   	for(conta_pacote=0;conta_pacote<=255;conta_pacote++)
    		{
				//printf("packet %d\n",conta_pacote+1);
				bzero(buff24[conta_pacote],sizeof(buff24[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff24[conta_pacote], 1028, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		       	{
	   				printf("Error on recvfrom12()!!!\n");
	   				return -1;
		       	}
		   	}
		   	close(sock);
		}
/**************************************************************************************************
*	socket fechado dados recebidos
**************************************************************************************************/
		printf("%d Packets\n",conta_pacote+1);
/**************************************************************************************************
*	tratamento da informacao recebida
***************************************************************************************************
*		flip na imagem 1bit
**************************************************************************************************/
		if(nbits==0)
		{
			int incremento=0;

			for(i=0;i<=63;i++)
    		{
    	  		for(j=0;j<=256;j++)
    	  		{
    	    	    if(j>0)
					{
						Image1[incremento]=(buff1[i][j] & 0x000000FF) >> 0;
		        		Image1[incremento+1]=(buff1[i][j] & 0x0000FF00) >> 8;
						Image1[incremento+2]=(buff1[i][j] & 0x00FF0000) >> 16;
						Image1[incremento+3]=(buff1[i][j] & 0xFF000000) >> 24;
						incremento=incremento+4;
					}
    			}
    		}
			// flip image
			incremento=65535;
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					Image_Flip[i][j]=Image1[incremento];
					incremento--;
				}
			}
		}
/**************************************************************************************************
*		decodificaçao 6 bits
**************************************************************************************************/
		else if(nbits==2)
		{
			int ibit;
			int incremento=0;

			for(i=0;i<=63;i++)
    		{
      			for(j=0;j<=256;j++)
      			{
        		    if(j>0)
					{
						for(ibit=0;ibit<=63;ibit++)
						{
							if((buff6[i][j] & 0x000000FF) >> 0 == LFSR6bits[ibit])
							{
								Image1[incremento]=ibit;
							}
		
							if((buff6[i][j] & 0x0000FF00) >> 8 == LFSR6bits[ibit])
							{
								Image1[incremento+1]=ibit;
							}

							if((buff6[i][j] & 0x00FF0000) >> 16 == LFSR6bits[ibit])
							{
								Image1[incremento+2]=ibit;
							}

							if((buff6[i][j] & 0xFF000000) >> 24 == LFSR6bits[ibit])
							{
								Image1[incremento+3]=ibit;
							}
						}
						/*Image1[incremento]=(buff6[i][j] & 0x000000FF) >> 0;
						Image1[incremento+1]=(buff6[i][j] & 0x0000FF00) >> 8;
						Image1[incremento+2]=(buff6[i][j] & 0x00FF0000) >> 16;
						Image1[incremento+3]=(buff6[i][j] & 0xFF000000) >> 24;*/
						incremento=incremento+4;
					}
    			}
    		}
		}
/**************************************************************************************************
*		decodificaçao 12 bits
**************************************************************************************************/
		else if(nbits==1)
		{
			int ibit;
			int incremento=0;

			for(i=0;i<=127;i++)
    		{
      			for(j=0;j<=256;j++)
      			{
        		    if(j>0)
					{
						for(ibit=0;ibit<=4095;ibit++)
						{
							if((buff12[i][j] & 0x000000FF) >> 0 == LFSR12bits[ibit])
							{
								Image1[incremento]=ibit;
							}

							if((buff12[i][j] & 0x0000FF00) >> 8 == LFSR12bits[ibit])
							{
								Image1[incremento+1]=ibit;
							}

							if((buff12[i][j] & 0x00FF0000) >> 16 == LFSR12bits[ibit])
							{
								Image1[incremento+2]=ibit;
							}

							if((buff12[i][j] & 0xFF000000) >> 24 == LFSR12bits[ibit])
							{
								Image1[incremento+3]=ibit;
							}
						}
						incremento=incremento+4;
					}
    			}
    		}
		}
/**************************************************************************************************
*		decodificaçao 24 bits
**************************************************************************************************/
		else if(nbits==3)
		{
			int ibit;
			int incremento=0;

			for(i=0;i<=127;i++)
    		{
      			for(j=0;j<=256;j++)
      			{
        		    if(j>0)
					{
						Image1A[incremento]=(buff24[i][j] & 0x000000FF) >> 0;
	    	    		Image1A[incremento+1]=(buff24[i][j] & 0x0000FF00) >> 8;
						Image1A[incremento+2]=(buff24[i][j] & 0x00FF0000) >> 16;
						Image1A[incremento+3]=(buff24[i][j] & 0xFF000000) >> 24;
						incremento=incremento+4;
					}
    			}
    		}
			incremento=0;
			for(i=129;i<=256;i++)
    		{
      			for(j=0;j<=256;j++)
      			{
        		    if(j>0)
					{
						Image1B[incremento]=(buff24[i][j] & 0x000000FF) >> 0;
	    	    		Image1B[incremento+1]=(buff24[i][j] & 0x0000FF00) >> 8;
						Image1B[incremento+2]=(buff24[i][j] & 0x00FF0000) >> 16;
						Image1B[incremento+3]=(buff24[i][j] & 0xFF000000) >> 24;
						incremento=incremento+4;
					}
    			}
    		}

		}
/**************************************************************************************************
*		decodificaçao 2x 12 bits
**************************************************************************************************/
		else if(nbits==4)
		{

			int ibit;
			int incremento=0;

			for(i=0;i<=127;i++)
    		{
      			for(j=0;j<=256;j++)
      			{
        		    if(j>0)
					{
						Image1A[incremento]=(buff24[i][j] & 0x000000FF) >> 0;
	    	    		Image1A[incremento+1]=(buff24[i][j] & 0x0000FF00) >> 8;
						Image1A[incremento+2]=(buff24[i][j] & 0x00FF0000) >> 16;
						Image1A[incremento+3]=(buff24[i][j] & 0xFF000000) >> 24;
						incremento=incremento+4;
					}
    			}
    		}
			incremento=0;
			for(i=129;i<=256;i++)
    		{
      			for(j=0;j<=256;j++)
      			{
        		    if(j>0)
					{
						Image1B[incremento]=(buff24[i][j] & 0x000000FF) >> 0;
	    	    		Image1B[incremento+1]=(buff24[i][j] & 0x0000FF00) >> 8;
						Image1B[incremento+2]=(buff24[i][j] & 0x00FF0000) >> 16;
						Image1B[incremento+3]=(buff24[i][j] & 0xFF000000) >> 24;
						incremento=incremento+4;
					}
    			}
    		}

			
		} 
/**************************************************************************************************
*		Gravacao dos dados decodificados
**************************************************************************************************/
		//altera o nome do arquivo toda vez
	    strcpy(arquivo,caminho);
		snprintf(packet,sizeof(packet),"%d",conta_img);
    	strcat(arquivo,packet);
   		strcat(arquivo,".ppm");

    	fp=fopen(arquivo,"w+");
	
    	if(fp==NULL)
    	{    
    	   	 printf("Error open file %s\n",caminho);
    	   	 return -1;
    	}
/**************************************************************************************************
*	Grava imagem 1bit
**************************************************************************************************/
		if(nbits==0)
		{
			fprintf(fp,"P1\n");
	    	fprintf(fp,"256 256\n");
    		for(i=0;i<=255;i++)
    		{
      		  for(j=0;j<=255;j++)
      		  {
					fprintf(fp,"%d ",Image_Flip[i][j]);
				
        	    	if (j==255)
					{	
						fprintf(fp,"\n");
					}
    			}
    		}
		}
/**************************************************************************************************
*	Grava imagem 6bits
**************************************************************************************************/
		else if (nbits==2)
		{
			fprintf(fp,"P2\n");
	    	fprintf(fp,"256 256\n");
	    	fprintf(fp,"63\n");

			for(i=0;i<=65535;i++)
			{
				fprintf(fp,"%02d ",Image1[i]);
			   	if ((i+1)%256==0)
				{	
					fprintf(fp,"\n");
				}
			}
			
		}
/**************************************************************************************************
*	Grava imagem 12bits
**************************************************************************************************/
		else if (nbits==1)
		{
			fprintf(fp,"P2\n");
	    	fprintf(fp,"256 256\n");
	    	fprintf(fp,"4095\n");
			for(i=0;i<=65535;i++)
			{
				fprintf(fp,"%04d ",Image1[i]);
			   	if ((i+1)%256==0)
				{	
					fprintf(fp,"\n");
				}
			}
		}
/**************************************************************************************************
*	Grava imagem 24bits
**************************************************************************************************/
		else if (nbits==3)
		{
			fprintf(fp,"P2\n");
	    	fprintf(fp,"256 256\n");
	    	fprintf(fp,"16777216\n");
			for(i=0;i<=65535;i++)
    		{
				fprintf(fp,"%08d ",Image1A[i]);
        	    if ((i+1)%256==0)
				{	
					fprintf(fp,"\n");
				}
    		}
		}
/**************************************************************************************************
*	Grava imagem 2 12bits
**************************************************************************************************/
		else if (nbits==4)
		{
			fprintf(fp,"P2\n");
	    	fprintf(fp,"256 256\n");
	    	fprintf(fp,"4095\n");
			for(i=0;i<=65535;i++)
    		{
				fprintf(fp,"%04d ",Image1A[i]);
        	    if ((i+1)%256==0)
				{	
					fprintf(fp,"\n");
				}
    		}
			fclose(fp);
    		strcpy(arquivo,caminho);
			snprintf(packet,sizeof(packet),"%d",conta_img);
    		strcat(arquivo,packet);
   			strcat(arquivo,"th1.ppm");

    		fp=fopen(arquivo,"w+");
			fprintf(fp,"P2\n");
	    	fprintf(fp,"256 256\n");
	    	fprintf(fp,"4095\n");
			for(i=0;i<=65535;i++)
    		{
				fprintf(fp,"%04d ",Image1B[i]);
        	    if ((i+1)%256==0)
				{	
					fprintf(fp,"\n");
				}
    		}
		}
    	fclose(fp);
	}
	printf("Enjoy!!!\n");
/**************************************************************************************************
*	executado com sucesso .....enjoy babe
**************************************************************************************************/
    return 0;
}


