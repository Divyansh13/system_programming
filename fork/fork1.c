#include<stdio.h>
#include<unistd.h>

int main(void)
{
	int ret;
	ret=fork();

	printf("fork() returned : %d\n",ret);
	while(1);
	return 0;
}
