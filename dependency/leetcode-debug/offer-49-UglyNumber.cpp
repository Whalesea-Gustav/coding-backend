#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

namespace std
{
    template<>
    struct hash<pair<int, int>>
    {
        size_t operator()(pair<int, int> const & t) const
        {
            size_t h1 = hash<int>()(t.first);
            size_t h2 = hash<int>{}(t.second);
            return h1 ^ (h2 << 1);
        }
    };
}

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n);

        int i = 0, j = 0, k = 0;

        dp[0] = 1;

        for (int l = 1; l < n; ++l)
        {
            int res = min(dp[i] * 2, min(dp[j] * 3, dp[k] * 5));

            dp[l] = res;

            //去重
            if(res == dp[i]*2) ++i;
            if(res == dp[j]*3) ++j;
            if(res == dp[k]*5) ++k;
        }

        return dp[n-1];
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offer-49.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(nthUglyNumber)

    exc.run();
}