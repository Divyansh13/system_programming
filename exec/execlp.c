#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	int pid,err,pid_status;
	printf("Parent started\n");
	pid=fork();
	if(pid==0)
	{
		err=execlp("ls","ls","-la",NULL);
		if(err == -1)
		{
			perror("Exec exited with error: ");
			exit(1);
		}
	}
	else
	{
		waitpid(pid,&pid_status,0);
		printf("Child terminated with exit status : %d\n",WEXITSTATUS(pid_status));
	}
	printf("Parent terminated\n");
	return 0;
}
