#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    //选择问题

    //1. dp
    // k*n = 10^5 * 10^5 超时
    int miceAndCheese_dfs(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size();

        vector<vector<int>> dp(n, vector<int>(k+1, -1));

        function<int(int, int)> dfs = [&](int id, int left_k) -> int
        {
            if(id >= n && left_k > 0)
            {
                return numeric_limits<int>::min();
            }

            if(left_k == 0)
            {
                int sum = 0;

                for (int i = id; i < n; ++i)
                {
                    sum += reward2[i];
                }

                return sum;
            }

            auto& res = dp[id][left_k];

            if(res != -1) return res;

            int max_res = 0;

            //option1

            max_res = max(max_res, reward2[id] + dfs(id+1, left_k));


            max_res = max(max_res, reward1[id] + dfs(id+1, left_k-1));


            res = max_res;

            return res;
        };
        int res = dfs(0, k);

        return res;
    }

    //2. 贪心
    // k+n = 2 * 10^5
    int miceAndCheese_greedy(vector<int>& reward1, vector<int>& reward2, int k) {
        int ans = 0;
        int n = reward1.size();
        vector<int> diffs(n);
        for (int i = 0; i < n; i++) {
            ans += reward2[i];
            diffs[i] = reward1[i] - reward2[i];
        }
        sort(diffs.begin(), diffs.end());
        for (int i = 1; i <= k; i++) {
            ans += diffs[n - i];
        }
        return ans;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-2611.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(miceAndCheese_greedy)

    exc.run();
}