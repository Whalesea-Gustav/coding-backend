#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        size_t size = heights.size();

        if(size == 1)  return heights[0];

        int max_area = 0;

        stack<int> s;
        for (size_t i = 0; i < heights.size(); ++i)
        {
            int height = heights[i];
            while(!s.empty() && height < heights[s.top()])
            {
                int width = heights[s.top()];
                s.pop();

                int height = i;

                if(!s.empty())
                {
                    height = i - s.top() - 1;
                }

                max_area = max(max_area, width * height);
            }

            s.push(i);
        }

        while(!s.empty())
        {
            auto height = heights[s.top()];
            int width = heights.size();
            s.pop();

            if(!s.empty())
            {
                width = width - s.top() - 1;
            }

            max_area = max(max_area, width * height);
        }

        return max_area;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-84.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(largestRectangleArea)

    exc.run();
}