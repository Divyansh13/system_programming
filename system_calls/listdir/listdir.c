#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(int argc,char *argv[])
{
	struct dirent *ent;
	if(argc !=2)
	{
		fprintf(stderr,"syntax: %s <dir path>\n",argv[0]);
		exit(1);
	}

	DIR *dir=opendir(argv[1]);
	while((ent=readdir(dir)) != NULL)
	{
		fprintf(stdout,"%ld -> %s\n",ent->d_ino,ent->d_name);
	}
	closedir(dir);
	return 0;
}
