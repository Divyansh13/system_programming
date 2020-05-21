#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/types.h>

typedef struct
{
	int count;
}data_t;

union semun
{
	int val;	/* Value for SETVAL */
	struct semid_ds *buf;	/*Buffer for IPC_STAT, IPC_SET*/
	unsigned short *array;	/* Array for GETALL, SETALL */
	struct seminfo *__buf;	/* Buffer for IPC_INFO (Linux-specific) */

};

#define SHM_KEY 0x12345
#define SEM_KEY 0x11111

int main(void)
{
	int pid,i,shmid,semid,ret;
	data_t *p=NULL;
	union semun su;
	struct sembuf op[1];

	/***Shared Memory Creation****/
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
	/*****************************/

	/***Semaphore creation***/
	semid=semget(SEM_KEY,1,IPC_CREAT | 0600);
	if(semid == -1)
	{
		perror("semget() call error: ");
		_exit(1);
	}

	su.val=1;
	ret=semctl(semid,0,SETVAL,su);
	if(ret == -1)
	{
		perror("semctl() call error: ");
		_exit(1);
	}
	/************************/



	p->count=0;
	pid=fork();
	if(pid==0)
	{
		//Child
		for(i=0;i<10;i++)
		{
			//P(s)
			op[0].sem_num=0;
			op[0].sem_op=-1;
			op[0].sem_flg=0;
			ret=semop(semid,op,1);
			if(ret == -1)
			{
				perror("semop() call error: ");
				_exit(1);
			}
			printf("Child  |  p->count : %2d\n",++p->count);
			//V(s)
			op[0].sem_num=0;
			op[0].sem_op=+1;
			op[0].sem_flg=0;
			ret=semop(semid,op,1);
			if(ret == -1)
			{
				perror("semop() call error: ");
				_exit(1);
			}
			sleep(1);
			
		}
		shmdt(p);
	}
	else
	{
		//Parent
		for(i=0;i<10;i++)
		{
			//P(s)
			op[0].sem_num=0;
			op[0].sem_op=-1;
			op[0].sem_flg=0;
			ret=semop(semid,op,1);
			if(ret == -1)
			{
				perror("semop() call error: ");
				_exit(1);
			}
			printf("Parent |  p->count : %2d\n",--p->count);
			//V(s)
			op[0].sem_num=0;
			op[0].sem_op=+1;
			op[0].sem_flg=0;
			ret=semop(semid,op,1);
			if(ret == -1)
			{
				perror("semop() call error: ");
				_exit(1);
			}
			sleep(1);
		}
		shmdt(p);
		shmctl(shmid,IPC_RMID,NULL);
		semctl(semid,0,IPC_RMID);
	}
	return 0;
}
