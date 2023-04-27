#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;


bool isGood(const string& s)
{
    char head = s[0];

    for (auto c : s)
    {
        if (head != c)
        {
            return false;
        }
    }

    return true;
}



int main() {
    int n, k;

    cin >> n >> k;

    string str;
    cin >> str;

    unordered_map<string, vector<int>> pos_hash;

    for (int i = 0; i <= n - k; ++i)
    {
        string s = str.substr(i, k);

        pos_hash[s].push_back(i);
    }

    int max_count = 0;

    for (auto hp : pos_hash)
    {
        if (isGood(hp.first))
        {
            //找到互不重叠的所有字串
            vector<int> pos = hp.second;

            //dp问题
            vector<int> dp(pos.size()+1, 0);
            dp[1] = 1;

            for (int t = 1; t < pos.size(); ++t)
            {
                int pt = pos[t];
                int target_p = pt - k;
                int target_i = -1;
                auto iter = upper_bound(pos.begin(), pos.end(), target_p);

                if (iter != pos.begin())
                {
                    iter--;
                    target_i = *iter; //内容不是长度
                    target_i = distance(pos.begin(), iter);
                }
                dp[t+1] = max(dp[t], dp[target_i+1] + 1);
            }

            max_count = max(max_count, dp[pos.size()]);
        }
    }

    cout << max_count << endl;
}
