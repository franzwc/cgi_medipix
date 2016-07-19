/*#include<stdio.h>
#include<stdlib.h>

int main()
{

	int i;
	char str[100];

	printf("checking \n");
	if (system(NULL)) puts("ok");
	else exit(EXIT_FAILURE);
	printf("dir\n");
	gets(str);
	i=system("ls -ls");
	printf("return %s\n",str);


	return 0;

}*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
int p[2], backup;
char buf[1000];

backup = dup(1);
close(0);
close(1);

pipe(p);
system ("ls -ls");
dup2(backup, 1);

printf("O system gerou os dados:\n");
while (fgets(buf, 1000, stdin)){
printf("%s", buf);
}
}
