#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isMatch_23_11_2(string s, string p) {
        int n = s.size();
        int m = p.size();

        vector<vector<int>> memo(n, vector<int>(m, -1));

        function<bool(int,int)> dfs = [&](int i, int j) -> bool
        {
            if(i < 0 && j < 0) return true;
            if(i < 0)
            {
                if(p[j] == '*')
                {
                    return dfs(i, j-2);
                }
                return false;
            }
            if(j < 0) return false;

            auto& res = memo[i][j];
            if(res != -1) return res;
            res = 0;

            if(s[i] == p[j])
            {
                res = dfs(i-1, j-1);
            }
            else if(p[j] == '.')
            {
                res = dfs(i-1, j-1);
            }
            else if (p[j] == '*')
            {
                res = dfs(i, j-2);
                if(s[i] == p[j-1])
                {
                    res = res || dfs(i-1, j);
                }
                else if(p[j-1] == '.')
                {
                    res = res || dfs(i-1, j);
                }
            }

            return res;
        };

        return dfs(n-1, m-1);
    }

    bool isMatch_23_10_20(string s, string p) {

        int n = s.size();
        int m = p.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));

        function<bool(int,int)> dfs = [&](int i, int j) -> bool
        {
            if(i < 0 && j < 0) return true;

            if(i < 0)
            {
                if(p[j] == '*')
                {
                    return dfs(i, j-2);
                }
                else
                {
                    return false;
                }
            }

            if(j < 0)
            {
                return false;
            }

            auto& res = dp[i][j];

            if(res != -1) return res;

            res = false;

            if(s[i] == p[j] || p[j] == '.')
            {
                res = res | dfs(i-1, j-1);
            }
            else if (p[j] == '*')
            {

                if(p[j-1] == '.' || p[j-1] == s[i])
                {
                    res = res | dfs(i-1, j);
                }

                res = res | dfs(i, j-2);
            }

            return res;
        };

        return dfs(n-1,m-1);
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-10.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(isMatch_23_10_20)

    exc.run();
}