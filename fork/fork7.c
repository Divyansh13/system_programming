#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	int pid=-1,i=0,s;
	int count=0;

	printf("Process counr: ");
	scanf("%d",&count);

	for(i=0;i<count;i++)
	{
		pid=fork();
		if(pid==0)
		{
			printf("child %d running\n",i);
			sleep(1);
			_exit(i);
		}
	}

	for(i=0;i<count;i++)
	{
		pid=waitpid(-1,&s,0);
		printf("Child %d returned %d exit stats of %d pid\n",i,WEXITSTATUS(s),pid);
	}
	return 0;
}
