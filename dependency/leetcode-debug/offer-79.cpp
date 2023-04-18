#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> ans;
        vector<vector<int>> res;
        dfs2(nums, 0, ans, res);
        return res;
    }

    void dfs(vector<int>& nums, int step, vector<int>& ans, vector<vector<int>>& res)
    {
        if (step == nums.size())
        {
            res.push_back(ans);
            return;
        }

        dfs(nums, step+1, ans, res);

        ans.push_back(nums[step]);
        dfs(nums, step+1, ans, res);
        ans.pop_back();
    }

    void dfs2(vector<int>& nums, int select, vector<int>& ans, vector<vector<int>>& res)
    {
        res.push_back(ans);
        if (select == nums.size())
        {
            return;
        }

        for (int i = select; i < nums.size(); ++i)
        {
            ans.push_back(nums[i]);
            dfs(nums, i+1, ans, res);
            ans.pop_back();
        }
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offer-79.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(subsets)

    exc.run();
}