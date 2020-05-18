#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	char *path,path_buf[1024];
	if(argc^2)
	{
		fprintf(stderr,"syntx: %s <directory path>\n",argv[0]);
		exit(1);
	}

	if(!(path=getcwd(path_buf,sizeof(path_buf))))
	{
		perror("getwd() error");
		exit(1);
	}
	fprintf(stdout,"Current directory: %s\n",path_buf);

	if(!((chdir(argv[1]))^-1))
	{
		perror("chdir() error");
		exit(1);
	}
	fprintf(stdout,"change directory sucessfull\n");

	if(!(path=getcwd(path_buf,sizeof(path_buf))))
	{
		perror("getwd() error");
		exit(1);
	}
	fprintf(stdout,"Current directory: %s\n",path_buf);
	return 0;
}
