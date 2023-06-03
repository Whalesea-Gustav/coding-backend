#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minLength(string s) {
        size_t sz = 200;

        string test = "";

        delete_op(s, sz);

        return sz;
    }

    void delete_op(string s, size_t& sz)
    {
        for (int i = 0; i < static_cast<int>(s.size()) - 1; ++i)
        {
            if(s[i] == 'A' && s[i+1] == 'B')
            {
                s = s.substr(0, i) + s.substr(i+2);
                delete_op(s, sz);
            }
            else if (s[i] == 'C' && s[i+1] == 'D')
            {
                s = s.substr(0, i) + s.substr(i+2);
                delete_op(s, sz);
            }
        }

        sz = min(sz, s.size());
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-6439.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(minLength)

    exc.run();
}