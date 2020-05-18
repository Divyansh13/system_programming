#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int fd=-1;
	char read_buf[20];


	if(!((fd=open("./test.txt",O_CREAT,00664)) ^ -1))
	{
		perror("file creation failed");
		exit(1);
	}

	close(fd);
	if(!((fd=open("./test.txt",O_WRONLY)) ^ -1))
	{
		perror("file open failed in write mode");
		exit(1);
	}


	if(!(write(fd,"test\n",5) ^ -1))
	{
		printf("%d\n",fd);
		perror("file write failed ");
		close(fd);
		exit(1);
	}

	close(fd);
	if(!((fd=open("./test.txt",O_RDONLY)) ^ -1))
	{
		perror("file open failed in read mode");
		exit(1);
	}

	if(!((read(fd,read_buf,5)) ^ -1))
	{
		perror("file read failed ");
		close(fd);
		exit(1);
	}

	printf("Read from file: %s\n",read_buf);

	close(fd);
	return 0;
}
