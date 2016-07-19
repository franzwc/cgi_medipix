/*CGI FILE
--------------------------------------------------------------------------------
--!@brief TCP Client
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! Socket Client TCP paramentro de IP e porta passada como argumento
--!
--! DETAILS:      
--!
--!- Project Name: tcpclient
--!- Module Name: client.c
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
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("ERRO abrindo socket\n");
        exit(0);
        }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERRO, host nao encontrado\n");
        exit(0);
        }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        perror("ERRO na conexao\n");
        exit(0);
        }
    printf("Conexao Estabelecida\n");
    printf("Digite sua mensagem! : ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0){ 
         perror("ERRO escrevendo no socket\n");
         exit(0);
         }
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) {
         perror("ERRO lendo do socket\n");
         exit(0);
         }
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}
