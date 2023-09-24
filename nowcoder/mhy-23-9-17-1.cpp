#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;

#define DEBUG

#if defined(DEBUG) && defined(GJY_SYSTEM)
#define MY_LOG(x) x
#else
#define MY_LOG(x)
#endif

int main() {
    int n;

    cin >> n;

    //初始贴图尺寸 10

    auto convert = [](int a) -> int
    {
        int c = 0;
        while (a >= 2)
        {
            a /= 2;
            c++;
        }
        return c;
    };

    vector<vector<int>> data(n);
    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        int w, s;
        cin >> w >> s;
        data[i] = {w, s};
    }

    auto cmp = [](pair<int, float>& a, pair<int, float>& b)
            -> bool {
        if (a.second == b.second)
        {
            return a.first > b.first;
        }
        else
        {
            return a.second < b.second;
        }
    };

    priority_queue<pair<int, float>,
            vector<pair<int, float>>, decltype(cmp)>
                    pq(cmp);

    for (int i = 0; i < n; ++i)
    {
        pq.emplace(convert(data[i][0]), data[i][1]);
    }

    vector<int> count(11, 0);
    count[10] = 1;

    auto try_GetId = [&](int id) -> bool
    {

    };

    while(!pq.empty())
    {
        auto top_ele = pq.top();
        int id = top_ele.first;
        float value = top_ele.second;
        pq.pop();
    }

    return sum;
}
