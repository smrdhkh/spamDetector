#include<bits/stdc++.h>
using namespace std;

int main( int argc, char *argv[] )
{
   string name, prob;
   cin >> name >> prob;

   fstream insertWord;
   insertWord.open("blockList", ios::app);
  
   insertWord << "\n" << name << " " << prob;
   return 0;
} 
