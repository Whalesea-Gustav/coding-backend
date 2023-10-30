#include "template_header.h"
#include <iostream>

using namespace std;

template<typename T>
void template_sep_test<T>::print() {
    cout << typeid(data).raw_name() << endl;
    cout << data << endl;
}


template<typename T>
T template_add(T a, T b)
{
    return a + b;
}

template float template_add<float>(float a, float b);
template int template_add<int>(int a, int b);