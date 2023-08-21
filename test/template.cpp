#include <bits/stdc++.h>

using namespace std;

template<class S, decltype(S::fromStdString(std::string()), std::declval<S>().toStdString(), 0)=0>
        S t(S s)
        {
                return S();
        };

int main()
{
    double d1 = 1e9;
    double d2 = 10e9;

    cout << d1 << endl;
    cout << d2 << endl;

    return 0;
}