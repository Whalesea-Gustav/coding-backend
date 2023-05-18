#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> memo(m, vector<int>(n, -1));

        auto isValid = [&](int x, int y) -> bool
        {
            if (x < 0 || x >= m) return false;
            if (y < 0 || y >= n) return false;

            return true;
        };

        vector<int> dir = {-1, 0, 1};

        function<int(int,int)> dfs = [&](int x, int y) -> int
        {
            if(memo[x][y] != -1) return memo[x][y];

            if (y == n - 1) return 0;

            int max_step = -1;

            for (int d = 0; d < 3; ++d)
            {
                int next_x = x + dir[d];
                int next_y = y + 1;

                if(isValid(next_x, next_y))
                {
                    if(grid[next_x][next_y] <= grid[x][y]) continue;

                    max_step = max(max_step, dfs(next_x, next_y));
                }
            }

            memo[x][y] = max_step + 1;

            return memo[x][y];
        };


        int max_step = 0;


        for (int i = 0; i < m; ++i)
        {
            max_step = max(max_step, dfs(i, 0));
        }

        return max_step;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-6433.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(maxMoves)

    exc.run();
}