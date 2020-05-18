#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define PIPENAME "./fifofile"

int main(void)
{
	int fd,err;
	char buf[30];
	fd=open(PIPENAME,O_RDONLY);
	read(fd,buf,sizeof(buf));
	puts(buf);
	close(fd);

	return 0;
}
