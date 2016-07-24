#include<bits/stdc++.h>
using namespace std;

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
   // 0 is '.' and 1 is '@' 
   string suffixArr;
   cin >> suffixArr;

   int *pos = buildSuffixArray(suffixArr); 
   for ( int i = 0; i < suffixArr.length(); i++ )
      cout << pos[i] << " ";
   cout << endl;  
   return 0;
}
