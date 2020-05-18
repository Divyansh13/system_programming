#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	int pid,pid_status,err;
	char *const *file="example";
	pid=fork();
	if(!pid)
	{
		err=execv("./example",file);
		if(err == -1)
		{
			perror("execv() exited with status:");
			exit(1);
		}
	}
	else
	{
		waitpid(pid,&pid_status,0);
		printf("Child terminated with exit status: %d\n",WEXITSTATUS(pid_status));
	}
	return 0;
}
