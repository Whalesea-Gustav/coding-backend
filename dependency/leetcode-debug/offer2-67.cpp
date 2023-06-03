#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int strToInt(string str) {

        if (str.size() == 0) return 0;

        bool pos = true;

        int k = 0;

        while(k < str.size() && str[k] == ' ') ++k;
        if(k == str.size()) return 0;

        if(str[k] == '+')
        {
            pos = true;
        }
        else if (str[k] == '-')
        {
            pos = false;
        }
        else if (str[k] > '9' || str[k] < '0')
        {
            return 0;
        }

        long long res = 0;

        bool find = false;
        for (int i = k; i < str.size(); ++i)
        {

            if(find) break;

            if(str[i] <= '9' && str[i] >= '0')
            {
                find = true;
                for (int j = i; j < str.size(); ++j)
                {
                    if(str[j] <= '9' && str[j] >= '0')
                    {
                        res = res * 10 + (str[j] - '0');

                        if(pos)
                        {
                            if(res > static_cast<long long>(numeric_limits<int>::max()))
                            {
                                return numeric_limits<int>::max();
                            }
                        }
                        else
                        {
                            if(-res < static_cast<long long>(numeric_limits<int>::min()))
                            {
                                return numeric_limits<int>::min();
                            }
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        return pos ? res : -res;
    }

    int strToInt2(string str) {

        if (str.size() == 0) return 0;

        bool pos = true;

        int k = 0;

        while(k < str.size() && str[k] == ' ') ++k;
        if(k == str.size()) return 0;

        if(str[k] == '+')
        {
            pos = true;
            ++k;
        }
        else if (str[k] == '-')
        {
            pos = false;
            ++k;
        }
        else if (str[k] > '9' || str[k] < '0')
        {
            return 0;
        }

        long long res = 0;

        for (int i = k; i < str.size(); ++i)
        {

            if(str[i] <= '9' && str[i] >= '0')
            {
                res = res * 10 + (str[i] - '0');

                if(pos)
                {
                    if(res > static_cast<long long>(numeric_limits<int>::max()))
                    {
                        return numeric_limits<int>::max();
                    }
                }
                else
                {
                    if(-res < static_cast<long long>(numeric_limits<int>::min()))
                    {
                        return numeric_limits<int>::min();
                    }
                }
            }
            else
            {
                break;
            }
        }

        return pos ? res : -res;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offer2-67.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(strToInt2)

    exc.run();
}