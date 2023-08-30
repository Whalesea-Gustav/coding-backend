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
    vector<int> singleNumbers3(vector<int>& nums) {
        int tmp = 0;

        for (auto num : nums)
        {
            tmp ^= num;
        }

        tmp = ((tmp - 1) & tmp) ^ tmp;

        int res1 = 0, res2 = 0;

        for (auto num : nums)
        {
            if(tmp & num)
            {
                res1 ^= num;
            }
            else
            {
                res2 ^= num;
            }
        }

        return {res1, res2};
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offer-56-I.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(singleNumbers3)

    exc.run();
}