#include"msgq.h"
#include<stdio.h>

int main(void)
{
	msg_t msg;
	int mid;
	
	mid=msgget(MSGKEY,IPC_CREAT|0600);
	printf("Waiting for msg..\n");
	msgrcv(mid,&msg,sizeof(msg_t)-sizeof(long),101,0);
	printf("Message received: %s\n",msg.buf);
	msgctl(mid,IPC_RMID,NULL);
	return 0;
}
