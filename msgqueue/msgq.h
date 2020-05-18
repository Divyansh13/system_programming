#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>

#define MSGKEY 0x1234

typedef struct 
{
	long id;
	char buf[30];
}msg_t;
