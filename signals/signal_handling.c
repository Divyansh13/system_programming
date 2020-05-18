#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>

void signal_INT(int sig)
{
	printf("Handled SIGINT with %d parameter\n",sig);
}

void signal_TERM(int sig)
{
	printf("Handled SIGTERM with %d parameter\n",sig);
}

void signal_SEGV(int sig)
{
	printf("Handled SIGSEGV with %d parameter\n",sig);
}

int main(void)
{
	struct sigaction s,s_old;
	sigset_t s_set,s_set_old;
	int err=0,temp=0;
	char *SEG_VAR=NULL;
	memset(&s,0,sizeof(s));
	s.sa_handler=signal_INT;
	err=sigaction(SIGINT,&s,&s_old);
	if(err == -1)
	{
		perror("sigaction returned with error: ");
		exit(1);
	}

	memset(&s,0,sizeof(s));
	s.sa_handler=signal_TERM;
	err=sigaction(SIGTERM,&s,&s_old);
	if(err == -1)
	{
		memset(&s,0,sizeof(s));
	s.sa_handler=signal_INT;
	err=sigaction(SIGINT,&s,&s_old);
	if(err == -1)
	{
		perror("sigaction returned with error: ");
		exit(1);
	}
		perror("sigaction returned with error: ");
		exit(1);
	}

	memset(&s,0,sizeof(s));
	s.sa_handler=signal_SEGV;
	err=sigaction(SIGSEGV,&s,&s_old);
	if(err == -1)
	{
		perror("sigaction returned with error: ");
		exit(1);
	}

	sigemptyset(&s_set);
	sigemptyset(&s_set_old);
	sigaddset(&s_set,SIGSEGV);
	err=sigprocmask(SIG_SETMASK,&s_set,&s_set_old);
	if(err == -1)
	{
		perror("sigprocmask() returned with error: ");
		exit(1);
	}

	while(1)
	{
		printf("running\n");
		sleep(1);
		if(temp++ == 10)
		{
			temp=0;
			*SEG_VAR='A';
		}
	}


	return 0;
}
