#include<stdio.h>

typedef struct
{
	int roll_no;
	char name[50];
	int age;
	int record_no;
}student_t;


#define DATA_BASE "student.db"
#define ONE_RECORD_SIZE	sizeof(student_t)

extern int read_input_record(student_t*);
extern int update_record(student_t*,student_t*);
extern int delete_record(student_t*);
extern int print_all_records(void);
extern int init_student(student*);
extern void menu(void);
