#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	int pid=-1,s=0;

	pid=fork();
	if(!pid)
	{
		printf("child 1\n");
		_exit(1);
	}
	pid=fork();
	if(!pid)
	{
		printf("child 2\n");
		_exit(2);
	}
	pid=fork();
	if(!pid)
	{
		printf("child 3\n");
		_exit(3);
	}

	while(waitpid(-1,&s,0)>0);
	return 0;
}
