#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdbool.h>

#include"header.h"

int main(){
int fd;
fd=open("adminusers.txt",O_CREAT|O_RDWR,0744);
adminu adtemp;
while(1){
printf("enter the following details\n");
	printf("user id :");
	scanf("%d",&adtemp.admin_id);
	printf("username :");
	scanf(" %[^\n]",adtemp.user_name);
	printf("password :");
	scanf(" %[^\n]",adtemp.password);
	write(fd,&adtemp,sizeof(adminu));
  break;
}
close(fd);
}
