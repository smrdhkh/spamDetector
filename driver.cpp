#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;

void print_error(char *message){
	fprintf(stderr, "%s\n",message);
	exit(EXIT_FAILURE);
}

void* email( void *pt )
{
   int *x = (int*)pt;
   execlp("/home/samridhi/spamProjct/insertWord","insertWord",NULL);
   pthread_exit(NULL);
}

void* smtp( void *pt )
{
   int *x = (int*)pt;
   execlp("/home/samridhi/spamProjct/smtpEval","smtpEval",NULL);
   pthread_exit(NULL);
}


int main()
{
   int x = 0;

   cout << "Enter 1 to see the probablity of smtp header\nEnter 2 for entering spam word and its probabilty\n";
   cin >> x;

   pthread_t tid;
   
   if ( x == 2 )
      if(pthread_create( &tid, NULL, email, &x ))
        cout << "Error creating thread" << endl;
   else
      if(pthread_create( &tid, NULL, smtp, &x ))
         cout << "Error creating thread" << endl;   
  
   if(pthread_join(tid,NULL))
      cout << "Error joining thread" << endl;
   return 0;
}
