#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<bits/stdc++.h>
using namespace std;

struct msgbuf1
{
   long mtype;
   char mtext[100001];
};

struct suffix
{
   int index;
   string suff;
};

bool cmp(struct suffix a, struct suffix b)
{
    if ( a.suff[0] <= '9' && a.suff[0] >= '0' )
       return false;
    if ( b.suff[0] <= '9' && b.suff[0] >= '0' )
        return true;    
    return a.suff[0] < b.suff[0];
}

int* buildSuffixArray( string txt )
{
   struct suffix suffixes[txt.length()+1];   
   for ( int i = 0; i < txt.length(); i++ )
   {
      suffixes[i].index = i;
      suffixes[i].suff = txt.substr( i, i+txt.length() );
   }

   sort(suffixes, suffixes+txt.length(), cmp);
   int *suffArr = new int[txt.length()+1];
   for ( int i = 0; i < txt.length(); i++ )
   {
      suffArr[i] = suffixes[i].index;
   }
   return suffArr;
}

int main()
{
   string firstname, lastname, email;
   fstream smtpHeader;
   smtpHeader.open("smtpHeader");
   string str;
   while ( getline( smtpHeader, str ) )
   {
      istringstream iss(str);
      string token;
      while( getline(iss, token,' ') )
      {
         if ( token=="From:" )
         {
            string name;
            while( getline(iss, token,' ') )
            {
               name+=(token+" ");
               if ( token[token.length()-2] == '>' )
               {
                  break;
               }
            }
            istringstream js(name);

            getline(js, token,' ');
            firstname = token.substr( 1, token.length() );
            //cout << firstname << endl;

            getline(js, token,'<');
            lastname=token.substr(0,token.length()-1);
            //cout << lastname << endl;

            getline(js, email,'>');
           // cout << email << endl;
         }
          // send arg by msgqueue 
      }
   }

   int *pos = buildSuffixArray(email); 
  /* for ( int i = 0; i < email.length(); i++ )
       cout << pos[i] << " ";
   cout << endl;*/
   string passArg;
   passArg += (firstname+lastname+email.substr(0,pos[1])+email.substr(pos[0]+1,email.length())+"." );

   char passChar[100001]; 
   for ( int i = 0; i < passArg.length(); i++ )
      passChar[i] = passArg[i];   

   passChar[passArg.length()] = '\0';

   int msgqid;
   int msgflg = IPC_CREAT | 0666;
   key_t key;
 
   struct msgbuf1 sbuf;
   int buf_length;
   key = 1234;     
   if ( msgqid = msgget( key, msgflg ) < 0 )
   {
      exit(1);
   }
   sbuf.mtype = 1;
   strcpy( sbuf.mtext, passChar );
   buf_length = strlen( sbuf.mtext )+1;

   if ( msgsnd( msgqid, &sbuf, buf_length, IPC_NOWAIT ) < 0 )
   {
      exit(1);
   }
   else
   {
 //     cout << "Message sent: " << sbuf.mtext << endl;
   }
   cout << "hey" << endl;
   execlp("/home/samridhi/spamProjct/distinctString","distinctString",NULL); 
   return 0;
}
