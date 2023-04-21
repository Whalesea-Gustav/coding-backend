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
    bool isMatch_memo(const string s, const string p) {
        int n = s.size();
        int m = p.size();

        unordered_map<pair<int, int>, bool> memo;

        function<bool(int, int)> dfs = [&](int i, int j) -> bool
        {
            if (i < 0 && j < 0) return true;
            if (j < 0) return false;
            if (i < 0 && p[j] != '*') return false;


            if (i < 0 && j >= 1)
            {
                if (p[j] == '*')
                {
                    return dfs(i, j-2);
                }
                else
                {
                    return false;
                }
            }

            auto key = make_pair(i, j);
            if (memo.count(key) > 0) return memo[key];

            //尝试进行匹配
            if (p[j] == '.' || s[i] == p[j])
            {
                bool res = dfs(i-1, j-1);
                memo[key] = res;
            }
            else if (p[j] == '*')
            {
                if (p[j-1] == '.' || s[i] == p[j-1])
                {
                    bool res1 = dfs(i-1, j);
                    bool res2 = dfs(i-1, j-2);
                    bool res3 = dfs(i, j-2);

                    memo[key] = res1 || res2;
                    memo[key] = memo[key] || res3;
                }
                else
                {
                    bool res = dfs(i, j-2);
                    memo[key] = res;
                }
            }
            else
            {
                memo[key] = false;
            }

            return memo[key];
        };

        return dfs(n-1, m-1);
    }

    bool isMatch_dp(const string s, const string p) {
        int n = s.size();
        int m = p.size();

        unordered_map<pair<int, int>, bool> memo;

        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
        dp[0][0] = true;

        for (int j = 0; j < m-1;)
        {
            if (p[j+1] == '*')
            {
                dp[0][j+2] = true;
                j = j + 2;
            }
            else
            {
                break;
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (s[i] == p[j] || p[j] == '.')
                {
                    dp[i+1][j+1] = dp[i][j];
                }
                else if (p[j] == '*')
                {
                    bool res1 = dp[i+1][j-1];

                    bool res2 = false, res3 = false;

                    if (s[i] == p[j-1] || p[j-1] == '.')
                    {
                        res2 = dp[i][j-1];
                        res3 = dp[i][j+1];
                    }

                    dp[i+1][j+1] = res1 || res2 || res3;
                }
                else
                {
                    dp[i+1][j+1] = false;
                }
            }
        }

        return dp[n][m];
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lcII-19.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(isMatch_dp)

    exc.run();
}