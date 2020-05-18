#include<stdio.h>
#include<unistd.h>

int main(void)
{
	int ret=-1,i=0;

	ret=fork();

	if(!ret)
	{
		for(i=0;i<25;i++)
		{
			printf("child\t:\t%d\n",i);
			sleep(1);
		}
	}
	else
	{
		for(i=0;i<10;i++)
		{
			printf("parent\t:\t%d\n",i);
			sleep(1);
		}
	}
	return 0;
}
