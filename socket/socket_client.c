#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>

#define SOCKET_FILE "socketfile"

int main(void)
{
	int client_fd,err;
	struct sockaddr srv_addr;
	char buf[50];

	//4. Create client socket
	client_fd=socket(AF_UNIX,SOCK_STREAM,0);
	if(client_fd == -1)
	{
		perror("socket() call returned error: ");
		exit(1);
	}
	printf("Client socket created\n");

	memset(&srv_addr,0,sizeof(srv_addr));
	srv_addr.sa_family=AF_UNIX;
	strcpy(srv_addr.sa_data,SOCKET_FILE);

	//5. Connect to server socket address
	err=connect(client_fd,&srv_addr,sizeof(socklen_t));
	if(err == -1)
	{
		perror("connect() call returned error: ");
		exit(1);
	}
	printf("Connected to server socket");

	do
	{
		//7. Write to socket
		printf("Client: ");
		gets(buf);
		write(client_fd,buf,strlen(buf)+1);

		//10. Read from socket
		read(client_fd,buf,sizeof(buf));
		printf("server replied: %s\n",buf);
	}while(strcmp(buf,"bye")!=0);

	//11. close socket
	close(client_fd);
	printf("Client Socket closed\n");

	return 0;
}
