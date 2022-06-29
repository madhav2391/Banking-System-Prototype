#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdbool.h>
#include"header.h"


int main(){
  int fd;
  int choice;
  fd=open("jointusers.txt",O_CREAT|O_RDWR,0744);
  jointu jtemp;
  while(1){
 printf("enter the following details\n");
	printf("user id :");
  	scanf("%d",&jtemp.user_id);
  	printf("username 1:");
  	scanf(" %[^\n]",jtemp.user_name_a);
  	printf("username 2:");
  	scanf(" %[^\n]",jtemp.user_name_b);
  	printf("password :");
  	scanf(" %[^\n]",jtemp.password);
  	printf("account number:");
  	scanf("%d",&jtemp.account_number);
  	printf("balance :");
  	scanf("%f",&jtemp.balance);
  	jtemp.status=true;
  	write(fd,&jtemp,sizeof(jointu));
    break;
  }
  close(fd);
}
