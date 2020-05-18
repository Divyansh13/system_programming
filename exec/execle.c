#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[],char *argp[])
{
	int pid,pid_status,err;
	pid=fork();
	if(pid == 0)
	{
		err=execle("./example","example",NULL,argp);
		if(err == -1)
		{
			perror("execlp() exited with error status: ");
			exit(1);
		}
	}
	else
	{
		waitpid(pid,&pid_status,0);
		printf("Child exited with status : %d\n",pid_status);
	}
	return 0;
}
