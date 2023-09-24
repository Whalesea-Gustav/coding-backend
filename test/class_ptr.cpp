#include <bits/stdc++.h>

using namespace std;

class A
{
public:
    string a;
    void f1()
    {
        printf("Hello World");
    }

    void f2()
    {
        a = "Hello World";
        printf("%s", a.c_str());
    }

    virtual void f3()
    {
        printf("Hello World");
    }

    virtual void f4()
    {
        a = "Hello World";
        printf("%s", a.c_str());
    }

};

int main()
{
   A* aptr = NULL;
   aptr->f1();
   return 0;
}