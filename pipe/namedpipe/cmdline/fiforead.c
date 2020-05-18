#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define PIPEFILE "pipefile"
/* Create 'pipefile' with "mkfifo pipefile" command in cmnd line*/

int main(void)
{
	int fd;
	char buf[30];

	fd=open(PIPEFILE,O_RDONLY);
	if(fd==-1)
	{
		perror("open() call error : ");
		exit(1);
	}
	read(fd,buf,sizeof(buf));
	puts(buf);
	close(fd);
	return 0;
}
