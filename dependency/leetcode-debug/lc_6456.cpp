#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    vector<vector<int>> memo;

    int maxIncreasingCells(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        memo = vector<vector<int>>(m, vector<int>(n, -1));

        vector<map<int, vector<int>>> rows(m);
        vector<map<int, vector<int>>> cols(n);

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                rows[i][mat[i][j]].push_back(j);
            }
        }

        for (int j = 0; j < n; ++j)
        {
            for (int i = 0; i < m; ++i)
            {
                cols[j][mat[i][j]].push_back(i);
            }
        }


        function<int(int, int)> dfs = [&](int r, int c) -> int
        {
            int& res = memo[r][c];

            if(res != -1) return res;

            int max_cell = 0;

            auto iter = rows[r].upper_bound(mat[r][c]);
            if(iter != rows[r].end())
            {
                auto& next_cols = (*iter).second;

                for (auto next_col : next_cols)
                {
                    max_cell = max(max_cell,dfs(r, next_col));
                }
            }


            iter = cols[c].upper_bound(mat[r][c]);

            if(iter != cols[c].end())
            {
                auto& next_rows = (*iter).second;

                for (auto next_row : next_rows)
                {
                    max_cell = max(max_cell,dfs(next_row, c));
                }
            }

            res = max_cell + 1;

            return res;
        };

        int max_res = 0;

        //从每行最小值开始dfs

        for (int i = 0; i < m; ++i)
        {
            int min_ele = *min_element(mat[i].begin(), mat[i].end());

            for (int j = 0; j < n; ++j)
            {
                if(mat[i][j] == min_ele)
                {
                    max_res = max(max_res, dfs(i, j));
                }
            }
        }

        return max_res;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-6456.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(maxIncreasingCells)

    exc.run();
}