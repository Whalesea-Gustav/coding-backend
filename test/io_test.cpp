#include <bits/stdc++.h>

using namespace std;

struct student
{
    int id;
    int score;
    char n;
    void show() {};
};

student s1{100, 97, 'A'};
student s2{1002, 90, 'B'};


int main()
{
   ofstream f1("text.dat", ios::binary);
   f1 << s1.id << " " << s1.score << " " << s1.n;
   f1.seekp(0, ios::beg);
   f1 << s2.id << " " << s2.score << " " << s2.n;
   f1.close();
   return 0;
}