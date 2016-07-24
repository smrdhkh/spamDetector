#include<bits/stdc++.h>
using namespace std;

double probSpam( double ps, double pws )
{
   return (ps*pws)/((ps*pws)+(1-ps)*(1-pws));
}

int main()
{
   double ps, pws;
   cin >> ps >> pws;
   double spamProb = probSpam( ps, pws );
   cout << spamProb << endl;
   return 0;
}
