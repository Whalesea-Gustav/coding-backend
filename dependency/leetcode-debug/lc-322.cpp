#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;



namespace std
{
    template<>
    struct hash<pair<int, int>>
    {
        std::size_t operator()(pair<int, int> const& s) const noexcept
        {
            std::size_t h1 = std::hash<int>{}(s.first);
            std::size_t h2 = std::hash<int>{}(s.second);
            return h1 ^ (h2 << 1); // or use boost::hash_combine
        }
    };
}

class Solution {
public:
    using LL = long long;

    int coinChangeMEMO(vector<int>& coins, int amount) {

        int n = coins.size();

        unordered_map<pair<int, int>, int> count_hash;


        function<int (int, int)> dfs = [&](int i, int c) -> int
        {
            if (i < 0)
            {
                if (c == 0)
                {
                    return 0;
                }
                else
                {
                    return numeric_limits<int>::max();
                }
            }

            if (c < coins[i])
            {
                return dfs(i-1, c);
            }

            auto search_key = make_pair(i, c);
            if (count_hash.find(search_key) != count_hash.end())
            {
                return count_hash[search_key];
            }

            int choice0 = dfs(i-1, c);

            int choice1 = dfs(i, c-coins[i]);

            if (choice1 < numeric_limits<int>::max())
            {
                ++choice1;
            }

            count_hash[search_key] = min(choice0, choice1);

            return count_hash[search_key];
        };

        int ans = dfs(n-1, amount);
        return ans == numeric_limits<int>::max() ? -1 : ans;
    }

    int coinChangeDP(vector<int>& coins, int amount) {

        int n = coins.size();

        unordered_map<pair<int, int>, int> count_hash;

        vector<vector<int>> dp(n + 1, vector<int>(amount+1, numeric_limits<int>::max()));

        dp[0][0] = 0;

        for (int i = 0; i < n; ++i)
        {
            for (int c = 0; c <= amount; ++c)
            {
                if (c < coins[i])
                {
                    dp[i+1][c] = dp[i][c];
                }
                else
                {
                    int res2 = dp[i+1][c-coins[i]];
                    if (res2 != numeric_limits<int>::max()) res2 += 1;
                    dp[i+1][c] = min(dp[i][c], res2);
                }
            }
        }
        return dp[n][amount] == numeric_limits<int>::max() ? -1 : dp[n][amount];
    }

    int coinChangeDP_space_optimization(vector<int>& coins, int amount) {

        int n = coins.size();

        unordered_map<pair<int, int>, int> count_hash;

        //vector<vector<int>> dp(n + 1, vector<int>(amount+1, numeric_limits<int>::max()));
        vector<int> dp(amount+1, numeric_limits<int>::max());

        dp[0] = 0;

        for (int i = 0; i < n; ++i)
        {
            for (int c = 0; c <= amount; ++c)
            {
                if (c < coins[i])
                {
                    dp[c] = dp[c];
                }
                else
                {
                    int res2 = dp[c-coins[i]];
                    if (res2 != numeric_limits<int>::max()) res2 += 1;
                    dp[c] = min(dp[c], res2);
                }
            }
        }
        return dp[amount] == numeric_limits<int>::max() ? -1 : dp[amount];
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-322.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    //REGISTER(coinChangeMEMO)
    REGISTER(coinChangeDP_space_optimization)

    exc.run();
}