#include <iostream>
#include "def_header.h"

class A
{
    int a;
    void foo()
    {
       std::cout << "A success!" << std::endl;
    }

    ~A() = default;
};

