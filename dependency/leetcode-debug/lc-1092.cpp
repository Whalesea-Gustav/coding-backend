#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.size(), m = str2.size();

        vector<vector<string>> memo(n, vector<string>(m));

        function<string(int,int)> dfs = [&](int x, int y) -> string
        {
            if(x < 0 && y < 0) return "";
            if(x < 0) return str2.substr(0, y+1);
            if(y < 0) return str1.substr(0, x+1);

            auto& res = memo[x][y];

            if(res.size() != 0) return res;

            if(str1[x] == str2[y])
            {
                res = dfs(x-1, y-1) + str1[x];
            }
            else
            {
                string res1 = dfs(x-1, y);
                string res2 = dfs(x, y-1);

                res = res1.size() < res2.size() ? res1 + str1[x] : res2 + str2[y];
            }

            return res;
        };

        return dfs(n-1, m-1);
    }

    string shortestCommonSupersequence_two_way(string str1, string str2) {

        int n = str1.size(), m = str2.size();

        vector<vector<int>> memo(n, vector<int>(m, -1));

        function<int(int,int)> dfs = [&](int x, int y) -> int
        {
            if(x < 0 && y < 0) return 0;
            if(x < 0) return y+1;
            if(y < 0) return x+1;

            auto& res = memo[x][y];

            if(res != -1) return res;

            if(str1[x] == str2[y])
            {
                res = dfs(x-1, y-1) + 1;
            }
            else
            {
                int res1 = dfs(x-1, y);
                int res2 = dfs(x, y-1);

                res = min(res1, res2) + 1;
            }

            return res;
        };

        int count = dfs(n-1, m-1);

        int i = n-1, j = m-1;

        function<string(int, int)> get_ans = [&](int x, int y) -> string
        {
            if(x < 0 && y < 0) return "";

            if(x < 0) return str2.substr(0, y+1);
            if(y < 0) return str1.substr(0, x+1);

            if(str1[x] == str2[y])
            {
                return get_ans(x-1, y-1) + str1[x];
            }
            else
            {
                auto cur_length = dfs(x,y);
                auto res1 = dfs(x-1, y);
                auto res2 = dfs(x, y-1);

                if(cur_length == res1 + 1)
                {
                    return get_ans(x-1, y) + str1[x];
                }
                else
                {
                    return get_ans(x, y-1) + str2[y];
                }
            }
        };

        return get_ans(n-1, m-1);
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-1092.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(shortestCommonSupersequence_two_way)

    exc.run();
}