
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>


int main(int argc, char *argv[])
{
    struct sockaddr_in si_me, si_other;
    FILE *fp;
    int sock, slen = sizeof(si_other) , recv_len;
    int port;
    int conta_img=1,conta_pacote=0;
    char buffer[150];

	if (argc < 2) 
	{
         fprintf(stderr,"Error!!! Entre com o porta\n");
         return -1;
    }

	port = atoi(argv[1]);
	
   	if ((sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
   	{
		fprintf(stderr,"Error open Socket!!!\n");
		return -1;
   	}
    
	bzero(&si_me,sizeof(si_me));
   	si_me.sin_family = AF_INET;
   	si_me.sin_port = htons(port);
   	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
   	if(bind(sock ,(struct sockaddr*)&si_me, sizeof(si_me)) == -1)
   	{
		fprintf(stderr,"Error on bind!!!\n");
		return -1;
   	}
   	printf("Waiting for data...\n");
	
	while(1)
	{
		bzero(buffer,sizeof(buffer));
		if ((recv_len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &si_other, &slen)) == -1)
   		{
			fprintf(stderr,"Error on recvfrom1()!!!\n");
			return -1;
   		}
		fprintf(stderr,"MSG %s\n",buffer);
		fprintf(stderr,"port %d\n", si_other.sin_port);
		fprintf(stderr,"ip %x\n",si_other.sin_addr.s_addr);

		//sendto(sock, buffer, sizeof(buffer), 0 , (struct sockaddr *) &si_other, slen);
	}
	printf("enjoy!\n\n");
    return 0;
}

