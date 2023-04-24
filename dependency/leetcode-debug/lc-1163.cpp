#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    string lastSubstring(string s) {
        unordered_map<char, vector<int>> pos_hash;

        char max_char = 'a';

        for (int i = 0 ; i < s.size(); ++i)
        {
            pos_hash[s[i]].push_back(i);
            max_char = max(max_char, s[i]);
        }

        vector<int> vec = pos_hash[max_char];

        while(true)
        {
            int legal_count = 0;
            int legal_idx = -1;
            for (int i = 0; i < vec.size(); ++i)
            {
                if (vec[i] != -1)
                {
                    legal_idx = i;
                    legal_count++;
                }
            }

            if (legal_count == 1)
            {
                int start_pos = pos_hash[max_char][legal_idx];
                return s.substr(start_pos, s.size());
                break;
            }

            vector<int> new_vec(vec.size(), -1);

            char local_max_char = 'a';
            for (int i = 0; i < new_vec.size(); ++i)
            {
                if(vec[i] == -1) continue;

                local_max_char = max(local_max_char, s[vec[i]]);
            }

            for (int i = 0; i < new_vec.size(); ++i)
            {
                if (vec[i] == -1 || vec[i] >= s.size()) continue;
                if (s[vec[i]] < local_max_char) continue;

                new_vec[i] = vec[i] + 1;
            }

            swap(new_vec, vec);
        }

        return "";
    }

    string lastSubstring_two_pointer(string& s)
    {
        char max_c = 'a';

        int n = s.size();

        for (int i = 0; i < s.size(); ++i)
        {
            max_c = max(s[i], max_c);
        }

        int left = 0;

        while(s[left] != max_c)
        {
            ++left;
        }

        int right = left + 1;

        while(left < n && right < n)
        {
            if (s[right] != max_c)
            {
                right++;
            }
            else
            {
                int j = left + 1;
                int k = right + 1;
                if (k >= n) break;

                while(k < n)
                {
                    if (s[j] == s[k])
                    {
                        ++j;
                        ++k;
                    }
                    else
                    {
                        if (s[j] > s[k])
                        {
                            ++right;
                        }
                        else
                        {
                            left = right;
                            ++right;
                        }
                        break;
                    }
                }
            }
        }

        return s.substr(left, s.size());
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-1163.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(lastSubstring_two_pointer)

    exc.run();
}