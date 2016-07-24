#include<stdio.h>
#include<string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<bits/stdc++.h>
using namespace std;

struct SpamWord
{
   struct SpamWord* word[26];
   double prob;
};

struct SpamWord* root;
struct SpamWord* createNode()
{
   struct SpamWord* temp;
   temp = (struct SpamWord*) malloc( sizeof ( SpamWord ) );
   for ( int i = 0; i < 26; i++ )
   {
      temp->word[i] = NULL;
   }
   temp->prob = 0.0;
   return temp;
}

void addWord( string spam, double prob )
{
   struct SpamWord* ad = root;
   double probCummulative = 0.0;
   for ( int i = 0; i < spam.length(); i++ )
   {
      ad->word[spam[i]-'a'] = createNode();
      ad = ad->word[spam[i]-'a'];
      ad->prob = (prob+(ad->prob)+probCummulative)/3.0;
      probCummulative = ad->prob;
   }
}

bool testSpam( string line )
{
   bool found = true;
   struct SpamWord* srch = root;
   for ( int i = 0; i < line.length(); i++ )
   {
      if ( srch->word[line[i]-'a'] == NULL )
      {
          found = false;
          break;
      }
      srch = srch->word[line[i]-'a'];
   }
   return found;
}

double getProbability( string wrd )
{
   double prob = 0.0;  
   struct SpamWord* srch = root;
   for ( int i = 0; i < wrd.length(); i++ )
   {
      srch = srch->word[wrd[i]-'a'];
      prob = (prob+(srch->prob))/2.0;
   }
   return prob;
}

int main( int argc, char *argv[] )
{ 
   cout << "wrng" << endl;
   int size = atoi(argv[2]);
   string str[size+1];
   int len = atoi(argv[3]);
   int prev = 0, cnt1 = 0;

   cout << argv[1] << endl;
   istringstream iss( argv[1] );
   string token;

   while( getline(iss, token,' ') )
   {
      cout << token << endl;
      str[cnt1++] = token;
   }
   cout << "l:" << endl;
   fstream insertWord;
   root = createNode();
   
   insertWord.open("blockList");
   while ( !insertWord.eof() )
   {
      string wrongWord;
      double prob;
      insertWord >> wrongWord >> prob;
      addWord( wrongWord, prob );
   }    

   int cnt = 0;
   double spamProb = 0.0;
   for ( int i = 0; i <= size-1; i++ )
   {
      if ( testSpam( str[i] ) )
      {
         cout << "b: " << str[i] << endl;
         cnt++;
         spamProb += getProbability( str[i] );
      }
   }
   spamProb = spamProb/cnt;
   cout << spamProb << endl;
   int welcomeSocket, newSocket;
   char buffer[1024];
   struct sockaddr_in serverAddr;
   struct sockaddr_storage serverStorage;
   socklen_t addr_size;

   welcomeSocket = socket( PF_INET, SOCK_STREAM, 0 );

   serverAddr.sin_family = AF_INET;
   serverAddr.sin_port = htons(7891);
   serverAddr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
   memset( serverAddr.sin_zero, '\0', sizeof( serverAddr.sin_zero ) );

   bind( welcomeSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr) );

   if ( listen(welcomeSocket,5)!=0 ) {
      cout << "Error" << endl;
   }
   else
   {
      addr_size = sizeof ( serverStorage );
      newSocket = accept( welcomeSocket, ( struct sockaddr* )&serverStorage, &addr_size );
   }

   char sendString[100001];
   sprintf( sendString, "%lf", spamProb );
   send( newSocket, sendString, sizeof(sendString), 0 );     
   return 0;
}
