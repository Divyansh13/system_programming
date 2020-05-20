#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SOCKET_IP "127.0.0.1"
#define SERVER_PORT 2882

int main(void)
{
	int client_fd,err;
	struct sockaddr_in srv_addr;
	char buf[50];

	//4. Create client socket
	client_fd=socket(AF_INET,SOCK_STREAM,0);
	if(client_fd == -1)
	{
		perror("socket() call returned error: ");
		exit(1);
	}
	printf("Client socket created\n");

	memset(&srv_addr,0,sizeof(srv_addr));
	srv_addr.sin_family=AF_INET;
	srv_addr.sin_port=htons(SERVER_PORT);
	srv_addr.sin_addr.s_addr=inet_addr(SOCKET_IP);

	//5. Connect to server socket address
	err=connect(client_fd,&srv_addr,sizeof(srv_addr));
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
