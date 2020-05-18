#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	int pid=-1;

	pid=fork();
	if(!pid)
	{
		printf("Child\t:My PID: %d\n",getpid());
		printf("Child\t:My parent PID: %d\n",getppid());
		while(1);
	}
	else
	{
		printf("Parent\t:My PID: %d\n",getpid());
		printf("Parent\t:My parent PID: %d\n",getppid());
		while(1);
	}
	return 0;
}
