#include <bits/stdc++.h>

using namespace std;

int MOD = 998244353;

using m_LL = long long;

namespace std
{
    template<>
    struct hash<pair<m_LL, m_LL>>
    {
        size_t operator()(pair<m_LL, m_LL> const & t) const
        {
            size_t t1 = hash<m_LL>{}(t.first);
            size_t t2 = hash<m_LL>{}(t.second);

            return t1 ^ (t2 >> 1);
        }
    };
}

int main()
{
    int T;
    cin >> T;
    constexpr size_t sz = 1e18;

    int dp;

    for (int j = 1; j <= 10; ++j)
    {
    }

    for (int i = 0 ; i < T; ++i)
    {
        int n, k;
        cin >> n >> k;
    }
}