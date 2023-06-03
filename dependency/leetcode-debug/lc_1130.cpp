#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();

        vector<vector<int>> max_info(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i)
        {
            for (int j = i; j < n; ++j)
            {
                if(j == i)
                {
                    max_info[i][j] = arr[j];
                }
                else
                {
                    max_info[i][j] = max(max_info[i][j-1], arr[j]);
                }
            }
        }


        function<int(int, int)> dfs = [&](int start, int end) -> int
        {
            if(start == end) return 0;

            int min_result = numeric_limits<int>::max();

            for (int split = start; split <= end - 1; ++split)
            {
                int node = max_info[start][split] * max_info[split+1][end];

                min_result = min(min_result, node + dfs(start, split) + dfs(split+1, end));
            }

            return min_result;
        };

        return dfs(0, arr.size()-1);
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-1130.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(mctFromLeafValues)

    exc.run();
}