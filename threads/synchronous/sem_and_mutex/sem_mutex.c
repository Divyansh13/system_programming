#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<string.h>

#define MAX 5

/*circular buffer*/
typedef struct
{
	int arr[MAX];
	int front,rear,count;
}circ_t;

circ_t cb;

sem_t sr,sw,s_multiple;
pthread_mutex_t mutex_lock;

void* writer(void *param)
{
	int num;
	while(1)
	{
		//Lock
		sem_wait(&s_multiple);
		pthread_mutex_lock(&mutex_lock);
		num=rand() %100;
		cb.rear=(cb.rear+1)%MAX;
		cb.arr[cb.rear]=num;
		cb.count++;
		printf("WR : %d\n",num);
		pthread_mutex_unlock(&mutex_lock);
		sem_post(&sr);
		//Unlock
		sleep(1);
	}
	return NULL;
}

void* reader(void *param)
{
	int num;
	while(1)
	{
		//Lock
		sem_wait(&sr);
		pthread_mutex_lock(&mutex_lock);
		num=rand() %100;
		cb.front=(cb.front+1)%MAX;
		num=cb.arr[cb.front];
		cb.count--;
		printf("RD : %d\n",num);
		pthread_mutex_unlock(&mutex_lock);
		sem_post(&s_multiple);
		//Unlock
		sleep(1);
	}
	return NULL;
}


int main(void)
{
	pthread_t wr,rd;
	int ret;
	pthread_mutexattr_t mutex_lock_attrib;

	sem_init(&sr,0,0);//for blocking reader when writer is writing
	sem_init(&sw,0,1);//for blocking writer when reader is reading
	sem_init(&s_multiple,0,MAX);//for allowing writer/reader to 
															//write/read untill MAX number of 
															//times instead or writing one and 
															//read one value

	/***Mutex initialization***/
	//Mutex attribute variable allocation
	pthread_mutexattr_init(&mutex_lock_attrib);
	//Mutex attribute variable type setting
	pthread_mutexattr_settype(&mutex_lock_attrib,PTHREAD_MUTEX_ERRORCHECK);
	//Initializing mutex with given attributes
	pthread_mutex_init(&mutex_lock,&mutex_lock_attrib);

	ret=pthread_create(&wr,NULL,writer,NULL);
	if(ret<0)
	{
		perror("pthread_create() call error: ");
		_exit(1);
	}

	ret=pthread_create(&rd,NULL,reader,NULL);
	if(ret<0)
	{
		perror("pthread_create() call error: ");
		_exit(1);
	}

	getchar();
	sem_destroy(&sr);
	sem_destroy(&sw);
	sem_destroy(&s_multiple);
	pthread_mutex_destroy(&mutex_lock);
	return 0;
}
