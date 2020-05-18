#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	int pid,s,count=1;
	while(1)
	{
		pid=fork();
		if(!(pid^-1))
		{
			perror("fork() failed");
			break;
		}
		if(!pid)
		{
			printf("child %d running\n",count);
			_exit(0);
		}
		count++;
	}

	printf("Maximum no of process cam be created: %d\n",count);
	
	getchar();
	while((waitpid(-1,&s,0))>0);
	return 0;
}
