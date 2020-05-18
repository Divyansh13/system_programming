#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define PIPEFILE "pipefile"

int main(void)
{
	int fd;
	char buf[30];

	fd=open(PIPEFILE,O_WRONLY);
	if(fd==-1)
	{
		perror("open() call error: ");
		exit(1);
	}

	printf("Enter data: ");
	gets(buf);

	write(fd,buf,sizeof(buf));
	close(fd);
	return 0;
}
