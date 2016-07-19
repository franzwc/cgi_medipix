
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define _XOPEN_SOURCE 500
#define SERVER "10.0.27.67"
#define BUFLEN 1024
#define PORT 4000


int main(int argc, char *argv[])
{
    char mensg[20];
    struct sockaddr_in Tx_cli;
    int sock, slen=sizeof(Tx_cli),recv_len;
	char buffer[150];

	if (argc < 3)
	{
     	 fprintf(stderr,"Erro, entre com o comando\n");
         return -1;
    }
    strcpy(mensg,argv[1]);
	strcat(mensg," ");
	strcat(mensg,argv[2]);
   	fprintf(stderr,"mensagem %s\n",mensg);
	//envia pela ethernet
    if ( (sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        return -1;
    }
 
    memset((char *) &Tx_cli, 0, sizeof(Tx_cli));
    Tx_cli.sin_family = AF_INET;
    Tx_cli.sin_port = htons(PORT); 
    inet_aton(SERVER , &Tx_cli.sin_addr);
   	//send the message
   	if (sendto(sock, mensg, sizeof(mensg), 0 , (struct sockaddr *) &Tx_cli, slen)==-1)
   	{
       	return -1;
   	}
	usleep(1);   
	if ((recv_len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &Tx_cli, &slen)) == -1)
   		{
			fprintf(stderr,"Error on recvfrom1()!!!\n");
			return -1;
   		}
		fprintf(stderr,"MSG %s\n",buffer);
		fprintf(stderr,"port %d\n", Tx_cli.sin_port);
		fprintf(stderr,"ip %x\n",Tx_cli.sin_addr.s_addr);

  
    close(sock);
    return 0;
}

