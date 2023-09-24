#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;

#define DEBUG

#if defined(DEBUG) && defined(GJY_SYSTEM)
#define MY_LOG(x) x
#else
#define MY_LOG(x)
#endif

using LL = long long;

int main() {
    int x;

    cin >> x;

    string data;

    LL rem = x;

    while(rem)
    {
        LL left = rem % 5;

        data = to_string(left) + data;

        rem = rem / 5;
    }

    int n = data.size();

    int m = n + 5;

    vector<bool> flag (n+5, true);
    vector<int> num(n+5, 0);

    int inc = 0;

    for (int i = n - 1; i >= 0; --i)
    {
        int j = (n - 1) - i;

        int cur_data = data[i] - '0';
        cur_data += inc;

        if(cur_data == 5)
        {
            inc = 1;
            flag[j] = true;
            num[j] = 0;
        }
        else if(cur_data >= 0 && cur_data <= 2)
        {
            flag[j] = true;
            inc = 0;
            num[j] = cur_data;
        }
        else if(cur_data >= 3 && cur_data <= 4)
        {
            inc = 1;
            flag[j] = false;
            num[j] = 5 - cur_data;
        }
    }

    if(inc == 1)
    {
        flag[n] = true;
        num[n] = 1;
    }

    string output = "";

    for (int i = n; i >= 0; --i)
    {
        string cur;

        if(num[i] == 0) continue;

        if(!flag[i])
        {
            cur += "-";
        }
        else
        {
            if(i != n)
            {
                cur += "+";
            }
        }

        LL tmp_num = pow(5, i);

        if(num[i] == 2)
        {
            cur += "2*";
        }

        cur += to_string(tmp_num);

        output += cur;
    }

    cout << output << endl;
}

