#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        if(n == 0) return false;

        int m = matrix[0].size();

        int x = 0, y = m - 1;

        while(x <= n-1 && y >= 0)
        {
            if(matrix[x][y] == target)
            {
                return true;
            }
            else if (matrix[x][y] > target)
            {
                --y;
            }
            else if (matrix[x][y] < target)
            {
                ++x;
            }
        }

        return false;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offer-04.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(findNumberIn2DArray)

    exc.run();
}