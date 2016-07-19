#include <stdio.h>
#include "net_utils.h"
typedef struct {
	int array[4];


} t;

int main(int argc,char **argv){
	int p;
	t a1;
	int array[4];
	int i=0;
	p = isValidIpAddress(argv[1]);
	printf(" Valid ? %d \n",p);
	parseIpAddress(argv[1],&a1.array);
	for(i=0;i<4;i++)
		printf("%d\n",a1.array[i]);
	return 0;

}
