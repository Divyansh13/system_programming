#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(int argc,char* argv[])
{
	struct stat stat_buf;
	int fd=-1;
	
	if(argc != 2)
	{
		fprintf(stderr,"Syntax: %s <file path>\n",argv[0]);
		exit(1);
	}
	
	if(!((fd=open(argv[1],O_RDONLY)) ^ -1))
	{
		perror("Error:");
		exit(1);
	}

	if(!((fstat(fd,&stat_buf)) ^ -1))
	{
		perror("Error:");
		exit(1);
	}

	printf("Device ID : %ld\n",stat_buf.st_dev);
	printf("Inode : %ld\n",stat_buf.st_ino);

	if(S_ISREG(stat_buf.st_mode)){printf("Regular file\n");}

	close(fd);
	return 0;
}
