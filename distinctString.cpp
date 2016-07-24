#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;

struct msgbuf1
{
   long mtype;
   char mtext[100001];
};

void distinctStr( string str )
{
   cout << "func" << endl;
   int cnt = 0, count = 0;
   map<string,int> m;
   for ( int i = 0; i < str.length(); i++ )
   {
      for ( int sz = 0; (sz+i) < str.length(); sz++ )
      {
         m[str.substr(i,i+sz)] = 1;
      }
      m[string(1,str[i])] = 1;
   }
   char str1[100001], str2[100001], str3[100001];
   string passArg;
   map<string, int>::iterator ii;
   for (ii = m.begin(); ii!=m.end(); ++ii) {
      passArg += ( (*ii).first + " " );
      count++;
      for ( int i = 0; i < (*ii).first.length(); i++ )
      {
         str1[cnt] = (*ii).first[i];
         cnt++;
      }
      str1[cnt++] = ' ';
   }
   str1[cnt] = '\0';
   
   sprintf( str2, "%d", count );
   sprintf( str3, "%d", cnt );
   cout << "b" << endl;
   execlp( "/home/samridhi/spamProjct/wrongWord", "wrongWord", str1, str2, str3, NULL );
}

int main()
{
   cout << "distinct" << endl;
   string str;
   int msgqid;
   key_t key;
   struct msgbuf1 rbuf;

   key = 1234;
   if ( msgqid = msgget( key, 0666 ) < 0 )
   {
      exit(1);
   }
   if ( msgrcv( msgqid, &rbuf, 100001, 1, 0 ) < 0 )
   {
      exit(1);
   }
   //cout << rbuf.mtext << endl;
   for ( int i = 0; rbuf.mtext[i] != '.'; i++ )
      str += rbuf.mtext[i];
   cout << str << endl;
//   cin >> str;
   distinctStr( str );
   return 0;
}
