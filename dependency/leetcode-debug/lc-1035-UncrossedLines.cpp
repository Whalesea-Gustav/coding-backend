#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {

        return maxUncrossedLines_SpaceOptimization(nums1, nums2);

        int m = nums1.size();
        int n = nums2.size();

        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
                if(nums1[i] == nums2[j])
                {
                    dp[i+1][j+1] = max(dp[i+1][j+1], 1 + dp[i][j]);
                }
            }
        }

        return dp[m][n];
    }

    int maxUncrossedLines_SpaceOptimization(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();

        vector<int> dp(n+1, 0);

        for (int i = 0; i < m; ++i)
        {
            int prev = 0;
            for (int j = 0; j < n; ++j)
            {
                int cur = dp[j+1];
                dp[j+1] = max(dp[j+1], dp[j]);
                if(nums1[i] == nums2[j])
                {
                    dp[j+1] = max(prev+1, dp[j+1]);
                }

                prev = cur;
            }
        }

        return dp[n];
    }

};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-1035.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(maxUncrossedLines)

    exc.run();
}