#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

#define SOCKET_PATH "socketfile"
#define FILE_PATH "file.txt"

int main(void)
{
	int main_fd,srv_fd,err,file_fd;
	int file_sending=0;
	struct sockaddr srv_addr,cli_addr;
	socklen_t len;
	char file_buf[512];

	// 0. Unlink socket file
	unlink("so");

	//1. Create UNIX socket file as stream type with default protocol
	main_fd=socket(AF_UNIX,SOCK_STREAM,0);
	if(main_fd < 0)
	{
		perror("socket() call returned error: ");
		_exit(1);
	}
	printf("Server socket created\n");

	memset(&srv_addr,0,sizeof(srv_addr));
	srv_addr.sa_family=AF_UNIX;
	strcpy(srv_addr.sa_data,SOCKET_PATH);

	//2. Binding
	err=bind(main_fd,&srv_addr,sizeof(socklen_t));
	if(err < 0)
	{
		perror("bind() call returned error: ");
		exit(1);
	}
	printf("Server address bind donen");

	//3. Listen to socket for maximum 2 connection(backlogs)
	err=listen(main_fd,5);
	if(err < 0)
	{
		perror("listen() call returned error: ");
		exit(1);
	}
	printf("Server is listening for 2 connections maximum\n");
	printf("Server waiting for client connection..\n");
	//6. Accept connection from client if requested and create proxy socket
	//   or wait untill client raises request
	memset(&cli_addr,0,sizeof(cli_addr));
	srv_fd=accept(main_fd,&cli_addr,&len);
	if(srv_fd <0)
	{
		perror("1accept() call returned error: ");
		exit(1);
	}
	printf("Server accepted client connection\n");

	printf("Waiting for client input..\n");
	do
	{
		//9. Read
		if(!file_sending)
		{
			read(srv_fd,file_buf,sizeof(file_buf));
			if(strcmp(file_buf,"download") != 0)
			{
				continue;
			}
			file_sending++;
		}
		printf("Sending file\n",file_buf);

		file_fd=open(FILE_PATH,O_RDONLY);
		if(file_fd == -1)
		{
			perror("open() call error: ");
			_exit(1);
		}
		while((err=read(file_fd,file_buf,sizeof(file_buf))) != 0)
		{
			if(err == -1)
			{
				perror("read() call error: ");
				_exit(1);
			}
			write(srv_fd,file_buf,err);
			printf("#");
		}
		file_sending=0;
		printf("\nFile sent successfully\n");
		break;
	}while(strcmp(file_buf,"stop") != 0);

	//12. CLose target socket
	close(srv_fd);
	printf("Target socket closed\n");

	//13. Shutdowm server
	shutdown(main_fd,SHUT_RDWR);
	printf("Server socket closed\n");
	return 0;
}
