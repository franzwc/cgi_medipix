#include <stdio.h>
//#include <persist.h>
#include "global.h"
#include "persist.h"
//#include "net_utils.h"


int main(){
	printf("Teste persist.c\n");
	host_network_param_t		host_param = { "192.168.100.79","255.255.255.0","192.168.100.1"};
	
	rx_param_t			rx_param = { "1","224.0.1.1","5004","1"};
	inetd_t				inetd_param = {"TSxpress","00:00:00:00:00:00:00"};
	
	printf("***** Host network parameters *****\n");		
	write_hostfile("host_param.txt",&host_param);
	read_hostfile("host_param.txt",&host_param);
	print_host_param(&host_param);
	printf("***** TX parameters *****\n");	
	write_txfile("tx_param.txt",&tx_param);
	read_txfile("tx_param.txt",&tx_param);
	print_tx_param(&tx_param);	
	printf("***** RX parameters *****\n");	
	write_rxfile("rx_param.txt",&rx_param);
	read_rxfile("rx_param.txt",&rx_param);
	print_rx_param(&rx_param);
	//if(setIPAddress("eth0")<0){
	//	printf("Failed\n");
	//}
	

}


void print_host_param(host_network_param_t *param){
	  printf("%s\n",param->ip_address);
	  printf("%s\n",param->mask);
	  printf("%s\n",param->gateway);
}

void print_tx_param(tx_param_t *param){
	  printf("%s\d",param->enable);
 	  printf("%s\n",param->ip_address);
 	  printf("%s\n",param->port);
 	  printf("%s\n",param->protocol);
 	  printf("%s\n",param->num_packets);
 	  printf("%s\n",param->fec_en);
 	  printf("%s\n",param->fec_row);
 	  printf("%s\n",param->fec_col);
	
}
void print_rx_param(rx_param_t *param){
  	printf("%s\n",param->enable);
  	printf("%s\n",param->ip_address);
  	printf("%s\n",param->port);
  	printf("%s\n",param->protocol);    
}
	
	
