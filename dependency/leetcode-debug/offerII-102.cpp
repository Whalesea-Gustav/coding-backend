#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = accumulate(nums.begin(), nums.end(), 0);
        //pos = p, neg = n - p
        // p - (n-p) = target
        // p = (target+n) % 2

        target = target + n;

        if (target < 0 || target % 2 == 1) return 0;

        target = target / 2;

        vector<vector<int>> memo(nums.size() + 1, vector<int>(target+1, -1));
        function<int(int, int)> dfs = [&](int i, int left) -> int
        {
            if (i < 0)
            {
                if (left == 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }

            }

            if (left < nums[i])
            {
                return dfs(i-1, left);
            }

            auto& v1 = memo[i][left];
            if (v1 == -1)
            {
                v1 = dfs(i-1, left);
            }

            auto& v2 = memo[i][left-nums[i]];
            if (v2 == -1)
            {
                v2 = dfs(i-1, left-nums[i]);
            }

            return v1 + v2;

            //return dfs(i - 1, left) + dfs(i - 1, left - nums[i]);
        };

        return dfs(nums.size() -1 , target);
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offerII-102.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(findTargetSumWays)

    exc.run();
}