#include<stdio.h>
#include<pthread.h>
#include<sys/wait.h>
#include<unistd.h>

void* fun1(void* param)
{
	int i=0;
	for(i=0;i<10;i++)
	{
		printf("Thread : %d\n",i);
		sleep(1);
	}
	return NULL;
}

int main(void)
{
	int i=0,ret;
	pthread_t t1;

	ret=pthread_create(&t1,NULL,fun1,NULL);
	if(ret<0)
	{
		perror("pthread() call error: ");
		_exit(1);
	}

	for(i=0;i<10;i++)
	{
		printf("main : %d\n",i);
		sleep(1);
	}
	
	return 0;
}
