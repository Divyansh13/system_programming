#include"msgq.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	msg_t msg;
	int mid;
	mid=msgget(MSGKEY,IPC_CREAT|0600);
	printf("Message : ");
	scanf("%s",msg.buf);
	msg.id=101;
	msgsnd(mid,&msg,sizeof(msg)-sizeof(long),0);
	printf("Message sent\n");
	return 0;
}
