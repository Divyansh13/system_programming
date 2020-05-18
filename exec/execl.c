#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

/* execl need PATH variable to execute linux commands
	 PATH vraibel can be got from command line argument as 3 char* in main()
	 in that list PATH variable exists as string like "PATH=/usr/...."
	 You have to do string operations to get only that path and give for execl
	 */

int main(int argc,char *argv[])
{
	int pid,err,pid_status;
	pid=fork();
	printf("Parent started\n");
	if(pid==0)
	{
		err=execl("./example","example",NULL);
		if(err == -1)
		{
			exit(1);
		}
	}
	else
	{
		waitpid(pid,&pid_status,0);
		printf("child exited with status : %d\n",WEXITSTATUS(pid_status));
	}
	printf("Parent terminated\n");
	return 0;
	
}
