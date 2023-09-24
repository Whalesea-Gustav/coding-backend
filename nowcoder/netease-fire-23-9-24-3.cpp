#include <bits/stdc++.h>

using namespace std;

struct Grass
{
    int Value;
    int Atr;
    int AtrNum;
};

int main() {
    int N, K, X, Y;

    cin >> N >> K >> X >> Y;

    vector<Grass> grass;

    for (int i = 0; i < N; ++i)
    {
        int v, a, b;
        cin >> v >> a >> b;

        grass.push_back({v, a, b});
    }


    vector<vector<unordered_map<int, int>>> memo = vector<vector<unordered_map<int, int>>>(N, vector<unordered_map<int, int>>(K+1));

    function<int(int, int, int)> dfs = [&](int grass_id, int grass_num, int targetNum) -> int {
        //边界条件
        if (targetNum == 0)
        {
            return 0;
        }

        if(grass_id >= N)
        {
            return numeric_limits<int>::max() / 2;
        }
        else if (grass_num >= K)
        {
            return numeric_limits<int>::max() / 2;
        }

        if(memo[grass_id][grass_num].count(targetNum) > 0)
        {
            return memo[grass_id][grass_num][targetNum];
        }
        else
        {
            //不使用这个草药
            int v1 = dfs(grass_id+1, grass_num, targetNum);

            //使用这个草药
            int cur_target = grass[grass_id].Atr == 1 ? 1 : -1;

            cur_target *= grass[grass_id].AtrNum;

            cur_target = targetNum - cur_target;

            int v2 = grass[grass_id].Value + dfs(grass_id+1, grass_num+1, cur_target);

            memo[grass_id][grass_num][targetNum] = min(v1, v2);

            return memo[grass_id][grass_num][targetNum];
        }
    };

    function<pair<bool, int>(int, int, int)> dfs2 = [&](int grass_id, int grass_num, int num) -> pair<bool, int> {
        if (num == 0) {
            return {true, 0};
        }

        if (grass_id >= N) {
            return {false, -1};
        }

        if (grass_num >= K) {
            return {false, -1};
        }

        if (memo[grass_id][grass_num].count(num) > 0)
        {
            return {true, memo[grass_id][grass_num][num]};
        }
        else
        {
            //不使用这个草药
            auto res1 = dfs2(grass_id + 1, grass_num, num);

            int nv = grass[grass_id].Atr == 1 ? 1 : -1;
            nv *= grass[grass_id].AtrNum;

            //使用这个草药
            auto res2 = dfs2(grass_id + 1, grass_num + 1, num - nv);

            int res = numeric_limits<int>::max();

            bool resb = false;
            resb = resb | res1.first;
            resb = resb | res2.first;
            if(res1.first)
            {
                res = min(res, res1.second);
            }
            if(res2.first)
            {
                res = min(res, res2.second + grass[grass_id].Value);
            }

            if(resb)
            {
                memo[grass_id][grass_num][num] = res;
            }

            return {resb, res};
        }
    };



    int Num = X == 1 ? Y : -Y;

    auto[flag, value2] = dfs2(0, 0, Num);

    if(flag)
    {
        cout << value2 << endl;
    }
    else
    {
        cout << "Cannot Make It!" << endl;
    }
}
