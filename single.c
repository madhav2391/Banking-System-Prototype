#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdbool.h>
#include"header.h"

int main(){
int fd;
int choice;
fd=open("singleusers.txt",O_CREAT|O_RDWR,0744);
singleu stemp;
while(1){
printf("enter the following details\n");
	printf("user id :");
	scanf("%d",&stemp.user_id);
	printf("username:");
	scanf(" %[^\n]",stemp.user_name);
	printf("password :");
	scanf(" %[^\n]",stemp.password);
	printf("account number:");
	scanf("%d",&stemp.account_number);
	printf("balance :");
	scanf("%f",&stemp.balance);
	stemp.status=true;
	write(fd,&stemp,sizeof(singleu));
	break;
}
close(fd);
}
