#pragma once

template<typename T>
class template_sep_test
{
private:
    T data;
public:

    explicit template_sep_test(T _data) : data(_data) {};

    void print();
};

template class template_sep_test<double>;
template class template_sep_test<int>;


template<typename T>
T template_add(T a, T b);



