#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int IntersectionNum(int n) {

        vector<int> res;

        unordered_set<int> m_set;

        function<void(int, int)> dfs = [&](int i, int sum) -> void
        {
            m_set.insert(sum);
            if(i == 0) return;

            for (int j = 1; j <= i; ++j)
            {
                dfs(i - j, j * (i - j) + sum);
            }
        };

        dfs(n, 0);

        return m_set.size();
    }

};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lg-2789.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(IntersectionNum)

    exc.run();
}