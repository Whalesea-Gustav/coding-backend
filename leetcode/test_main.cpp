#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;

#define DEBUG

#if defined(DEBUG) && defined(GJY_SYSTEM)
#define MY_LOG(x) x
#else
#define MY_LOG(x)
#endif

int main() {
    std::cout << "Hello, World!" << std::endl;

    MY_LOG(fmt::print("234"));

    return 0;
}
