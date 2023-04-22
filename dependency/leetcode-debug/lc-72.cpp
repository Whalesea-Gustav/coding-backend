#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minDistance_DP(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m+1, vector<int>(n+1));

        vector<int> dp1(n+1);
        for (int i = 0; i < n; ++i)
        {
            dp[0][i+1] = i + 1;
        }

        for (int j = 0; j < m; ++j)
        {
            dp[j+1][0] = j + 1;
        }


        for (int i = 0; i < m; ++i)
        {

            for (int j = 0; j < n; ++j)
            {
                if(word1[i] == word2[j])
                {
                    dp[i+1][j+1] = dp[i][j];
                }
                else
                {
                    dp[i+1][j+1] = dp[i][j] + 1;
                    dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j+1] + 1);
                    dp[i+1][j+1] = min(dp[i+1][j+1], dp[i+1][j] + 1);
                }

            }
        }

        return dp[m][n];
    }

    int minDistance_DP_space_optimization(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        vector<int> dp(n+1);

        for (int i = 0; i < n; ++i)
        {
            dp[i+1] = i + 1;
        }

        for (int i = 0; i < m; ++i)
        {
            int pre = i;
            dp[0] = i;
            for (int j = 0; j < n; ++j)
            {
                int cur = dp[j+1];
                if(word1[i] == word2[j])
                {
                    dp[j+1] = pre;
                }
                else
                {
                    dp[j+1] = min(dp[j+1], pre);
                    dp[j+1] = min(dp[j+1], dp[j]);

                    dp[j+1]++;
                }
                pre = cur;
            }
        }

        return dp[n];
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-72.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(minDistance_DP_space_optimization)

    exc.run();
}