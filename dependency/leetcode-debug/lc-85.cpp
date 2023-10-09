#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int j = 0; j < n; ++j)
        {
            for (int i = 0; i < m; ++i)
            {
                dp[i][j] = matrix[i][j]== '0' ? 0 :  (i==0 ? 1 : dp[i-1][j] + 1);
            }
        }

        //每一行
        int area = 0;

        for (int i = 0; i < m; ++i)
        {
            stack<int> stk;

            for(int j = 0; j < n; ++j)
            {
                while(!stk.empty() && dp[i][j] < dp[i][stk.top()])
                {
                    int pre = stk.top();
                    stk.pop();

                    int height = dp[i][pre];

                    int width = j;
                    if(!stk.empty())
                    {
                        width = j - stk.top() - 1;
                    }

                    area = max(area, height * width);
                }

                stk.push(j);
            }

            while(!stk.empty())
            {
                int height = dp[i][stk.top()];
                stk.pop();
                int width = n;
                if(!stk.empty())
                {
                    width = n - stk.top() - 1;
                }

                area = max(area, height * width);
            }
        }

        return area;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-85.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(maximalRectangle)

    exc.run();
}