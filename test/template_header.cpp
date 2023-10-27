#include "template_header.h"
#include <iostream>

using namespace std;

template<typename T>
void template_sep_test<T>::print() {
    cout << typeid(data).raw_name() << endl;
    cout << data << endl;
}


