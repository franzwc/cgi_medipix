#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main()
{
	int i;
	int fd;
	int rd_count;
	unsigned char rd_buf[8];
	unsigned char alarms[8] = {0};

	if ((fd = open("/dev/busydev", O_RDWR)) == -1) 
	{
		printf("Error! Failed to open busydev!\n");
		return 0;
	}

	lseek(fd, 0, SEEK_SET);
	rd_count = read(fd, rd_buf,8);
	
	if (rd_count < 0) 
	{
		fprintf(stderr,"Error! Failed to read from busydev!\n");
		close(fd);
		return 0;
	} 
	else 
	{

		alarms[0] = rd_buf[0] & 0001;
		close(fd);
	}
    /*fprintf(stderr,"count %d\n",&rd_count);
    fprintf(stderr,"rdbuf %s\n",&rd_buf);

    fprintf(stderr,"rdbuf[1] %s\n",&rd_buf[0]);
    fprintf(stderr,"rdbuf[1] %s\n",&rd_buf[1]);
    fprintf(stderr,"rdbuf[1] %s\n",&rd_buf[2]);*/

	fprintf(stderr,"rdbuf[1] %d\n",rd_buf[0]);
    //fprintf(stderr,"rdbuf[1] %d\n",rd_buf[1]);
    //fprintf(stderr,"rdbuf[1] %d\n",rd_buf[2]);

	fprintf(stderr,"alarm[1] %d\n",alarms[0]);
    //fprintf(stderr,"alarm[1] %d\n",&alarms[0]);

}
