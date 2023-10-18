#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    string minWindow_v2(string& s, string& t)
    {
        unordered_map<char,int> tcount;
        int allcount = 0;
        for (auto c : t)
        {
            tcount[c]++;
            allcount++;
        }

        unordered_map<char,int> scount;

        int left = 0;
        int right = 0;
        int n = s.size();
        int curcount = 0;

        string res = "";
        int minlen = numeric_limits<int>::max();
        while(left < n && right < n && left <= right)
        {
            if(tcount.count(s[right]) > 0)
            {
                if(scount[s[right]] < tcount[s[right]])
                {
                    curcount++;
                }
                scount[s[right]]++;
            }

            while(left < n && left < right)
            {
                if(tcount.count(s[left]) == 0)
                {
                    ++left;
                }
                else if (scount[s[left]] > tcount[s[left]])
                {
                    --scount[s[left]];
                    ++left;
                }
                else
                {
                    break;
                }
            }

            if(curcount == allcount)
            {
                int curlength = right - left + 1;
                if(curlength < minlen)
                {
                    minlen = curlength;
                    res = s.substr(left, curlength);
                }


                --scount[s[left]];
                ++left;
                --curcount;
            }

            ++right;
        }

        return res;

    }

};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-76.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(minWindow_v2)

    exc.run();
}