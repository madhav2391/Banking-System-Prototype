typedef struct singleuser{
unsigned int user_id;
char user_name[20];
char password[20];
int account_number;
float balance;
bool status;
}singleu;

typedef struct jointuser{
  int user_id;
  char account_name[20];
  char user_name_a[20];
  char user_name_b[20];
  char password[20];
  int account_number;
  float balance;
  bool status;
}jointu;

typedef struct adminuser{
  int admin_id;
  char user_name[20];
  char password[20];
}adminu;
