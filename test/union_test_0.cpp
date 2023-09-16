#include <bits/stdc++.h>

using namespace std;

union {
    int i;
    char x[4];
} a;

int main()
{
   a.x[0] = 10;
   a.x[1] = 1;

   cout << a.i << endl;
   return 0;
}