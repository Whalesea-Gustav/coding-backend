#include <bits/stdc++.h>

using namespace std;

using m_LL = long long;

int main()
{
    m_LL k;
    cin >> k;

    m_LL count = 0;
    int limit = 16;
    for (int i = 0; i < limit; ++i)
    {
        char ci = i < 10 ? ('0' + i) : ('a' + i - 10);

        for (int j = i+1; j < limit; ++j)
        {
            char cj = j < 10 ? ('0' + j) : ('a' + j - 10);

            for (int k = j+1; k < limit; ++k)
            {
                char ck = k < 10 ? ('0' + k) : ('a' + k - 10);

                for (int l = k+1; l < limit; ++l)
                {
                    char cl = l < 10 ? ('0' + l) : ('a' + l - 10);

                    count++;
                    if(count == k)
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