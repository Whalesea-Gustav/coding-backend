#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> memo{8, vector<int>(1001, 0)};

    int punishmentNumber(int n) {
        int sum = 0;

        for (int i = 1; i <= n; ++i)
        {
            if (isPN_dfs(i))
            {
                sum += i * i;
            }
        }

        return sum;
    }

    bool isPN(int n)
    {
        int value = n * n;

        string s = to_string(value);

        int sz = s.size();

        vector<vector<int>> dp(sz+1, vector<int>(n+1, false));
        dp[0][0] = 1;

        for (int i = 0; i < sz; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                for (int v = 1; v <= n; ++v)
                {
                    string sub = s.substr(j, i - j + 1);
                    int sub_v = stoi(sub);
                    if(v < sub_v) continue;
                    int left_v = v - sub_v;
                    dp[i+1][v] = dp[i+1][v] || dp[j][left_v];
                }
            }
        }

        return dp[sz][n];
    }

    bool isPN_memo(int n)
    {
        int value = n * n;

        string s = to_string(value);

        int sz = s.size();

        vector<vector<int>> dp(sz+1, vector<int>(n+1, false));
        dp[0][0] = 1;

        for (int i = 0; i < sz; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                for (int v = 1; v <= n; ++v)
                {
                    string sub = s.substr(j, i - j + 1);
                    int sub_v = stoi(sub);
                    if(v < sub_v) continue;
                    int left_v = v - sub_v;
                    dp[i+1][v] = dp[i+1][v] || dp[j][left_v];
                }
            }
        }

        return dp[sz][n];
    }

    bool isPN_dfs(int n)
    {
        int n_sq = n * n;
        string s = to_string(n_sq);

        bool isFind = false;
        function<void(int, int)> dfs = [&](int index, int sum) -> void
        {
            if (index >= s.size())
            {
                if(sum == n)
                {
                    isFind = true;
                }

                return;
            }

            for (int i = index+1; i <= s.size(); ++i)
            {
                string sub = s.substr(index, i - index);
                dfs(i, sum + stoi(sub));
            }

            return;
        };

        dfs(0, 0);

        return isFind;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-6441.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(isPN_dfs)

    exc.run();
}