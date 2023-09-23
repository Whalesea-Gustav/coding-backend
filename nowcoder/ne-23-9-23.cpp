//
// Created by whalesea on 2023/5/15.
//

#include <bits/stdc++.h>

using namespace std;

const int mod=1e9+7;
typedef long long ll;
ll tmp(ll a ,ll k)
{
    ll rec=1;
    while(k)
    {
        if (k&1)
            rec=((rec%mod)*(a%mod))%mod;
        a=((a%mod)*(a%mod))%mod;
        k>>=1;
    }
    return rec%mod;
}



int main() {
    //1 / L % mod = L^(mod-2) % mod
    //cout << ksm(2, mod-2)  << endl;

    int n;

    cin >> n;

    vector<int> data(n, 0);

    for (int i = 0; i < n; ++i)
    {
        cin >> data[i];
    }

    ll ans = 1;

    ll res = 0;

    for (int L = 1; L <= n - 1; ++L)
    {
        ans = ans * (n - 1 - L + 1) / L;

        res += ans * tmp(L+1, mod-2);

        res = res % mod;
    }

    res = (res + 1) % mod;



    ll pre_res = 0;
    for (int i = 0; i < n; ++i)
    {
        pre_res = (pre_res + data[i]) % mod;
    }

    ll tmp_res = pre_res * (tmp(2, n) - 1);
    tmp_res = tmp_res % mod;
    tmp_res = tmp_res * tmp(n, mod-2) % mod;

    cout << tmp_res << endl;

    cout << (pre_res * res) % mod << endl;
}
