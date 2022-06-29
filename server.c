
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

int valids(int cfd,int id,char user_name[20],char password[20],int type){
	int flag=0;
	/*strtok(user_name, "\n");
    strtok(password,"\n");
*/
	if(type==1){
		singleu sst;
  	int fd = open("singleusers.txt",O_RDONLY);
	  perror("open fd");
		lseek(fd,((id-1))*(sizeof(singleu)),SEEK_SET);
		read(fd,&sst,sizeof(singleu));

   strtok(user_name, "\n");
    strtok(password,"\n");
	printf("%d %s %s %d\n",id,user_name,password,type);
			printf(" pass %s,%s\n",sst.password,password);
		printf("user %s,%s\n " ,sst.user_name,user_name);
    if(sst.status==true)

    {
		printf("First if");
		printf("%s,%s\n",sst.password,password);
		printf("%s,%s\n " ,sst.user_name,user_name);
		printf("%d %d \n",strcmp(sst.password,password),strcmp(sst.user_name,user_name));
  		if((strcmp(sst.password,password)==0) && (strcmp(sst.user_name,user_name)==0))
      {
		  printf("second if");
  			printf("ValidUser\n");
  			flag=1;
      }
    	else{
			printf("Invaliduser\n");
			write(cfd,&flag,sizeof(flag));
			close(cfd);
		}
    }
	else{
			printf("Invaliduser\n");
			write(cfd,&flag,sizeof(flag));
			close(cfd);
		}

	  close(fd);
	}

	else if(type==2)
  {
		jointu jst;
		int fd = open("jointusers.txt",O_RDONLY);
		lseek(fd,(id-1)*(sizeof(jointu)),SEEK_SET);
		read(fd,&jst,sizeof(jointu));
   strtok(user_name, "\n");
    strtok(password,"\n");
    if(jst.status==true)
    {
  		if((strcmp(jst.user_name_a,user_name)==0) || (strcmp(jst.user_name_b,user_name)==0))
      {
        if((strcmp(jst.password,password)==0))
        {
          printf("ValidUser\n");
          flag=1;
        }
        
		else{
			printf("Invaliduser\n");
			write(cfd,&flag,sizeof(flag));
			close(cfd);
		}
      }
      	else{
			printf("Invaliduser\n");
			write(cfd,&flag,sizeof(flag));
			close(cfd);
		}
    }
		else{
			printf("Invaliduser\n");
			write(cfd,&flag,sizeof(flag));
			close(cfd);
		}
	  close(fd);
	}

	else if(type==3){
		adminu ast;
		int fd = open("adminusers.txt",O_RDONLY);
		lseek(fd,((id-1))*(sizeof(adminu)),SEEK_SET);
		read(fd,&ast,sizeof(adminu));
  
    strtok(user_name, "\n");
    strtok(password,"\n");


		if((strcmp(ast.password,password)==0) && strcmp(ast.user_name,user_name)==0)
    {
			printf("ValidUser\n");
			flag=1;
    }
		else{
			printf("Invaliduser\n");
			write(cfd,&flag,sizeof(flag));
			close(cfd);
		}
	  close(fd);
	}
		write(cfd,&flag,sizeof(flag));
		return flag;

}

void ser_balenq(int cfd,int id,int type){
	if(type==1)
  {
		singleu sst;
		int fd = open("singleusers.txt",O_RDONLY);
		lseek(fd,(id-1)*(sizeof(singleu)),SEEK_SET);
		read(fd,&sst,sizeof(singleu));

		write(cfd,&sst.balance,sizeof(sst.balance));
	  close(fd);
	}

	else if(type==2)
  {
		jointu jst;
		int fd = open("jointusers.txt",O_RDONLY);
		lseek(fd,(id-1)*(sizeof(jointu)),SEEK_SET);
		read(fd,&jst,sizeof(jointu));

		write(cfd,&jst.balance,sizeof(jst.balance));
	  close(fd);
	}

}


void ser_view(int cfd,int id,int type){
	int flag=0;

	if(type==1){
		singleu sst;
		int fd = open("singleusers.txt",O_RDONLY);
		lseek(fd,(id-1)*(sizeof(singleu)),SEEK_SET);
		read(fd,&sst,sizeof(singleu));
		write(cfd,&sst,sizeof(singleu));
		printf("%s",sst.password);
		flag=1;
		close(fd);
	}
	else if(type==2){
		jointu jst;
		int fd = open("jointusers.txt",O_RDONLY);
		lseek(fd,(id-1)*(sizeof(jointu)),SEEK_SET);
				read(fd,&jst,sizeof(jointu));
		write(cfd,&jst,sizeof(jointu));
		flag=1;
		close(fd);
	}
	// write(cfd,&flag,sizeof(flag));
	return ;
	}


void ser_Deposit(int cfd,int id,int type){
	float s_damt;
  int flag=0;
  int done;
	read(cfd,&s_damt,sizeof(s_damt));
	if(type==1){
		singleu sst;
		int fd = open("singleusers.txt",O_RDWR);

		struct flock lock;
		lock.l_type =F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(id-1)*sizeof(singleu);
		lock.l_len=sizeof(singleu);
		lock.l_pid=getpid();
		int i=fcntl(fd,F_SETLKW,&lock);
		printf("Entered the critical section\n");

		lseek(fd,(id-1)*(sizeof(singleu)),SEEK_SET);
		read(fd,&sst,sizeof(singleu));
		sst.balance=sst.balance+s_damt;

		lseek(fd,-(sizeof(singleu)),SEEK_CUR);
		read(cfd,&done,sizeof(done));
		write(fd,&sst,sizeof(singleu));

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		flag=1;
		close(fd);

		write(cfd,&flag,sizeof(flag));
	}

	else if(type==2){
		jointu jst;
		int fd = open("jointusers.txt",O_RDWR);

		struct flock lock;
		lock.l_type =F_WRLCK; 
		lock.l_whence=SEEK_SET;
		lock.l_start=(id-1)*sizeof(jointu);
		lock.l_len=sizeof(jointu);
		lock.l_pid=getpid();
		int i=fcntl(fd,F_SETLKW,&lock);
		printf("Entered the critical section\n");

		lseek(fd,(id-1)*(sizeof(jointu)),SEEK_SET);
		read(fd,&jst,sizeof(jointu));

		jst.balance=jst.balance+s_damt;

		lseek(fd,-(sizeof(jointu)),SEEK_CUR);
		read(cfd,&done,sizeof(done));
		write(fd,&jst,sizeof(jointu));

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		flag=1;
		close(fd);

		write(cfd,&flag,sizeof(flag));
	}
}


void ser_withdraw(int cfd,int id,int type){
	float s_wamt;
  int flag=0;
	read(cfd,&s_wamt,sizeof(s_wamt));
	if(type==1){
		singleu sst;
		int fd = open("singleusers.txt",O_RDWR);
		lseek(fd,(id-1)*(sizeof(singleu)),SEEK_SET);
		read(fd,&sst,sizeof(singleu));

		if(sst.balance>=s_wamt){
			sst.balance-=s_wamt;

			struct flock lock;
			lock.l_type =F_WRLCK; 
			lock.l_whence=SEEK_SET;
			lock.l_start=(id)*sizeof(singleu);
			lock.l_len=sizeof(singleu);
			lock.l_pid=getpid();
			int i=fcntl(fd,F_SETLKW,&lock);
			printf("Entered the critical section\n");

			lseek(fd,-(sizeof(singleu)),SEEK_CUR);
			write(fd,&sst,sizeof(singleu));

			lock.l_type=F_UNLCK;
			fcntl(fd,F_SETLK,&lock);

			flag=1;
		}

		write(cfd,&flag,sizeof(flag));
	close(fd);
	}
	else if(type==2){
		jointu jst;
		int fd = open("jointusers.txt",O_RDWR);
		lseek(fd,(id-1)*(sizeof(jointu)),SEEK_SET);
		read(fd,&jst,sizeof(jointu));


		if(jst.balance>=s_wamt){
			jst.balance-=s_wamt;

			struct flock lock;
			lock.l_type =F_WRLCK; 
			lock.l_whence=SEEK_SET;
			lock.l_start=(id-1)*sizeof(jointu);
			lock.l_len=sizeof(jointu);
			lock.l_pid=getpid();
			int i=fcntl(fd,F_SETLKW,&lock);
			printf("Entered the critical section\n");

			lseek(fd,-(sizeof(jointu)),SEEK_CUR);
			write(fd,&jst,sizeof(jointu));

			lock.l_type=F_UNLCK;
			fcntl(fd,F_SETLK,&lock);
			flag=1;
		}


		write(cfd,&flag,sizeof(flag));
	close(fd);
	}
		return ;
}


void ser_pwdmod(int cfd,int id,int type){
  	int flag=0;
    char oldpass[20];
    char newpass[20];

  	if(type==1)
    {

	read(cfd,&newpass,sizeof(newpass));	
	printf(" part1 %s",newpass);
	strtok(newpass,"\n");
	printf("part 2 %s",newpass);
	strtok(newpass,"\n");
  	printf("part 3 %s",newpass);
  		singleu sst;
  		int fd = open("singleusers.txt",O_RDWR);
  		lseek(fd,(id-1)*(sizeof(singleu)),SEEK_SET);
  		read(fd,&sst,sizeof(singleu));
			
//			write(1,"first if in pwd",sizeof("first if in pwd"));
  			flag=1;
  			strcpy(sst.password,newpass);
//			write(1,"first if in sss",sizeof("first if in pwd"));

  			struct flock lock;
  			lock.l_type =F_WRLCK; 
  			lock.l_whence=SEEK_SET;
  			lock.l_start=(id-1)*sizeof(singleu);
  			lock.l_len=sizeof(singleu);
  			lock.l_pid=getpid();
  			int i=fcntl(fd,F_SETLKW,&lock);
  //			perror("fcntl");
  			printf("Entered the critical section\n");

  			lseek(fd,-(sizeof(singleu)),SEEK_CUR);
  			write(fd,&sst,sizeof(singleu));

  			lock.l_type=F_UNLCK;
  			fcntl(fd,F_SETLK,&lock);
  		//	        lseek(fd, 0, SEEK_SET);
			//perror("\n fcntl2");
			printf("%s",sst.password);
  			flag=1;
  			printf("%d",flag);
      			write(cfd,&flag,sizeof(flag));
      			perror("write");

  	close(fd);
  	perror("clsoe");
  	}


  	else if(type==2){
	read(cfd,&newpass,sizeof(newpass));
	printf(" part1 %s",newpass);
	strtok(newpass,"\n");
	printf("part 2 %s",newpass);
	strtok(newpass,"\n");
  	printf("part 3 %s",newpass);
  		
  		jointu jst; 
  		int fdj = open("jointusers.txt",O_RDWR);
  		  		perror("\n open");
  		lseek(fdj,(id-1)*(sizeof(jointu)),SEEK_SET);
  		read(fdj,&jst,sizeof(jointu));
  		  		perror("\n read");
  			flag=1;
  			strcpy(jst.password,newpass);
			
			struct flock lock;
  			lock.l_type =F_WRLCK; 
  			lock.l_whence=SEEK_SET;
  			lock.l_start=(id-1)*sizeof(jointu);
  			lock.l_len=sizeof(jointu);
  			lock.l_pid=getpid();
  			int i=fcntl(fdj,F_SETLKW,&lock);
  			printf("Entered the critical section\n");

  			lseek(fdj,-(sizeof(jointu)),SEEK_CUR);
  			write(fdj,&jst,sizeof(jointu));
  	//	perror("\n write");
  			lock.l_type=F_UNLCK;
  			fcntl(fdj,F_SETLK,&lock);
//  		perror("\n fcntl2");
			printf("%s",jst.password);
  			flag=1;
  			printf("%d",flag);
      			write(cfd,&flag,sizeof(flag));
      			//perror("write");

  	close(fdj);
  	}
  	else if(type==3){
  	
	read(cfd,&newpass,sizeof(newpass));	
	printf(" part1 %s",newpass);
	strtok(newpass,"\n");
	printf("part 2 %s",newpass);
	strtok(newpass,"\n");
  	printf("part 3 %s",newpass);
  		adminu ast;
  		int fd = open("adminusers.txt",O_WRONLY);
  		lseek(fd,(id-1)*(sizeof(adminu)),SEEK_SET);
  		read(fd,&ast,sizeof(adminu));

      
        flag=1;
        
  			read(cfd,&newpass,sizeof(newpass));
  			strcpy(ast.password,newpass);

  			struct flock lock;
  			lock.l_type =F_WRLCK; 
  			lock.l_whence=SEEK_SET;
  			lock.l_start=(id-1)*sizeof(adminu);
  			lock.l_len=sizeof(adminu);
  			lock.l_pid=getpid();
  			fcntl(fd,F_SETLKW,&lock);
  			printf("Entered the critical section\n");

  			lseek(fd,-(sizeof(adminu)),SEEK_CUR);
  			write(fd,&ast,sizeof(adminu));

  			lock.l_type=F_UNLCK;
  			fcntl(fd,F_SETLK,&lock);

			printf("%s",ast.password);
  			flag=1;
  			printf("%d",flag);
      			write(cfd,&flag,sizeof(flag));

  	close(fd);
  	}
  		return;
  }


void terminate(int cfd)
{
  		close(cfd);
  		exit(0);
}

void ser_addacc(int cfd){
	int type;
  int flag=0;
	read(cfd,&type,sizeof(type));

	if(type==1){
		singleu s1,s2;
		read(cfd,&s2,sizeof(singleu));
		int fd = open("singleusers.txt",O_RDWR);
		lseek(fd,-(sizeof(singleu)),SEEK_END);
		read(fd,&s1,sizeof(singleu));
		s2.user_id=s1.user_id+1;
		s2.account_number=s1.account_number+1;
		s2.balance=0;
		s2.status=true;
printf(" uid:%d \n",s2.user_id);
int tx=s2.user_id;

		struct flock lock;
		lock.l_type =F_WRLCK;
		lock.l_whence=SEEK_END;
		lock.l_start=-sizeof(singleu);
		lock.l_len=sizeof(singleu);
		lock.l_pid=getpid();
		fcntl(fd,F_SETLKW,&lock);
		printf("Entered the critical section\n");

		write(fd,&s2,sizeof(singleu));
perror("write");
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
write(cfd,&tx,sizeof(int));
		flag=1;
		close(fd);
	}

	else if(type==2){
		jointu j1,j2;
    read(cfd,&j2,sizeof(jointu));
		int fd = open("jointusers.txt",O_RDWR);
		lseek(fd,-(sizeof(jointu)),SEEK_END);
		read(fd,&j1,sizeof(jointu));
		j2.user_id=j1.user_id+1;
		j2.account_number=j1.account_number+1;
		j2.balance=0;
		j2.status=true;
printf("jid:%d\n",j2.user_id);
int tx=j2.user_id;
		struct flock lock;
		lock.l_type =F_WRLCK; 
		lock.l_whence=SEEK_END;
		lock.l_start=-sizeof(jointu);
		lock.l_len=sizeof(jointu);
		lock.l_pid=getpid();
		fcntl(fd,F_SETLKW,&lock);
		printf("Entered the critical section\n");

		write(fd,&j2,sizeof(jointu));

		lock.l_type=F_UNLCK;
	  fcntl(fd,F_SETLK,&lock);
	  	  write(cfd,&tx,sizeof(int));
		flag=1;
		close(fd);
	}
	write(cfd,&flag,sizeof(flag));
	return ;
}

void ser_delacc(int cfd){
	int type;
  int flag=0;
  int user_id;
	read(cfd,&type,sizeof(type));
//write(1,"entered func\n",sizeof("entered func\n"));
	if(type==1){
//	write(1,"entered ones\n",sizeof("entered func\n"));
		singleu sst;
		read(cfd,&user_id,sizeof(user_id));
		int fd = open("singleusers.txt",O_RDWR);
//		perror("open\n");
		lseek(fd,(user_id-1)*(sizeof(singleu)),SEEK_SET);
//		perror("lessk\n");
		read(fd,&sst,sizeof(singleu));
//		perror("read\n");
		printf("uid: %d\n, umane: %s\n, upass:%s\n, ubal: %f\n, staus:%d\n ",sst.user_id,sst.user_name,sst.password,sst.balance,sst.status);
		if(sst.status==true){
			sst.status=false;
printf("true changing to false");
			struct flock lock;
			lock.l_type =F_WRLCK; 
			lock.l_whence=SEEK_SET;
			lock.l_start=(user_id-1)*sizeof(singleu);
			lock.l_len=sizeof(singleu);
			lock.l_pid=getpid();
			fcntl(fd,F_SETLKW,&lock);
			printf("Entered the critical section\n");

			lseek(fd,-(sizeof(singleu)),SEEK_CUR);
			write(fd,&sst,sizeof(singleu));

			lock.l_type=F_UNLCK;
			fcntl(fd,F_SETLK,&lock);
printf("sucessful delte");
			flag=1;
    }

		close(fd);
	}
	else if(type==2){
		jointu jst;
		read(cfd,&user_id,sizeof(user_id));
		int fd = open("jointusers.txt",O_RDWR);
		lseek(fd,(user_id-1)*(sizeof(jointu)),SEEK_SET);
		read(fd,&jst,sizeof(jointu));
		if(jst.status==true){
			jst.status=false;
			struct flock lock;
			lock.l_type =F_WRLCK;
			lock.l_whence=SEEK_SET;
			lock.l_start=(user_id-1)*sizeof(jointu);
			lock.l_len=sizeof(jointu);
			lock.l_pid=getpid();
			fcntl(fd,F_SETLKW,&lock);
			printf("Entered the critical section\n");

			lseek(fd,-(sizeof(jointu)),SEEK_CUR);
			write(fd,&jst,sizeof(jointu));

			lock.l_type=F_UNLCK;
			fcntl(fd,F_SETLK,&lock);


			flag=1;}

		close(fd);
	}
	write(cfd,&flag,sizeof(flag));
	return;
}

void ser_modacc(int cfd){
	int type;
  int flag=0;
	read(cfd,&type,sizeof(type));
//printf("type %d\n",type);
	if(type==1){
		singleu s1,s2;
		read(cfd,&s2,sizeof(singleu));
		int fd = open("singleusers.txt",O_RDWR);
//		perror("open\n");
		lseek(fd,(s2.user_id-1)*(sizeof(singleu)),SEEK_SET);
//		perror("lesk\n");
		read(fd,&s1,sizeof(singleu));
//		perror("read\n");
		strcpy(s1.user_name,s2.user_name);
		strcpy(s1.password,s2.password);
		s1.account_number=s2.account_number;
		s1.balance=s2.balance;

		struct flock lock;
		lock.l_type =F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(s2.user_id-1)*sizeof(singleu);
		lock.l_len=sizeof(singleu);
		lock.l_pid=getpid();
		fcntl(fd,F_SETLKW,&lock);
//		perror("fcntl\n");
		printf("Entered the critical section\n");

		lseek(fd,-(sizeof(singleu)),SEEK_CUR);
//		perror("lsek\n");
		write(fd,&s1,sizeof(singleu));
//perror("write\n");
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		//perror("unloack\n");

		flag=1;
		close(fd);
	}

	else if(type==2){
		jointu j1,j2;
		int fd = open("jointusers.txt",O_RDWR);
		read(cfd,&j2,sizeof(j2));
		lseek(fd,(j2.user_id-1)*(sizeof(jointu)),SEEK_SET);
		read(fd,&j1,sizeof(jointu));
		strcpy(j1.user_name_a,j2.user_name_a);
		strcpy(j1.user_name_b,j2.user_name_b);
		strcpy(j1.password,j2.password);
		j1.account_number=j2.account_number;
		j1.balance=j2.balance;


		struct flock lock;
		lock.l_type =F_WRLCK; 
		lock.l_whence=SEEK_SET;
		lock.l_start=(j2.user_id-1)*sizeof(jointu);
		lock.l_len=sizeof(jointu);
		lock.l_pid=getpid();
		fcntl(fd,F_SETLKW,&lock);
		printf("Entered the critical section\n");

		lseek(fd,-(sizeof(jointu)),SEEK_CUR);
		write(fd,&j1,sizeof(jointu));

		lock.l_type=F_UNLCK;
		int jx=fcntl(fd,F_SETLK,&lock);
		flag=1;
		close(fd);
	}
	write(cfd,&flag,sizeof(flag));
	return ;
	}

void ser_find(int cfd){
	int type;
  int flag=0;
  int user_id;
	read(cfd,&type,sizeof(type));
	printf("%d",type);
	if(type==1){
		singleu sst;
		read(cfd,&user_id,sizeof(user_id));
		int fd = open("singleusers.txt",O_RDONLY);
		lseek(fd,(user_id-1)*(sizeof(singleu)),SEEK_SET);
		read(fd,&sst,sizeof(singleu));
		printf("uid: %d\n, umane: %s\n, upass:%s\n, ubal: %f\n, staus:%d\n ",sst.user_id,sst.user_name,sst.password,sst.balance,sst.status);
		
		write(cfd,&sst,sizeof(singleu));
		flag=1;
		close(fd);
	}
	else if(type==2){
		jointu jst;
		read(cfd,&user_id,sizeof(user_id));
		int fd = open("jointusers.txt",O_RDONLY);
		lseek(fd,(user_id-1)*(sizeof(jointu)),SEEK_SET);
				read(fd,&jst,sizeof(singleu));
		write(cfd,&jst,sizeof(jointu));
		flag=1;
		close(fd);
	}
	write(cfd,&flag,sizeof(flag));
	return ;
	}


int main()
{
int sd = socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in server1,client;

server1.sin_family = AF_INET;
server1.sin_addr.s_addr = INADDR_ANY;
server1.sin_port = htons(5555);
bind(sd,(struct sockaddr*)&server1,sizeof(server1));

listen(sd,5);
write(1,"Server Ready\n",sizeof("Server Ready\n"));



while(1)
{
    int client_len = sizeof(client);
    int cfd=accept(sd,(struct sockaddr *)&client,&(client_len));
    if(!fork()){
    int type;
    int id;
    char user_name[20];
    char password[20];
    int log;
    write(1,"Login req acknowled\n",sizeof("Login req acknowled\n"));
    read(cfd,&type,sizeof(type));

    while(1)
    {
         if(type==1)
         {
            singleu stemp;
            read(cfd,&id,sizeof(stemp.user_id));
            read(cfd,&user_name,sizeof(stemp.user_name));
       		 	read(cfd,&password,sizeof(stemp.password));
       			log=valids(cfd,id,user_name,password,type);
       			break;
         }

         else if(type==2)
         {
           jointu jtemp;
           read(cfd,&id,sizeof(jtemp.user_id));
           read(cfd,&user_name,sizeof(jtemp.account_name));
           read(cfd,&password,sizeof(jtemp.password));
           log=valids(cfd,id,user_name,password,type);
           break;
         }

         else if(type==3)
         {
           adminu atemp;
           read(cfd,&id,sizeof(atemp.admin_id));
           read(cfd,&user_name,sizeof(atemp.user_name));
           read(cfd,&password,sizeof(atemp.password));
           log=valids(cfd,id,user_name,password,type);
           break;
         }
    }

    while(1)
    {
        if(type==1 || type==2)
        {
              int usel;
              read(cfd,&usel,sizeof(usel));
              if(usel==1)
			  {ser_view(cfd,id,type);}
                
              else if(usel==2)
			  {ser_balenq(cfd,id,type);}
                
              else if(usel==3)
              {ser_Deposit(cfd,id,type);}
              else if(usel==4)
			  {ser_withdraw(cfd,id,type);}
              else if(usel==5)
			  {ser_pwdmod(cfd,id,type);}

              else if(usel==6)
                {terminate(cfd);}
       }
       else if(type==3)
       {
          int asel;
          read(cfd,&asel,sizeof(asel));
          if(asel==1)
            {ser_addacc(cfd);}
          else if(asel==2)
            {ser_delacc(cfd);}
          else if(asel==3)
            {ser_modacc(cfd);}
          else if(asel==4)
            {ser_find(cfd);}
          else if(asel==5)
            {ser_pwdmod(cfd,id,type);}
          else if(asel==6)
            {terminate(cfd);}
      }
    }
}

	else close(cfd);
}

}
