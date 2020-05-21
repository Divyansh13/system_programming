#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct
{
	int count;
}data_t;


int main(void)
{
	int pid,i;
	data_t *p=(data_t*)malloc(sizeof(data_t));

	p->count=0;

	pid=fork();
	if(pid==0)
	{
		for(i=0;i<10;i++)
		{
			printf("child: p->count : %d\n",--p->count);
			sleep(1);
		}
		free(p);
	}
	else
	{
		for(i=0;i<10;i++)
		{
			printf("Parent: p->count : %d\n",++p->count);
			sleep(1);
		}
		free(p);
	}
	return 0;
}
