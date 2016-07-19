/*CGI FILE
--------------------------------------------------------------------------------
--!@brief Server TCP
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Socket server TCP paramentro da porta passada como argumento
--!
--! DETAILS:      
--!
--!- Project Name: tcpserver
--!- Module Name: server.c
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 27/02/2014     
--!- Version: 1.0.0 (fev/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERRO, entre com a porta\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0){ 
        perror("ERRO abrindo socket");
        exit(1);
        }
     fprintf(stderr,"Socket Aberto\n");
     memset((char *) &serv_addr,0, sizeof(serv_addr));//bzero
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
  
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        perror("ERRO on binding");
        exit(1);
        }
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
     if (newsockfd < 0){ 
        perror("ERRO on accept");
        exit(1);
        }
     fprintf(stderr,"Conexao aceita!\n");
     while(1){
     memset(buffer,0,256);
     n = read(newsockfd,buffer,255);
     if (n < 0){
        perror("ERRO lendo do socket");
        exit(1);
        }
     printf("Aqui esta sua mensagem: %s\n",buffer);
     n = write(newsockfd,"Mensagem Recebida com Sucesso!",18);
     if (n < 0){
        perror("ERRO escrevendo no socket");
        exit(1);
        }
     }
     close(newsockfd);
     close(sockfd);
     return 0; 
}
