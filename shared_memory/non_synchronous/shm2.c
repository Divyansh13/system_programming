#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

typedef struct
{
	int count;
}data_t;

#define SHM_KEY 0x12345

int main(void)
{
	int pid,i,shmid;
	data_t *p=NULL;

	// Allocate a shared memory area and get the ID of it
	shmid=shmget(SHM_KEY,sizeof(data_t),IPC_CREAT | 0600);
	if(shmid == -1)
	{
		perror("shmget() call error: ");
		_exit(1);
	}

	// Attach the shared memory allocated with ID to your pointer
	p=(data_t*)shmat(shmid,NULL,0);
	if(p == (void*)-1)
	{
		perror("shmat() call error: ");
		_exit(1);
	}

	p->count=0;
	pid=fork();
	if(pid==0)
	{
		//Child
		for(i=0;i<10;i++)
		{
			printf("Child  |  p->count : %2d\n",++p->count);
			sleep(1);
		}
		shmdt(p);
	}
	else
	{
		//Parent
		for(i=0;i<10;i++)
		{
			printf("Parent |  p->count : %2d\n",--p->count);
			sleep(1);
		}
		shmdt(p);
		shmctl(shmid,IPC_RMID,NULL);
	}
	return 0;
}
