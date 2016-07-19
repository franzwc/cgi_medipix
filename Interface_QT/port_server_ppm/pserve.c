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
#include <errno.h>
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
	int reuse;

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
     	
		if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
		{
 			printf("Reuse port Error : %s\n", strerror(errno));
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
		   	for(conta_pacote=0;conta_pacote<=63;conta_pacote++)
    		{
				bzero(buff1[conta_pacote],sizeof(buff1[conta_pacote]));
		    	if ((recv_len = recvfrom(sock, buff1[conta_pacote], 1032, 0, (struct sockaddr *) &si_other, &slen)) == -1)
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
		   	for(conta_pacote=0;conta_pacote<=383;conta_pacote++)
    		{
				bzero(buff6[conta_pacote],sizeof(buff6[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff6[conta_pacote], 1032, 0, (struct sockaddr *) &si_other, &slen)) == -1)
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
		   	for(conta_pacote=0;conta_pacote<=767;conta_pacote++)
    		{
				//printf("packet %d\n",conta_pacote+1);
				bzero(buff12[conta_pacote],sizeof(buff12[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff12[conta_pacote], 1032, 0, (struct sockaddr *) &si_other, &slen)) == -1)
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
		   	for(conta_pacote=0;conta_pacote<=1535;conta_pacote++)
    		{
				//printf("packet %d\n",conta_pacote+1);
				bzero(buff24[conta_pacote],sizeof(buff24[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff24[conta_pacote], 1032, 0, (struct sockaddr *) &si_other, &slen)) == -1)
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
		   	for(conta_pacote=0;conta_pacote<=1536;conta_pacote++)
    		{
				//printf("packet %d\n",conta_pacote+1);
				bzero(buff24[conta_pacote],sizeof(buff24[conta_pacote]));
		       	if ((recv_len = recvfrom(sock, buff24[conta_pacote], 1032, 0, (struct sockaddr *) &si_other, &slen)) == -1)
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

		printf("%d Packets\n",conta_pacote);
/**************************************************************************************************
*	tratamento da informacao recebida
***************************************************************************************************
*		flip na imagem 1bit
**************************************************************************************************/
		if(nbits==0)
		{
			char Image1 [65536];
			int incremento=0;

			for(i=0;i<=63;i++)
    		{
    	  		for(j=0;j<=257;j++)
    	  		{
    	    	    if(j>1)
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
			Generate6BitTable();
			int Image[256][256];
			int Image_Decod [256][256];
			char Image1 [393216];
			int Image2 [256][1536];
			int ibit;
			int incremento=0;

			for(i=0;i<=383;i++)
    		{
      			for(j=0;j<=257;j++)
      			{
        		    if(j>1)
					{
						Image1[incremento]=(buff6[i][j] & 0x000000FF) >> 0;
	    	    		Image1[incremento+1]=(buff6[i][j] & 0x0000FF00) >> 8;
						Image1[incremento+2]=(buff6[i][j] & 0x00FF0000) >> 16;
						Image1[incremento+3]=(buff6[i][j] & 0xFF000000) >> 24;
						//sprintf(teste,"%x%x%x%x",(buff6[i][j] & 0x000000FF)>>0,(buff6[i][j] & 0x0000FF00)>>8,(buff6[i][j] & 0x00FF0000)>>16,(buff6[i][j] & 0xFF000000)>>24);
						incremento=incremento+4;
					}
    			}
    		}

			for(i=0;i<=255;i++)
			{
				for(j=0;j<=1535;j++)
				{
					Image2[i][j]=Image1[i+(256*j)];//pulo do gato
				}
			}

			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{	
					Image[j][i] = ((Image2[i][j*6])*32)+((Image2[i][(j*6)+1])*16)+((Image2[i][(j*6)+2])*8)+((Image2[i][(j*6)+3])*4)+((Image2[i][(j*6)+4])*2)+(Image2[i][(j*6)+5]);
				}
			}

			//decod
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					for(ibit=0;ibit<=63;ibit++)
					{
						if(Image[i][j]==LFSR6bits[ibit])
						{
							Image_Decod[i][j]=ibit;
						}
					}
				}
			}
			// flip image
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					Image_Flip[i][j]=Image_Decod[255-i][255-j];
				}
			}
		}
/**************************************************************************************************
*		decodificaçao 12 bits
**************************************************************************************************/
		else if(nbits==1)
		{
			Generate12BitTable();
			int Image[256][256];
			int Image_Decod [256][256];
			char Image1 [786432];
			int Image2 [256][3072];
			int ibit;
			int incremento=0;

			for(i=0;i<=767;i++)
    		{
      			for(j=0;j<=257;j++)
      			{
					/*if (j==0)
					{
						printf("%x ", (buff12[i][j] & 0x000000FF) >> 0);
						printf("%x ", (buff12[i][j] & 0x0000FF00) >> 8);
						printf("%d ", (buff12[i][j] & 0x00FF0000) >> 16);
						printf("%d\n", (buff12[i][j] & 0xFF000000) >> 24);
					}*/
        		    if(j>1)
					{
						Image1[incremento]=(buff12[i][j] & 0x000000FF) >> 0;
	    	    		Image1[incremento+1]=(buff12[i][j] & 0x0000FF00) >> 8;
						Image1[incremento+2]=(buff12[i][j] & 0x00FF0000) >> 16;
						Image1[incremento+3]=(buff12[i][j] & 0xFF000000) >> 24;
						//sprintf(teste,"%x%x%x%x",(buff6[i][j] & 0x000000FF)>>0,(buff6[i][j] & 0x0000FF00)>>8,(buff6[i][j] & 0x00FF0000)>>16,(buff6[i][j] & 0xFF000000)>>24);
						incremento=incremento+4;
					}
    			}
    		}
			
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=3071;j++)
				{
					Image2[i][j]=Image1[i+(256*j)];//pulo do gato
				}
			}

			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{	
					Image[j][i] = ((Image2[i][j*12])*2048)+((Image2[i][(j*12)+1])*1024)+((Image2[i][(j*12)+2])*512)+((Image2[i][(j*12)+3])*256)+((Image2[i][(j*12)+4])*128)+((Image2[i][(j*12)+5])*64)+((Image2[i][(j*12)+6])*32)+((Image2[i][(j*12)+7])*16)+((Image2[i][(j*12)+8])*8)+((Image2[i][(j*12)+9])*4)+((Image2[i][(j*12)+10])*2)+(Image2[i][(j*12)+11]);
				}
			}

			//decod
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					for(ibit=0;ibit<=4095;ibit++)
					{
						if(Image[i][j]==LFSR12bits[ibit])
						{
							Image_Decod[i][j]=ibit;
							//printf("%d ", Image_Decod[i][j]);
						}
					}
				}
			}
			// flip image
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					Image_Flip[i][j]=Image_Decod[255-i][255-j];
				}
			}
		}
/**************************************************************************************************
*		decodificaçao 24 bits
**************************************************************************************************/
		else if(nbits==3)
		{
			Generate12BitTable();
			int ImageA[256][256];

			int Image_DecodA [256][256];
			int Image_DecodB [256][256];

			char Image1A [786432];
			char Image1B [786432];

			int Image2A [256][3072];

			int ibit;
			int incremento=0;

			for(i=0;i<=767;i++)
    		{
      			for(j=0;j<=257;j++)
      			{
        		    if(j>1)
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
			for(i=768;i<=1535;i++)//for(i=769;i<=1536;i++)
    		{
      			for(j=0;j<=257;j++)
      			{
        		    if(j>1)
					{
						Image1B[incremento]=(buff24[i][j] & 0x000000FF) >> 0;
	    	    		Image1B[incremento+1]=(buff24[i][j] & 0x0000FF00) >> 8;
						Image1B[incremento+2]=(buff24[i][j] & 0x00FF0000) >> 16;
						Image1B[incremento+3]=(buff24[i][j] & 0xFF000000) >> 24;
						incremento=incremento+4;
					}
    			}
    		}

			for(i=0;i<=255;i++)
			{
				for(j=0;j<=3071;j++)
				{
					Image2A[i][j]=Image1A[i+(256*j)];//pulo do gato
				}
			}

			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{	
					ImageA[j][i] = ((Image2A[i][j*12])*2048)+((Image2A[i][(j*12)+1])*1024)+((Image2A[i][(j*12)+2])*512)+((Image2A[i][(j*12)+3])*256)+((Image2A[i][(j*12)+4])*128)+((Image2A[i][(j*12)+5])*64)+((Image2A[i][(j*12)+6])*32)+((Image2A[i][(j*12)+7])*16)+((Image2A[i][(j*12)+8])*8)+((Image2A[i][(j*12)+9])*4)+((Image2A[i][(j*12)+10])*2)+(Image2A[i][(j*12)+11]);
				}
			}

			//decod
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					for(ibit=0;ibit<=4095;ibit++)
					{
						if(ImageA[i][j]==LFSR12bits[ibit])
						{
							Image_DecodA[i][j]=ibit;
						}
					}
				}
			}

			for(i=0;i<=255;i++)
			{
				for(j=0;j<=3071;j++)
				{
					Image2A[i][j]=Image1B[i+(256*j)];
				}
			}
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{	
					ImageA[j][i] = ((Image2A[i][j*12])*2048)+((Image2A[i][(j*12)+1])*1024)+((Image2A[i][(j*12)+2])*512)+((Image2A[i][(j*12)+3])*256)+((Image2A[i][(j*12)+4])*128)+((Image2A[i][(j*12)+5])*64)+((Image2A[i][(j*12)+6])*32)+((Image2A[i][(j*12)+7])*16)+((Image2A[i][(j*12)+8])*8)+((Image2A[i][(j*12)+9])*4)+((Image2A[i][(j*12)+10])*2)+(Image2A[i][(j*12)+11]);
				}
			}
			//decod
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					for(ibit=0;ibit<=4095;ibit++)
					{
						if(ImageA[i][j]==LFSR12bits[ibit])
						{
							Image_DecodB[i][j]=ibit;
						}
					}
				}
			}

			// flip image
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					Image_Flip[i][j]=(Image_DecodA[255-i][255-j]&0x000FFF)+(Image_DecodB[255-i][255-j]<<12);
				}
			}
		}
/**************************************************************************************************
*		decodificaçao 2x 12 bits
**************************************************************************************************/
		else if(nbits==4)
		{
			Generate12BitTable();
			int ImageA[256][256];

			int Image_DecodA [256][256];
			int Image_DecodB [256][256];

			char Image1A [786432];
			char Image1B [786432];

			int Image2A [256][3072];

			int ibit;
			int incremento=0;

			for(i=0;i<=767;i++)
    		{
      			for(j=0;j<=257;j++)
      			{
        		    if(j>1)
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
			for(i=769;i<=1536;i++)
    		{
      			for(j=0;j<=257;j++)
      			{
        		    if(j>1)
					{
						Image1B[incremento]=(buff24[i][j] & 0x000000FF) >> 0;
	    	    		Image1B[incremento+1]=(buff24[i][j] & 0x0000FF00) >> 8;
						Image1B[incremento+2]=(buff24[i][j] & 0x00FF0000) >> 16;
						Image1B[incremento+3]=(buff24[i][j] & 0xFF000000) >> 24;
						incremento=incremento+4;
					}
    			}
    		}

			for(i=0;i<=255;i++)
			{
				for(j=0;j<=3071;j++)
				{
					Image2A[i][j]=Image1A[i+(256*j)];//pulo do gato
				}
			}

			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{	
					ImageA[j][i] = ((Image2A[i][j*12])*2048)+((Image2A[i][(j*12)+1])*1024)+((Image2A[i][(j*12)+2])*512)+((Image2A[i][(j*12)+3])*256)+((Image2A[i][(j*12)+4])*128)+((Image2A[i][(j*12)+5])*64)+((Image2A[i][(j*12)+6])*32)+((Image2A[i][(j*12)+7])*16)+((Image2A[i][(j*12)+8])*8)+((Image2A[i][(j*12)+9])*4)+((Image2A[i][(j*12)+10])*2)+(Image2A[i][(j*12)+11]);
				}
			}

			//decod
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					for(ibit=0;ibit<=4095;ibit++)
					{
						if(ImageA[i][j]==LFSR12bits[ibit])
						{
							Image_DecodA[i][j]=ibit;
						}
					}
				}
			}

			for(i=0;i<=255;i++)
			{
				for(j=0;j<=3071;j++)
				{
					Image2A[i][j]=Image1B[i+(256*j)];
				}
			}
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{	
					ImageA[j][i] = ((Image2A[i][j*12])*2048)+((Image2A[i][(j*12)+1])*1024)+((Image2A[i][(j*12)+2])*512)+((Image2A[i][(j*12)+3])*256)+((Image2A[i][(j*12)+4])*128)+((Image2A[i][(j*12)+5])*64)+((Image2A[i][(j*12)+6])*32)+((Image2A[i][(j*12)+7])*16)+((Image2A[i][(j*12)+8])*8)+((Image2A[i][(j*12)+9])*4)+((Image2A[i][(j*12)+10])*2)+(Image2A[i][(j*12)+11]);
				}
			}
			//decod
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					for(ibit=0;ibit<=4095;ibit++)
					{
						if(ImageA[i][j]==LFSR12bits[ibit])
						{
							Image_DecodB[i][j]=ibit;
						}
					}
				}
			}

			// flip image
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					Image_Flip[i][j]=(Image_DecodA[255-i][255-j]);
                    Image_Flip2[i][j]=(Image_DecodB[255-i][255-j]);
				}
			}
		} 
/**************************************************************************************************
*		Gravacao dos dados decodificados
**************************************************************************************************/
		//altera o nome do arquivo toda vez
		if(nbits==0)
		{
	    	strcpy(arquivo,caminho);
			snprintf(packet,sizeof(packet),"%d",conta_img);
    		strcat(arquivo,packet);
   			strcat(arquivo,".ppm");
		}
		else if(nbits==2)
		{
	    	strcpy(arquivo,caminho);
			snprintf(packet,sizeof(packet),"%d",conta_img);
    		strcat(arquivo,packet);
   			strcat(arquivo,".ppm");
		}
		else if(nbits==4)
		{
	    	strcpy(arquivo,caminho);
			snprintf(packet,sizeof(packet),"%d",conta_img);
    		strcat(arquivo,packet);
   			strcat(arquivo,".ppm");
		}
		else
		{
	    	strcpy(arquivo,caminho);
			snprintf(packet,sizeof(packet),"%d",conta_img);
    		strcat(arquivo,packet);
   			strcat(arquivo,".ppm");
		}
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
					fprintf(fp,"%x ",Image_Flip[i][j]);
				
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

			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					fprintf(fp,"%02d ",Image_Flip[i][j]);
					if (j==255)
					{	
						fprintf(fp,"\n");
					}
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
			for(i=0;i<=255;i++)
			{
				for(j=0;j<=255;j++)
				{
					fprintf(fp,"%04d ",Image_Flip[i][j]);
					if (j==255)
					{	
						fprintf(fp,"\n");
					}
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
			for(i=0;i<=255;i++)
    		{
      		  for(j=0;j<=255;j++)
      		  {
					fprintf(fp,"%08d ",Image_Flip[i][j]);
        	    	if (j==255)
					{	
						fprintf(fp,"\n");
					}
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
			for(i=0;i<=255;i++)
    		{
      		  for(j=0;j<=255;j++)
      		  {
					fprintf(fp,"%04d ",Image_Flip[i][j]);
        	    	if (j==255)
					{	
						fprintf(fp,"\n");
					}
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
			for(i=0;i<=255;i++)
    		{
      		  for(j=0;j<=255;j++)
      		  {
					fprintf(fp,"%04d ",Image_Flip2[i][j]);
        	    	if (j==255)
					{	
						fprintf(fp,"\n");
					}
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


