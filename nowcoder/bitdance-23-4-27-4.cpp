#include <bits/stdc++.h>

using namespace std;

using m_LL = long long;

int main() {

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t)
    {
        m_LL n, L, R;

        cin >> n >> L >> R;

        m_LL max_num = 0;

        for (m_LL iter = L; iter <= R; ++iter)
        {
            max_num = max(max_num, n ^ iter);
        }

        cout << max_num << endl;
    }
}
