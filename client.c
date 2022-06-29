#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdbool.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<arpa/inet.h>


#include"header.h"

int Intro(int scfd);
void terminate();

void single_login(int scfd);
void joint_login(int scfd);
void admin_login(int scfd);

void user_choice(int scfd, int type);
void admin_choices(int scfd);

void view(int scfd, int type);
void balenq(int scfd, int type);

void Deposit(int scfd, int type);
void Withdrawl(int scfd, int type);

void pwdmod(int scfd, int type);


void addacc(int scfd);
void delacc(int scfd);
void Modacc(int scfd);
void find(int scfd);

int checkbit = 0;

int Intro(int scfd)
{
write(1,"Online banking system. please choise a option\n",sizeof("Online banking system. please choise a option\n"));
write(1,"Type 'S' for single user account \n 'J' for jointaccount \n 'A' for adminaccount\n",sizeof("Type 'S' for single user account \n 'J' for jointaccount \n 'A' for adminaccount\n"));
char user_type;
int type;
read(0,&user_type,sizeof(user_type));

  if(user_type=='S')
  {
      type = 1;
      write(scfd,&type,sizeof(type));
      single_login(scfd);
  }

  else if(user_type=='J')
  {
     type = 2;
     write(scfd,&type,sizeof(type));
     joint_login(scfd);
  }

  else if(user_type=='A')
  {
    type = 3;
    write(scfd,&type,sizeof(type));
    admin_login(scfd);
  }

  else
  {
    write(1,"Invalid input\n",sizeof("Invalid input\n"));
  }
return type;
}



void terminate()
{
  exit(0);
}



void single_login(int scfd)
{
  singleu stemp;
  write(1,"Enter UserId : ",sizeof("Enter UserId : "));
  scanf("%d",&stemp.user_id);
  write(1,"Enter Username : ",sizeof("Enter Username : "));
  read(0,&stemp.user_name,sizeof(stemp.user_name));
  write(1,"Enter Password : ",sizeof("Enter Password : "));
  read(0,&stemp.password,sizeof(stemp.password));

  write(scfd,&stemp.user_id,sizeof(stemp.user_id));
  write(scfd,&stemp.user_name,sizeof(stemp.user_name));
  write(scfd,&stemp.password,sizeof(stemp.password));
  read(scfd,&checkbit,sizeof(checkbit));

  return;

}

void joint_login(int scfd)
{
  jointu jtemp;

  write(1,"Enter UserId : ",sizeof("Enter UserId : "));
  scanf("%d",&jtemp.user_id);
  write(1,"Enter Username : ",sizeof("Enter Username : "));
  read(0,&jtemp.account_name,sizeof(jtemp.account_name));
  write(1,"Enter Password : ",sizeof("Enter Password : "));
  read(0,&jtemp.password,sizeof(jtemp.password));

  write(scfd,&jtemp.user_id,sizeof(jtemp.user_id));
  write(scfd,&jtemp.account_name,sizeof(jtemp.account_name));
  write(scfd,&jtemp.password,sizeof(jtemp.password));

  read(scfd,&checkbit,sizeof(checkbit));

  return;

}

void admin_login(int scfd)
{
  adminu atemp;

  write(1,"Enter AdminId : ",sizeof("Enter AdminId : "));
  scanf("%d",&atemp.admin_id);
  write(1,"Enter Admin Username : ",sizeof("Enter Admin Username : "));
  read(0,&atemp.user_name,sizeof(atemp.user_name));
  write(1,"Enter Password : ",sizeof("Enter Password : "));
  read(0,&atemp.password,sizeof(atemp.password));

  write(scfd,&atemp.admin_id,sizeof(atemp.admin_id));
  write(scfd,&atemp.user_name,sizeof(atemp.user_name));
  write(scfd,&atemp.password,sizeof(atemp.password));
  read(scfd,&checkbit,sizeof(checkbit));

  return;

}



void user_choice(int scfd, int type)
{
  int selection;
  write(1,"select a user choice\n",sizeof("select a user choice\n"));
  write(1," 1:Account Details\n 2: Balance Enquiry\n 3: Deposit\n 4: Withdrawl\n 5: Password Change\n  6: terminate\n ",sizeof(" 1:Account Details\n 2: Balance Enquiry\n 3: Deposit\n 4: Withdrawl\n 5: Password Change\n  6: terminate\n "));
  scanf("%d",&selection);

  switch(selection)
  {
    case 1:
      write(scfd,&selection,sizeof(selection));
      view(scfd,type);
      break;

    case 2:
      write(scfd,&selection,sizeof(selection));
      balenq(scfd,type);
      break;

    case 3:
      write(scfd,&selection,sizeof(selection));
      Deposit(scfd,type);
      break;
    case 4:
      write(scfd,&selection,sizeof(selection));
      Withdrawl(scfd,type);
      break;

    case 5:
      write(scfd,&selection,sizeof(selection));
      pwdmod(scfd,type);
      break;

    case 6:
      write(scfd,&selection,sizeof(selection));
      terminate();
      break;
    default:
     write(1,"Invalid Selection\n",sizeof("Invalid Selection\n"));
     break;
  }

  return ;
}

void admin_choices(int scfd)
{
  int selection;
  write(1," Admin selection: \n",sizeof(" Admin selection: \n"));
  write(1,"1:Add Account\n 2: Delete Account\n 3: Modify Account\n 4: find\n 5:Change Password\n 6: terminate\n",sizeof("1:Add Account\n 2: Delete Account\n 3: Modify Account\n 4: find\n 5:Change Password\n 6: terminate\n"));
  scanf("%d",&selection);
  switch(selection)
  {
    case 1:
      write(scfd,&selection,sizeof(selection));
      addacc(scfd);
      break;
    case 2:
      write(scfd,&selection,sizeof(selection));
      delacc(scfd);
      break;
    case 3:
      write(scfd,&selection,sizeof(selection));
      Modacc(scfd);
      break;
    case 4:
      write(scfd,&selection,sizeof(selection));
      find(scfd);
      break;
    case 5:
      write(scfd,&selection,sizeof(selection));
      pwdmod(scfd,3);
      break;
    case 6:
      write(scfd,&selection,sizeof(selection));
      terminate();
      break;
    default:
     write(1,"Invalid Selection\n",sizeof("Invalid Selection\n"));
     break;

  }
  return;
}



void view(int scfd, int type)
{
  if(type==1)
  {
    singleu stemp;
    read(scfd,&stemp,sizeof(stemp));
    printf("Username = %s\n",stemp.user_name);
    printf("Account Number =%d\n",stemp.account_number);
    printf("Balance = %f\n",stemp.balance);
        printf("passworrd= %s\n",stemp.password);
  }
  else if(type==2)
  {
    jointu jtemp;
    read(scfd,&jtemp,sizeof(jtemp));
    printf("Username1 = %s\n",jtemp.user_name_a);
    printf("Username2 = %s\n",jtemp.user_name_b);
    printf("Account Number =%d\n",jtemp.account_number);
    printf("Balance = %f\n",jtemp.balance);
            printf("passworrd= %s\n",jtemp.password);
  }
  user_choice(scfd,type);
}


void balenq(int scfd, int type)
{
  float bal;
  read(scfd,&bal,sizeof(bal));
  write(1,"Current Balance in this account is: ",sizeof("Current Balance in this account is: "));
  printf("%f\n",bal);
  user_choice(scfd,type);
  return;
}

void Deposit(int scfd, int type)
{
   float damt;
   write(1,"Enter Amount for deposit\n",sizeof("Enter Amount for deposit\n"));
   scanf("%f",&damt);
   write(1,"check: Depositing Rupees ",sizeof("check: Depositing Rupees "));
   printf("%f\n",damt);

   write(scfd,&damt,sizeof(damt));
   int transfer = 1;
   write(scfd,&transfer,sizeof(transfer));
   int check;
   read(scfd,&check,sizeof(check));
   if(check)
   {
     write(1,"Successfully Deposited\n",sizeof("Successfully Deposited\n"));
   }
   else
   {
     write(1,"Deposit Unsuccessful.",sizeof("Deposit Unsuccessful."));
   }

   user_choice(scfd, type);
   return;
}

void Withdrawl(int scfd, int type)
{
  float wamt;
  write(1,"Enter Amount to Withdraw\n",sizeof("Enter Amount to Withdraw\n"));
  scanf("%f",&wamt);
  write(1,"check: Withdrawing Rupees\n",sizeof("check: Withdrawing Rupees\n"));
  printf("%f\n",wamt);
  write(scfd,&wamt,sizeof(wamt));
  int check;
  read(scfd,&check,sizeof(check));
  if(check)
  {
    write(1,"Withdraw sucessful\n",sizeof("Withdraw sucessful\n") );
  }
  else
  {
    write(1,"Insufficient Balance\n",sizeof("Insufficient Balance\n"));
  }
  user_choice(scfd,type);
  return;
}


void pwdmod(int scfd, int type)
{

  char new_password[20];

  int check;
  check=0;

    write(1,"Enter New Password : ",sizeof("Enter New Password : "));
    read(0,&new_password,sizeof(new_password));
    write(scfd,&new_password,sizeof(new_password));
   
   
//printf("check: %d",check);
 
    read(scfd,&check,check);

    write(1,"Password successfully chaged and login again with new credentials\n",sizeof("Password successfully chaged and login again with new credentials\n"));

          terminate();

  return ;
}


void addacc(int scfd)
{
  int check;
  char user_type;
  int type;
  write(1,"ADD user choices:\n",sizeof("ADD user choices:\n"));
  write(1,"'S': singleaccount\n 'J': jointaccount\n",sizeof("'S': singleaccount\n 'J': jointaccount\n"));
  read(0,&user_type,sizeof(user_type));

  if(user_type=='S')
  {
     singleu stemp;
     type = 1;
     write(1,"Enter Username\n",sizeof("Enter Username\n"));
     scanf(" %[^\n]",stemp.user_name);
     write(1,"Enter Password\n",sizeof("Enter Password\n"));
     scanf(" %[^\n]",stemp.password);
     write(scfd,&type,sizeof(type));
     write(scfd,&stemp,sizeof(singleu));
  }
  else if(user_type=='J')
  {
    jointu jtemp;
    type = 2;
    write(1,"Enter Username 1\n",sizeof("Enter Username 1\n"));
    scanf(" %[^\n]",jtemp.user_name_a);
    write(1,"Enter Username 2\n",sizeof("Enter Username 2\n"));
    scanf(" %[^\n]",jtemp.user_name_b);
    write(1,"Enter Password\n",sizeof("Enter Password\n"));
    scanf(" %[^\n]",jtemp.password);
    write(scfd,&type,sizeof(type));
    write(scfd,&jtemp,sizeof(jointu));
  }
  read(scfd,&check,sizeof(check));
  if(checkbit)
    {printf("Account Created Successfully\n");}
  admin_choices(scfd);

}


void Modacc(int scfd)
{
  int type;
  int check;
  char user_type;

  write(1,"'S': singleaccount\n 'J': jointaccount\n",sizeof("'S': singleaccount\n 'J': jointaccount\n"));
  read(0,&user_type,sizeof(user_type));
int types;
  if(user_type=='S')
  {
  types=1;
  		write(scfd,&types,sizeof(int));
    singleu stemp;
    printf("Enter the User ID\n");
    scanf("%d",&stemp.user_id);
    printf("Enter Modifications Required\n");
		printf("Enter the username\n");
		scanf(" %[^\n]",stemp.user_name);
		printf("Enter the password\n");
		scanf(" %[^\n]",stemp.password);
		printf("Enter the balance\n");
		scanf("%f",&stemp.balance);
		write(scfd,&stemp,sizeof(singleu));

  }

  else if(user_type=='J')
  {  types=2;
  		write(scfd,&types,sizeof(int));
    jointu jtemp;
    printf("Enter the User ID\n");
    scanf("%d",&jtemp.user_id);
    printf("Enter Modifications Required\n");
    printf("Enter the username1\n");
    scanf(" %[^\n]",jtemp.user_name_a);
    printf("Enter the other username2\n");
    scanf(" %[^\n]",jtemp.user_name_b);
    printf("Enter the password\n");
    scanf(" %[^\n]",jtemp.password);
    printf("Enter the balance\n");
    scanf("%f",&jtemp.balance);
    write(scfd,&jtemp,sizeof(jointu));
  }

  read(scfd,&check,sizeof(check));
	if(check)
		{printf(" Modification Successful\n");}
  else
    {printf("Unable to make modifications to the Account\n");}
	admin_choices(scfd);

}

void delacc(int scfd)
{
  int check;
  char user_type;
  int type;

  write(1,"'S': singleaccount\n 'J': jointaccount\n",sizeof("'S': singleaccount\n 'J': jointaccount\n"));
  read(0,&user_type,sizeof(user_type));
  int userid;
  if(user_type =='S')
  {
    type = 1;
    write(scfd,&type,sizeof(type));
    write(1,"Enter User Id\n",sizeof("Enter User Id\n"));
    scanf("%d",&userid);
    write(scfd,&userid,sizeof(userid));
  }

  else if(user_type=='J')
  {
    type = 2;
    write(scfd,&type,sizeof(type));
    write(1,"Enter User Id\n",sizeof("Enter User Id\n"));
    scanf("%d",&userid);
    write(scfd,&userid,sizeof(userid));
  }

  if(check)
  {
    write(1,"Successfully Deleted The Account\n",sizeof("Successfully Deleted The Account\n"));
  }
  else
  {
    write(1,"Error Deleting The Account\n",sizeof("Error Deleting The Account\n"));
  }
  admin_choices(scfd);


}


void find(int scfd)
{
  int type;
  int check;
  char user_type;
  int userid;
  write(1,"'S': singleaccount\n 'J': jointaccount\n",sizeof("'S': singleaccount\n 'J': jointaccount\n"));
  read(0,&user_type,sizeof(user_type));

  if(user_type=='S'){
  type=1;
    write(scfd,&type,sizeof(type));
    singleu stemp;
    printf("Enter the User ID\n");
    scanf("%d",&userid);
    write(scfd,&userid,sizeof(userid));
    printf("id sent\n");
    read(scfd,&stemp,sizeof(stemp));
    printf("username = %s\n",stemp.user_name);
    printf("account number =%d\n",stemp.account_number);
    printf("Balance = %f\n",stemp.balance);
    }
  else if(user_type=='J'){
  type=2;
    write(scfd,&type,sizeof(type));
    jointu jtemp;
    printf("Enter the User ID\n");
    scanf("%d",&userid);
    write(scfd,&userid,sizeof(userid));
    read(scfd,&jtemp,sizeof(jtemp));
    printf("Username 1  = %s\n",jtemp.user_name_a);
    printf("Username 2 = %s\n",jtemp.user_name_b);
    printf("Account Number =%d\n",jtemp.account_number);
    printf("Balance = %f\n",jtemp.balance);

    }


  admin_choices(scfd);
}



int main()
{
  int scfd = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in server1;

  server1.sin_family = AF_INET;
	server1.sin_addr.s_addr=inet_addr("127.0.0.1");
	server1.sin_port = htons(5555);

  connect(scfd,(struct sockaddr *)&server1,sizeof(server1));

  int type = Intro(scfd);
  if(type==1 || type==2){
    if(checkbit)
       {user_choice(scfd,type);}
    else
       {write(1,"Invalid Credentials\n",sizeof("Invalid Credentials\n"));}
  }
  else if(type==3){
    if(checkbit)
      {admin_choices(scfd);}
    else
      {write(1,"Invalid Credentials\n",sizeof("Invalid Credentials\n"));}
    }

}
