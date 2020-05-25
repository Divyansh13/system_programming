#include<stdio.h>
#include<pthread.h>
#include<sys/wait.h>
#include<unistd.h>

void* fun1(void* param)
{
	int i=0,params=(int*)param;
	for(i=0;i<10;i++)
	{
		if(params == 1)
		{
			printf("Thread1 : %d\n",i);
			sleep(1);
		}
		else if (params == 2)
		{
			printf("Thread2 : %d\n",i);
			sleep(1);
		}
	}
	return (void*)15;
}


int main(void)
{
	int i=0,ret;
	int ret1,ret2;
	pthread_t t1,t2;

	ret=pthread_create(&t1,NULL,fun1,(void*)1);
	if(ret<0)
	{
		perror("pthread() call error: ");
		_exit(1);
	}

	ret=pthread_create(&t2,NULL,fun1,(void*)2);
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

	pthread_join(t1,(void**)&ret1);
	printf("ret1=%d\n",ret1);
	pthread_join(t2,(void**)&ret2);
	return 0;
}
