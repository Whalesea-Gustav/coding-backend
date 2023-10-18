#include <stdio.h>
#include <iostream>
struct node
{
    virtual void func1();
    virtual void func2(int);
    void func3();
    char a;
    int b;
};

void node::func1() {

}

void node::func2(int) {

}

void node::func3() {

}

int main(int argc, char* argv[]) {
    node test{};
    test.a = 'a';

    std::cout << sizeof (node) << std::endl;
}