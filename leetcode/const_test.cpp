#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;

#define DEBUG

#if defined(DEBUG) && defined(GJY_SYSTEM)
#define MY_LOG(x) x
#else
#define MY_LOG(x)
#endif

template<uint32_t IN>
void const_test1()
{
    cout << IN << endl;
}

int main() {

    uint32_t i;
    cin >> i;
    const uint32_t j = i;
    uint32_t k = 10;
    const uint32_t in = 10;

    const_test1<in>();

    const_test1<j>();

    const_test1<k>();

    return 0;
}
