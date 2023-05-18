#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;

    cin >> n >> m;

    vector<int> a(n,0);
    vector<int> b(m, 0);

    for (int i = 0 ; i < n; ++i)
    {
        cin >> a[i];
    }

    for (int i = 0 ; i < m; ++i)
    {
        cin >> b[i];
    }

    sort(a.begin(), a.end());

    sort(b.begin(), b.end(), greater<int>());

    if (a[0] >= b[0])
    {
        a[0] = b[0];
    }
    else
    {
        for (int i = 0 ; i < n; ++i)
        {
            if (a[i] <= b[0])
            {
                swap(a[i], b[0]);
                sort(b.begin(), b.end(), greater<int>());
            }
            else
            {
                break;
            }
        }
    }

    long long sum = 0;
    for (int i = 0 ; i < n; ++i)
    {
        sum += static_cast<long long>(a[i]);
    }

    cout << sum << endl;
}