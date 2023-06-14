#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxRepOpt1(string text) {
        unordered_map<char, int> count_map;

        int n = text.size();

        for (auto c : text)
        {
            ++count_map[c];
        }

        int max_count = 1;

        for (int left = 0; left < n;)
        {
            int count = 0;

            int cur_count = count_map[text[left]];

            int right = left;

            while(right < n)
            {
                if(text[left] == text[right])
                {
                    count++;
                    right++;
                }
                else
                {
                    break;
                }
            }

            int next_left = right;
            right++;

            while(right < n)
            {
                if(text[left] == text[right])
                {
                    right++;
                    count++;
                }
                else
                {
                    break;
                }
            }

            if(cur_count > count)
            {
                count++;
            }

            max_count = max(max_count, count);

            left = next_left;
        }

        return max_count;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-1156.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(maxRepOpt1)

    exc.run();
}