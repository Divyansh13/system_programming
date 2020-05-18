#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	int fd_src=-1,fd_dest=-1,read_bytes;
	char temp_buf[512];
	
	if(argc^3)
	{
		fprintf(stderr,"Syntax: %s <src file path> <dest file path>\n",argv[0]);
		exit(1);
	}

	if(!((fd_src=open(argv[1],O_RDONLY))^-1))
	{
		perror("Source file reading error");
		exit(1);
	}

	if(!((fd_dest=open(argv[2],O_WRONLY|O_CREAT,00664))^-1))
	{
		close(fd_src);
		perror("Destination file opening error");
		exit(1);
	}

	printf("Copying");
	while((read_bytes=read(fd_src,temp_buf,sizeof(temp_buf)))^-1)
	{
		if(!(read_bytes^0))
		{
			close(fd_src);
			close(fd_dest);
			fprintf(stdout,"\nCopying completed\n");
			return 0;
		}
		printf(".");

		if(!(write(fd_dest,temp_buf,read_bytes) ^ -1))
		{
			close(fd_src);
			close(fd_dest);
			perror("\nDestination file writing failed while copying");
			exit(1);
		}
	}

	close(fd_src);
	close(fd_dest);
	perror("\nSource file reading error while copying");
	return 1;
}
