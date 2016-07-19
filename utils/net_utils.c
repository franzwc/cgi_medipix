/*C FILE
--------------------------------------------------------------------------------
--!@brief NET UTILS C FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! FUNCOES DE MANIPULACAO DE ENDEREÇOS IP
--!
--! DETAILS:      
--!
--!- Project Name: net_utils
--!- Module Name: net_utils.c
--!- Tools: jedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 22/01/2014     
--!- Version: 1.0.0 (jan/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*Local include */
#include "net_utils.h"


static int Skfd = 0;

int parseIpAddress(const char *ipAddress, int *ipArray)
{
	char separator[]=".";
	char *token;
	char ip[17];
	int i=0;
	strncpy(ip,ipAddress,16);
	token = strtok(ip,separator);
	while(token){
		ipArray[i] = atoi(token);
		//printf("token %s",token);
		token = strtok(NULL,separator);
		i++;
	}
	return 0;
}

int split_ip_address(const char* ipAddress, int* array){
  char *token;
  char ip[18];
  char separator[2]=".";
  int i;
  strncpy(ip,ipAddress,18);
  token = strtok(ip,separator);
  while(token){
    if(i==4) break;
    array[i]=atoi(token);
    token=strtok(NULL,separator);
    i++;
  }
  return 0;
  
}

int setIPV4(host_network_param_t *param)
{
	int fd;
	struct ifreq ifr;
	char name[]="eth0";
	struct sockaddr_in* addr = (struct sockaddr_in*)&ifr.ifr_addr;
	// create socket
	fprintf(stderr,"Try configure ip  %s netmask %s\n",param->ip_address,param->mask);
	fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

	strncpy(ifr.ifr_name, name, IFNAMSIZ);

	ifr.ifr_addr.sa_family = AF_INET;
	inet_pton(AF_INET, param->ip_address, &addr->sin_addr);
	ioctl(fd, SIOCSIFADDR, &ifr);

	inet_pton(AF_INET, param->mask, &addr->sin_addr);
	ioctl(fd, SIOCSIFNETMASK, &ifr);

	ioctl(fd, SIOCGIFFLAGS, &ifr);
	strncpy(ifr.ifr_name, name, IFNAMSIZ);
	ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);

	ioctl(fd, SIOCSIFFLAGS, &ifr);

}

int setIPAddress( char *interface)
{
	host_network_param_t		hparam = { "192.168.100.59","255.255.255.0","192.168.100.1"};
	host_network_param_t *param;
	param = &hparam;
	struct ifreq ifr;
	struct in_addr addr;
	struct in_addr mask;
	struct in_addr broadcast;
	if(inet_aton(param->ip_address, &addr) ==0){
		fprintf(stderr,"Inet_aton() failed. ip: %s \n",param->ip_address);
		return -1;
	}
	if(inet_aton(param->mask,&mask)==0){
		fprintf(stderr,"Inet_aton() failed. mask: %s \n",param->ip_address);
		return -1;
	}
	/*Derrubando interface */
	strncpy(ifr.ifr_name,interface,sizeof (ifr.ifr_name));
	ifr.ifr_flags &= ~IFF_UP;
	if(ioctl(Skfd,SIOCSIFFLAGS,&ifr) <0){
		fprintf(stderr,"ioctl() failed, %s\n",strerror(errno));
		return -1;
	}
	/* Compute broadcast address from ip address and netmask */
	*(uint32_t *) (&broadcast) = *(uint32_t *) (&addr) | ~*(uint32_t *) (&mask);
	/*Escrevendo IP*/
	if(writeAddress(interface,SIOCSIFADDR,&addr)<0){
		return -1;
	}
	/* Escrevendo netmask */
	if(writeAddress(mask,SIOCSIFNETMASK,&addr)<0){
		return -1;
	}
	/* Escrevendo broadcast */
	if(writeAddress(mask,SIOCSIFNETMASK,&broadcast)<0){
		return -1;
	}

	strncpy(ifr.ifr_name, interface, sizeof ifr.ifr_name);
	ifr.ifr_flags |= IFF_UP | IFF_RUNNING;
	if (ioctl(Skfd, SIOCSIFFLAGS, &ifr) < 0) {
		fprintf(stderr, "ioctl() failed, %s", strerror(errno));
		return -1;
	}

}

int isValidIpAddress(const char *ipAddress)
{
	struct sockaddr_in sa;
	int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
	//printf("%d result\n",result);
	return result ;
}

int isValidMacAddress(const char* mac) 
{
	int i = 0;
    int s = 0;

    while (*mac) 
	{
    	if (isxdigit(*mac)) 
		{
        	i++;
        }
        else if (*mac == ':' || *mac == '-') 
		{
        	if (i == 0 || i / 2 - 1 != s)
            break;
            ++s;
        }
        else 
	    {
            s = -1;
        }
        ++mac;
     }
    return (i == 12 && (s == 5 || s == 0));
}

int setIPv4(const char *interface , const char *ipAddress,const char *mask)
{
	struct ifreq ifr;
	struct sockaddr_in* addr = (struct sockaddr_in*)&ifr.ifr_addr;
	int fd=-1;
	fd = socket(PF_INET,SOCK_DGRAM,IPPROTO_IP);
	strncpy(ifr.ifr_name,interface,IFNAMSIZ);

	ifr.ifr_addr.sa_family = AF_INET;
	inet_pton(AF_INET, ipAddress, &addr->sin_addr);
	ioctl(fd, SIOCSIFADDR, &ifr);

	inet_pton(AF_INET, mask, &addr->sin_addr);
	ioctl(fd, SIOCSIFNETMASK, &ifr);

	ioctl(fd, SIOCGIFFLAGS, &ifr);
	strncpy(ifr.ifr_name, ipAddress, IFNAMSIZ);
	ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);

	ioctl(fd, SIOCSIFFLAGS, &ifr);

}

int writeAddress(char *ifname, int flag, struct in_addr *addr)
{

	struct sockaddr_in sin;
	struct ifreq ifr;

	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	memcpy(&sin.sin_addr, addr, sizeof(struct in_addr));

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
	memcpy((char *) &ifr.ifr_addr, (char *) &sin, sizeof(struct sockaddr_in));

	if (ioctl(Skfd, flag, &ifr) < 0) {
		fprintf(stderr, "ioctl() failed, %s", strerror(errno));
		return -1;
	}
	return 0;
}

