#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(void)
{
	int arr[2],fd_read,fd_write;
	char w_buf[30],r_buf[30];

	pipe(arr);

	printf("Enter data: ");
	gets(w_buf);
	write(arr[1],w_buf,sizeof(w_buf));

	read(arr[0],r_buf,sizeof(r_buf));
	puts(r_buf);

	close(arr[0]);
	close(arr[1]);
	return 0;
}
