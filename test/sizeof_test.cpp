#include <stdio.h>
#include <iostream>
struct node1
{
    virtual void func1();
    virtual void func2(int);
    void func3();
    char a;
    int b;
};

void node1::func1() {

}

void node1::func2(int) {

}

void node1::func3() {

}


/*
 1、第一个成员的首地址为0.

2、每个成员的首地址是自身大小的整数倍

3、结构体的总大小，为其成员中所含最大类型的整数倍。

 */

//4(4)+8+1(7)=24
struct node2
{
    int a;
    double b;
    char c;
};
//7(1)+8+2(6)+8=32
struct node3
{
    char d[7];
    double a;
    short  b;
    char* c;
};

struct node4
{

};


int main(int argc, char* argv[]) {
    node1 test{};
    test.a = 'a';

    std::cout << sizeof (node1) << std::endl;
    std::cout << sizeof (node2) << std::endl;
    std::cout << sizeof (node3) << std::endl;
    std::cout << sizeof (node4) << std::endl;

}