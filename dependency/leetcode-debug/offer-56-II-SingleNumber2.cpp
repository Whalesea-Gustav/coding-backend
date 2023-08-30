#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

namespace std
{
    template<>
    struct hash<pair<int, int>>
    {
        size_t operator()(pair<int, int> const & t) const
        {
            size_t h1 = hash<int>()(t.first);
            size_t h2 = hash<int>{}(t.second);
            return h1 ^ (h2 << 1);
        }
    };
}

using namespace std;

class Solution {
public:
    int singleNumbers2(vector<int>& nums) {
        vector<int> count(32, 0);

        for (auto num : nums)
        {
            for (int i = 0; i <= 31; ++i)
            {
                if(num & (1 << i))
                {
                    count[i]++;
                }
            }
        }

        for (int i = 0; i <= 31; ++i)
        {
            count[i] %= 3;
        }

        int result = 0;

        for (int i = 0; i <= 31; ++i)
        {
            result += count[i] * (1 << i);
        }

        return result;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offer-56-II.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(singleNumbers2)

    exc.run();
}