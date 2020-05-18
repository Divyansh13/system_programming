#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#define PIPENAME "./fifofile"

int main(void)
{
	int fd,err;
	char buf[30];

	err= mkfifo(PIPENAME,0666);
	fd=open(PIPENAME,O_WRONLY);
	printf("Enter data: ");
	gets(buf);

	write(fd,buf,sizeof(buf));
	close(fd);
	return 0;
}
