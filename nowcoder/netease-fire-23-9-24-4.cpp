#include <bits/stdc++.h>

using namespace std;


int main() {

    int N, K, X, Y;

    cin >> N >> K >> X >> Y;

    if (X == 2)
    {
        Y = Y * -1;
    }

    vector<pair<int,int>> grass_av;

    for (int i = 0; i < N; ++i)
    {
        int v, a, b;
        cin >> v >> a >> b;

        if(a == 2)
        {
            b = -b;
        }

        //atr, value
        grass_av.emplace_back(b, v);
    }

    vector<vector<unordered_map<int, int>>> memo = vector<vector<unordered_map<int, int>>>(N, vector<unordered_map<int, int>>(K+1));

    function<pair<bool,int>(int,int,int)> dfs = [&](int id, int cnt, int num) -> pair<bool,int>
    {
        if(num == 0)
        {
            return {true, 0};
        }

        if(cnt <= 0 || id >= N)
        {
            return {false, -1};
        }

        if(memo[id][cnt].count(num) > 0)
        {
            auto& value = memo[id][cnt][num];

            if(value == -1)
            {
                return {false, -1};
            }
            else
            {
                return {true, value};
            }
        }
        else
        {
            auto[f1, v1] = dfs(id+1, cnt, num);

            int cv = grass_av[id].second;
            int attr = grass_av[id].first;
            auto[f2, v2] = dfs(id+1, cnt-1, num - attr);

            if(f2) v2 = cv + v2;

            bool bFind = false;

            if(f1 && f2)
            {
                bFind = true;
                memo[id][cnt][num] =  min(v1, v2);
            }
            else if (f1)
            {
                bFind = true;
                memo[id][cnt][num] = v1;
            }
            else if (f2)
            {
                bFind = true;
                memo[id][cnt][num] = v2;
            }
            else
            {
                memo[id][cnt][num] = -1;
            }

            return {bFind, memo[id][cnt][num]};

        }
    };

    int min_value = numeric_limits<int>::max();


    for (int k = 1; k < K; ++k) {
        auto res = dfs(0, k, Y);

        if (res.first) {
            min_value = min(min_value, res.second);
        }
    }


    if(min_value < numeric_limits<int>::max())
    {
        cout << min_value << endl;
    }
    else
    {
        cout << "Cannot Make It!" << endl;
    }
}
