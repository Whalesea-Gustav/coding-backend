#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    //有冷冻期

    int maxProfit(vector<int>& prices) {
        return maxProfit_memo(prices);
    }

    int maxProfit_memo(vector<int>& prices)
    {
        int n = prices.size();

        unordered_map<int, int> memo;

        function<int(int,int)> dfs = [&](int d, int hold) -> int
        {
            int key = d + 1e5 * hold;

            if (memo.count(key) > 0) return memo[key];

            if (d < 0 && hold == 1)
            {
                return -1e5;
            }
            else if (d < 0 && hold == 0)
            {
                return 0;
            }

            if (hold == 1)
            {
                memo[key] = max(dfs(d-1, 1), dfs(d-2, 0) - prices[d]);

            }
            else
            {
                memo[key] = max(dfs(d-1, 0), dfs(d-1, 1) + prices[d]);
            }

            return memo[key];
        };

        return dfs(n-1, 0);
    }

    int maxProfit_dp_optimization(vector<int>& prices)
    {
        int hold0 = 0;
        int hold1 = -1e5;
        int prev_hold0 = 0;

        int n = prices.size();

        for (int i = 0; i < n; ++i)
        {
            int new_hold0 = max(hold0, hold1 + prices[i]);
            hold1 = max(hold1, prev_hold0 - prices[i]);
            prev_hold0 = hold0;
            hold0 = new_hold0;
        }

        return hold0;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-309.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    //REGISTER(coinChangeMEMO)
    REGISTER(maxProfile_dp_space_optimization)

    exc.run();
}