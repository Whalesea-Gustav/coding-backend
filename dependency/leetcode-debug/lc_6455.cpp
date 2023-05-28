#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long minimumCost(string s) {
        int n = s.size();

        vector<int> dp(n, 0);

        for (int j = n - 2; j >= 0; --j)
        {
            if(s[j] == s[j+1])
            {
                dp[j] = dp[j+1];
            }
            else
            {
                dp[j] = dp[j+1] + n - j - 1;
            }
        }


        vector<int> dp2(n, 0);

        for (int j = 1; j < n; ++j)
        {
            if(s[j] == s[j-1])
            {
                dp2[j] = dp2[j-1];
            }
            else
            {
                dp2[j] = dp2[j-1] + j;
            }
        }


        int min_cost = numeric_limits<int>::max();

        for (int i = 0; i < n; ++i)
        {
            min_cost = min(dp[i] + dp2[i], min_cost);
        }

        return min_cost;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-6455.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(minimumCost)

    exc.run();
}