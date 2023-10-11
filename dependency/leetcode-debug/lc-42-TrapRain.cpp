#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if(height.size() <= 1)
        {
            return 0;
        }

        int n = height.size();

        vector<int> prefix(n, 0);
        vector<int> suffix(n, 0);

        prefix[0] = height[0];
        suffix[n-1] = height[n-1];

        for (int i = 1; i < n; ++i)
        {
            prefix[i] = max(prefix[i-1], height[i]);
        }

        for (int i = n - 2; i >= 0; --i)
        {
            suffix[i] = max(suffix[i+1], height[i]);
        }

        int res = 0;

        for (int i = 0; i < n; ++i)
        {
            res += min(prefix[i], suffix[i]) - height[i];
        }

        return res;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-42.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(trap)

    exc.run();
}