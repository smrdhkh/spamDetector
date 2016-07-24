#include <sys/types.h>
#include<stdio.h>
#include<string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<bits/stdc++.h>
using namespace std;

int main()
{
   int clientSocket;
   char buffer[1024];

   struct sockaddr_in serverAddr;
   socklen_t addr_size;

   clientSocket = socket( PF_INET, SOCK_STREAM, 0 );
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_port = htons(7891);
   serverAddr.sin_addr.s_addr = inet_addr( "127.0.01" );
   memset( serverAddr.sin_zero, '\0', sizeof ( serverAddr.sin_zero ) );

   addr_size = sizeof( serverAddr );

   connect( clientSocket, ( struct sockaddr* )&serverAddr, addr_size );

   recv( clientSocket, buffer, 1024, 0 );
   cout << buffer << endl;
   return 0;
}