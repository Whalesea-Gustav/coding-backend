#include "template_header.h"

#include <iostream>

using namespace std;

int main()
{
    cout << "test start:" << endl;

    template_sep_test<double> t1(0.1);
    template_sep_test<int> t2(100);


    t1.print();
    t2.print();

    //template_sep_test<float> t3(100);
    //t3.print();

    cout << template_add<float>(0.1f, 0.2f) << endl;
    cout << template_add<int>(0, 1) << endl;
    //cout << template_add<double>(0.1, 1.2) << endl;

    return 0;
}