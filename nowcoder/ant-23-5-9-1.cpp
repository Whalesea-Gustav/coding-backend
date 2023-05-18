#include <bits/stdc++.h>

using namespace std;

using m_LL = long long;

int main()
{
    m_LL t;
    cin >> t;

    m_LL count = 0;
    int limit = 16;
    for (int i = 0; i < limit; ++i)
    {
        char ci = i < 10 ? ('0' + i) : ('A' + i - 10);

        for (int j = 0; j < limit; ++j)
        {
            if (j == i) continue;
            char cj = j < 10 ? ('0' + j) : ('A' + j - 10);

            for (int k = 0; k < limit; ++k)
            {
                if (k == i || k == j) continue;

                char ck = k < 10 ? ('0' + k) : ('A' + k - 10);

                for (int l = 0; l < limit; ++l)
                {
                    if(l == i || l == j || l == k) continue;

                    char cl = l < 10 ? ('0' + l) : ('A' + l - 10);

                    count++;
                    if(count == t)
                    {
                        //输出 ijkl
                        cout << ci << cj << ck << cl << endl;
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}