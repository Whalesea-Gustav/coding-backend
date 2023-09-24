//
// Created by whalesea on 2023/9/15.
//

#include <bits/stdc++.h>

using namespace std;


int main() {

    int n, k;

    cin >> n >> k;

    vector<int> pos(n, 0);
    vector<int> color(n, 0);

    for(int i = 0; i < n; ++i)
    {
        cin >> pos[i];
    }

    for (int i = 0; i < n; ++i)
    {
        cin >> color[i];
    }

    vector<int> blue_count(n, 0);
    vector<int> red_count(n, 0);

    vector<int> pos_sum(n, 0);

    for (int i = 0; i < n; ++i)
    {
        if(i == 0)
        {
            blue_count[i] = color[i];
            red_count[i] = 1 - color[i];

            if(!color[i]) pos_sum[i] = pos[i];
        }
        else
        {
            blue_count[i] = blue_count[i-1] + color[i];
            red_count[i] += 1 - color[i];


            pos_sum[i] = pos_sum[i-1] + (color[i]? 0 : pos[i]);
        }
    }

    int res = 0;

    for (int i = 0; i < n; ++i)
    {
        if(color[i] == 0)
        {
            auto right_bound = lower_bound(blue_count.begin(), blue_count.end(), k+1);
            int right_pos = (pos_sum[n-1] - pos_sum[*right_bound]) - (*right_bound - 1) * (red_count[n-1] - red_count[*right_bound]);

        }
    }


}
