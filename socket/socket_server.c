#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define SOCKET_FILE "socketfile"

int main(void)
{
	int socket_fd,srv_fd,err;
	struct sockaddr srv_addr,cli_addr;
	socklen_t len;
	char buf[50];

	// 0. Unlink socket file
	unlink("so");

	//1. Create UNIX socket file as stream type with default protocol
	socket_fd=socket(AF_UNIX,SOCK_STREAM,0);
	if(socket_fd == -1)
	{
		perror("socket() call returned error: ");
		exit(1);
	}
	printf("Server socket created\n");

	memset(&srv_addr,0,sizeof(srv_addr));
	srv_addr.sa_family=AF_UNIX;
	strcpy(srv_addr.sa_data,SOCKET_FILE);

	//2. Binding
	err=bind(socket_fd,&srv_addr,sizeof(socklen_t));
	if(err == -1)
	{
		perror("bind() call returned error: ");
		exit(1);
	}
	printf("Server address bind donen");

	//3. Listen to socket for maximum 2 connection(backlogs)
	err=listen(socket_fd,2);
	if(err == -1)
	{
		perror("listen() call returned error: ");
		exit(1);
	}
	printf("Server is listening for 2 connections maximum\n");
	printf("Server waiting for client connection..\n");
	//6. Accept connection from client if requested and create proxy socket
	//   or wait untill client raises request
	memset(&cli_addr,0,sizeof(cli_addr));
	srv_fd=accept(socket_fd,&cli_addr,&len);
	if(srv_fd == -1)
	{
		perror("accept() call returned error: ");
		exit(1);
	}
	printf("Server accepted client connection\n");

	do
	{
		//9. Read
		read(srv_fd,buf,sizeof(buf));
		printf("Client sent: %s\n",buf);

		//Write
		printf("Server: ");
		gets(buf);
		write(srv_fd,buf,sizeof(buf));
	}while(strcmp(buf,"bye") != 0);

	//12. CLose target socket
	close(srv_fd);
	printf("Target socket closed\n");

	//13. Shutdowm server
	shutdown(socket_fd,SHUT_RDWR);
	printf("Server socket closed\n");
	return 0;
}
