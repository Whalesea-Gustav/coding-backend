#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        vector<vector<int>> pos_fruits;
        vector<vector<int>> neg_fruits;

        for (auto fruit : fruits)
        {
            int position = fruit[0];
            int amount = fruit[1];

            int dist = position - startPos;

            if (dist > 0)
            {
                pos_fruits.push_back(vector<int>{dist, amount});
            }
            else
            {
                neg_fruits.push_back(vector<int>{-dist, amount});
            }
        }

        auto cmp1 = [](vector<int>& a, vector<int>& b)
        {
            return a[0] < b[0];
        };

        sort(pos_fruits.begin(), pos_fruits.end(), cmp1);
        sort(neg_fruits.begin(), neg_fruits.end(), cmp1);

        //前缀和
        vector<int> pos_psum(pos_fruits.size() + 1, 0);
        vector<int> neg_psum(neg_fruits.size() + 1, 0);

        for (int i = 0; i < pos_fruits.size(); ++i)
        {
            pos_psum[i+1] = pos_psum[i] + pos_fruits[i][1];
        }

        for (int i = 0; i < neg_fruits.size(); ++i)
        {
            neg_psum[i+1] = neg_psum[i] + neg_fruits[i][1];
        }

        int max_amount = 0;

        for (int i = 0; i < pos_fruits.size(); ++i)
        {
            int dist = pos_fruits[i][0];
            int amount = pos_psum[i+1];

            if(dist > k) break;

            int remain_dist = k - 2 * dist;

            //二分查找
            int l = 0, r = neg_fruits.size() - 1;

            while(l <= r)
            {
                int mid = l + ((r-l) >> 1);
                if(neg_fruits[mid][0] >= remain_dist + 1)
                {
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            //(r, l)
            amount += neg_psum[r+1];

            max_amount = max(max_amount, amount);
        }

        for (int i = 0; i < neg_fruits.size(); ++i)
        {
            int dist = neg_fruits[i][0];
            int amount = neg_psum[i+1];

            if(dist > k) break;

            int remain_dist = k - 2 * dist;

            //二分查找
            int l = 0, r = pos_fruits.size() - 1;

            while(l <= r)
            {
                int mid = l + ((r-l) >> 1);
                if(pos_fruits[mid][0] >= remain_dist + 1)
                {
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            //(r, l)
            amount += pos_psum[r+1];

            max_amount = max(max_amount, amount);
        }

        return max_amount;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-2106.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(maxTotalFruits)

    exc.run();
}