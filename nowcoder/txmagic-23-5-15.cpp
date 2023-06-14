//
// Created by whalesea on 2023/5/15.
//

#include <bits/stdc++.h>

using namespace std;

#define DEBUG

#if defined(DEBUG) && defined(MY_SYSTEM)
#define MY_LOG(x) x
#else
#define MY_LOG(x)
#endif

class Solution {
public:

};

int main() {

    int a = 0;

    auto f = [a=a]() -> void
    {
        return;
    };

    function<void()> test = f;

    cout << sizeof(f) << endl;
    cout << sizeof(test) << endl;

}
