#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

namespace std
{
    template<>
    struct hash<tuple<int, int, int>>
    {
        size_t operator()(tuple<int, int, int> const& t) const
        {
            int res = get<0>(t) + 1001 * get<1>(t) + 1e8 * get<2>(t);

            return hash<int>{}(res);
        }
    };
}


class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {

        return maxProfit_dp(k, prices);
    }

    int maxProfit_memo(int k, vector<int>& prices)
    {
        int n = prices.size();

        unordered_map<tuple<int, int, int>, int> memo;

        function<int(int, int, int)> dfs = [&](int i, int j, int hold) -> int
        {
            if (i < 0 && hold == 0) return 0;
            if (i < 0 && hold == 1) return -1e5;
            if (i < 0 || j < 0) return -1e5;

            auto key = make_tuple(i, j, hold);

            if (memo.find(key) != memo.end()) return memo[key];

            int res = -1e5;

            if (hold == 1)
            {
                res = max(dfs(i-1, j, 1), dfs(i-1, j, 0) - prices[i]);
            }
            else
            {
                res =  max(dfs(i-1, j, 0), dfs(i-1, j-1, 1) + prices[i]);
            }

            memo[key] = res;

            return memo[key];
        };

        return dfs(n-1, k, 0);
    }

    int maxProfit_dp(int k, vector<int>& prices)
    {
        int n = prices.size();

        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(k+2, vector<int>(2, -1e8)));

        for (int j = 1; j <= k+1; ++j)
        {
            dp[0][j][0] = 0;
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 1; j <= k+1; ++j)
            {
                dp[i+1][j][1] = max(dp[i][j][1], dp[i][j][0] - prices[i]);
                dp[i+1][j][0] = max(dp[i][j][0], dp[i][j-1][1] + prices[i]);
            }
        }

        return dp[n][k+1][0];
    }

};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-188.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    //REGISTER(coinChangeMEMO)
    REGISTER(maxProfit_dp)

    exc.run();
}