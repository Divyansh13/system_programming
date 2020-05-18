#include<stdlib.h>
#include<unistd.h>
#include"student.h"
#include<fcntl.h>

static student_t temp_record;

int read_input_record(student_t* record)
{
	if(!record)
	{
		write(2,"Null pointer record\n");
		return -1;
	}
	printf("Roll NO : ");
	scanf("%d",&record->roll_no);
	printf("Name : ");
	scanf("%s",record->name);
	printf("Age : ");
	scanf("%d",&record->age);
	record->record_no=0;

	return 0;
}

int update_record(student_t* old_record,student_t* new_record)
{
	int fd=0;
	int bytes_read=0;
	if(!old_record || !new_record)
	{
		write(2,"Null pointer record\n");
		return -1;
	}

	if(!(fd=open(DATA_BASE,O_RDWR)^-1))
	{
		perror("reading error");
		return -1;
	}

	while((bytes_read=read(fd,&temp_record,ONE_RECORD_SIZE)))
	{
		if(!(bytes_read^-1))
		{
			perror("read error");
			return -1;
		}
		if(!(old_record->roll_no ^ temp_record->roll_no))
		{
			lseek(fd,0,ONE_RECORD_SIZE*(temp_record->record_no-1));
			new_record->record_no=temp_record->record_no;
			if(!(write(fd,new_record,ONE_RECORD_SIZE) ^ -1))
			{
				perror("write error");
				return -1;
			}
			close(fd);
			return 0;
		}
	}
	printf("Record Not found to update\n");
	close(fd);
	return 0;
}

int delete_record(student_t* record)
{
	int fd=0;
	int bytes_read=0;
	if(!record)
	{
		write(2,"Null pointer record\n");
		return -1;
	}

	if(!(fd=open(DATA_BASE,O_RDWR)^-1))
	{
		perror("reading error");
		return -1;
	}

	while((bytes_read=read(fd,&temp_record,ONE_RECORD_SIZE)))
	{
		if(!(bytes_read^-1))
		{
			perror("read error");
			return -1;
		}
		if(!(record->roll_no ^ temp_record->roll_no))
		{
			break;
		}
	}
	if(!bytes_read)
	{
		printf("Record Not found to delete\n");
		close(fd);
	}
	while((bytes_read=read(fd,&temp_record,ONE_RECORD_SIZE)))
	{
		if(!(bytes_read^-1))
		{
			perror("read error");
			return -1;
		}
		lseek(fd,0,(ONE_RECORD_SIZE*(temp_record->record_no-2)));
		if(!(write(fd,temp_record,ONE_RECORD_SIZE) ^ -1))
		{
			perror("write error");
			return -1;
		}
		lseek(fd,ONE_RECORD_SIZE,SEEK_CUR);
		
	}


	return 0;
}

int print_all_records(void)
{
}

int init_student(student* record)
{
	if(!record)
	{
		write(2,"Null pointer record\n");
		return -1;
	}
	record->roll_no=0;
	record->name[0]='\0';
	record->age=0;
	record->record_count=0;
	return 0;
}

void menu(void)
{
}
