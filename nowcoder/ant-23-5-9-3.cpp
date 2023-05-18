#include <bits/stdc++.h>

using namespace std;

using m_LL = long long;

m_LL MOD = 1e9 + 7;

m_LL cxk(int x, int k)
{
    m_LL deno = 1;
    m_LL nom = 1;

    for (int i = 1; i <= k; ++i)
    {
        deno *= (x - i + 1);
        nom *= i;
    };

    return (deno / nom) % MOD;
}

int main()
{
    string s;
    cin >> s;

    unordered_map<char, int> count_map;

    for (auto c : s)
    {
        count_map[c]++;
    }

    m_LL res = 1;


    for (char c = 'a'; c <= 'z'; ++c)
    {
        m_LL local_res = 1;

        if (count_map[c] < 2) continue;

        for (int i = 2; i <= count_map[c] ; i+=2)
        {
            local_res = (local_res + cxk(count_map[c], i)) % MOD;
        }

        res = (res * local_res % MOD);
    }

    cout << res - 1 << endl;
}