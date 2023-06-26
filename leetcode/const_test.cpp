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
    std::cout << "Hello, World!" << std::endl;

    const uint32_t in = 10;

    const_test1<in>();

    return 0;
}
