#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>>& queries) {
        //根据染色前后的相邻状态，判断数目的变化情况

        vector<int> res;

        vector<int> state(n, 0);


        int count = 0;

        for (int i = 0; i < queries.size(); ++i)
        {
            int index = queries[i][0];
            int color = queries[i][1];

            if(color == state[index])
            {
                res.push_back(count);
                continue;
            }

            bool pre1 = false, pre2 = false;
            bool aft1 = false, aft2 = false;

            if(index > 0)
            {
                if (state[index-1] == state[index] && state[index] != 0)
                {
                    pre1 = true;
                }

                if (state[index-1] == color && color != 0)
                {
                    aft1 = true;
                }
            }

            if(index < n - 1)
            {
                if(state[index] == state[index+1] && state[index] != 0)
                {
                    pre2 = true;
                }

                if(color == state[index+1] && color != 0)
                {
                    aft2 = true;
                }
            }

            state[index] = color;

            count += aft1 + aft2 - pre1 - pre2;

            res.push_back(count);
        }

        return res;
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-6418.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(colorTheArray)

    exc.run();
}