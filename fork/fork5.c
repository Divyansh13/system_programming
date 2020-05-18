#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	int ret=-1,i=0,s=0;

	ret=fork();

	if(!ret)
	{
		for(i=0;i<10;i++)
		{
			printf("child\t:\t%d\n",i);
			sleep(1);
		}
		_exit(5);
	}
	else
	{
		for(i=0;i<20;i++)
		{
			printf("parent\t:\t%d\n",i);
			sleep(1);
			if(!(i^10))
			{
				wait(&s);
				printf("child exit status : %d\n",WEXITSTATUS(s));
			}
		}
	}
	return 0;
}
