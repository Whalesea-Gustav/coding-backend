#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<int> max_nums(N);

    for (int i = 0; i < N; ++i)
    {
        int local_max = 0;

        for (int j = 0; j < 6; ++j)
        {
            int num;
            cin >> num;
            local_max = max(local_max, num);
        }

        max_nums[i] = local_max;
    }

    auto cmp = [](int a, int b) -> bool
    {
        if (a < 10 && b < 10)
        {
            return a > b;
        }
        else if (a >= 10 && b >= 10)
        {
            return a > b;
        }
        else if (a >= 10 && b < 10)
        {
            int a_first = a / 10;
            int a_second = a % 10;

            if (a_first > b)
            {
                return a > b;
            }
            else if (a_first == b)
            {
                return a_second > b;
            }
            else
            {
                return a < b;
            }
        }
        else if (a < 10 && b >= 10)
        {
            int b_first = b / 10;
            int b_second = b % 10;

            if (b_first > a)
            {
                return a > b;
            }
            else if (b_first == b)
            {
                return a > b_second;
            }
            else
            {
                return a < b;
            }
        }

        return true;
    };

    sort(max_nums.begin(), max_nums.end(), cmp);

    int res = 0;

    for (int i = 0; i < N; ++i)
    {
        if (max_nums[i] >= 10)
        {
            res = res * 100 + max_nums[i];
        }
        else
        {
            res = res * 10 + max_nums[i];
        }
    }
    cout << res << endl;
}