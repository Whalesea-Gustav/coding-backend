#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    int res;

    int sumNums_memory(int n)
    {
        //only allow to g++ with --pedantic(迂腐的) command flag
        //bool arr[n][n+1];

        //return sizeof(arr) >> 1;
        return 0;
    }

    int sumNums_recur(int n)
    {
        bool x = n > 1 && sumNums(n-1) > 0;

        res += n;

        return res;
    }
    int sumNums(int n) {
        //return sumNums_memory(n);
        return sumNums_recur(n);
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offer-63.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(sumNums)

    exc.run();
}