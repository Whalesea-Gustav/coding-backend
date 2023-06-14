#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int numTimesAllBlue(vector<int>& flips) {
        return numTimesAllBlue_reverse(flips);
    }

    //更容易思考
    int numTimesAllBlue_reverse(vector<int>& flips)
    {
        int n = flips.size();

        if(n == 0) return 0;

        int min_val = flips[n-1] - 2;

        int count=  1;

        for (int i = n-2; i >= 0; --i)
        {
            if(min_val >= i) count++;

            min_val = min(min_val, flips[i] - 2);
        }

        return count;
    }

    //很难想到
    int numTimesAllBlue_transverse(vector<int> &flips) {
        int ans = 0, mx = 0, n = flips.size();
        for (int i = 0; i < n; i++) {
            mx = max(mx, flips[i]);
            ans += mx == i + 1;
        }
        return ans;
    }

    //求和的思路
    int numTimesAllBlue_sum(vector<int> &flips)
    {
        int sum = 0;
        int n = flips.size();
        int count = 0;
        for (int i = 1; i <= n; ++i)
        {
            sum += flips[i-1];

            if(sum == i * (i+1) / 2)
            {
                count++;
            }
        }

        return count;
    }

};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-1375.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(numTimesAllBlue)

    exc.run();
}