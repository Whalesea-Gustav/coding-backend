#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> min_vec(n, 0);
    vector<int> max_vec(n, 0);

    for (int i = 0 ; i < n; ++i)
    {
        string data;
        cin >> data;

        for (int d = 0 ; d < data.size(); ++d)
        {
            if(data[d] == '?' && d == 0)
            {
                min_vec[i] = (data.size() == 1) ? 0 : 1;
                max_vec[i] = 9;
            }
            else if (data[d] == '?' && d != 0)
            {
                min_vec[i] = min_vec[i] * 10;
                max_vec[i] = max_vec[i] * 10 + 9;
            }
            else if (data[d] >= '0' && data[d] <= '9')
            {
                min_vec[i] = min_vec[i] * 10 + data[d] - '0';
                max_vec[i] = max_vec[i] * 10 + data[d] - '0';
            }
        }
    }

    vector<int> pre_max(n+1, 0);
    vector<int> suf_max(n+1, 0);

    for (int i = 0; i < n; ++i)
    {
        pre_max[i+1] = max(pre_max[i], max_vec[i]);
    }

    for (int i = n-1; i >= 0; --i)
    {
        suf_max[i] = max(suf_max[i+1], max_vec[i]);
    }

    vector<int> exclu_max(n, 0);

    for (int i = 0; i < n; ++i)
    {
        exclu_max[i] = max(pre_max[i], suf_max[i+1]);
    }

    vector<int> pre_min(n+1, numeric_limits<int>::max());
    vector<int> suf_min(n+1, numeric_limits<int>::max());

    for (int i = 0; i < n; ++i)
    {
        pre_min[i+1] = min(pre_min[i], min_vec[i]);
    }

    for (int i = n-1; i >= 0; --i)
    {
        suf_min[i] = min(suf_min[i+1], min_vec[i]);
    }

    vector<int> exclu_min(n, 0);

    for (int i = 0; i < n; ++i)
    {
        exclu_min[i] = min(pre_min[i], suf_min[i+1]);
    }

    int max_diff = 0;

    for (int i = 0; i < n; ++i)
    {
        int max_ele = max(exclu_max[i], max_vec[i]);

        max_diff = max(max_diff, max_ele - exclu_min[i]);

        int min_ele = min(exclu_min[i], min_vec[i]);

        max_diff = max(max_diff, exclu_max[i] - min_ele);
    }

    cout << max_diff << endl;
}