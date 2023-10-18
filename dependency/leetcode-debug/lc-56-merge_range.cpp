#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge_left_bound_sort(vector<vector<int>>& intervals) {

        vector<vector<int>> res;

        sort(intervals.begin(), intervals.end(),
             [](vector<int>& a, vector<int>& b) -> bool
             {
                 if (a[0] < b[0])
                 {
                     return true;
                 }
                 else if (a[0] > b[0])
                 {
                     return false;
                 }
                 else
                 {
                     return a[1] < b[1];
                 }

             });

        res.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); ++i)
        {
            auto interval = intervals[i];
            if(res.back()[0] <= interval[0] && res.back()[1] >= interval[0])
            {
                res.back()[1] = max(res.back()[1], interval[1]);
            }
            else
            {
                res.push_back(interval);
            }
        }

        return res;
    }

    vector<vector<int>> merge_right_bound_sort(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) -> bool
        {
            if(a[1] < b[1])
            {
                return true;
            }
            else if (a[1] > b[1])
            {
                return false;
            }
            else
            {
                return a[0] > b[0];
            }
        });

        vector<vector<int>>res;
        res.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); ++i)
        {
            int low = intervals[i][0];
            int high = intervals[i][1];

            while(!res.empty() && res.back()[1] >= low && res.back()[1] <= high)
            {
                low = min(res.back()[0], low);
                res.pop_back();
            }

            res.push_back({low, high});
        }

        return res;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-56.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(merge_right_bound_sort)

    exc.run();
}