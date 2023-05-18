#include <bits/stdc++.h>

using namespace std;


bool isPrime(int x)
{
    for (int i = 2; i * i <= x; ++i)
    {
        if (x % i == 0)
        {
            return false;
        }
    }

    return true;
}



int main()
{
    //[直线条数][交点个数]
    vector<vector<int>> memo(21, vector<int>(21 * 21 / 2, -1));

    for (int i = 1; i <= 20; ++i)
    {
        memo[i][0] = 1;
    }

    function<int(int, int)> dfs= [&](int n, int p) -> int
    {
        if (p == 0 && n >= 0) return 1;
        if (p < 0) return 0;

        if (memo[n][p] != -1) return memo[n][p];

        int state = 0;

        for (int i = 1; i <= n - 1; ++i)
        {
            int left_line = n - i;

            int left_point = p - i * left_line;

            int res = dfs(left_line, left_point);

            if (res == 1)
            {
                state = 1;
            }
        }

        memo[n][p] = state;

        return state;
    };

    //cout << dfs(3, 3) << endl;

    int n;

    while(cin>>n)
    {
        for (int i = 0; i <= n * (n-1) / 2; ++i)
        {
            if (dfs(n,i) == 1)
            {
                cout << i << " ";
            }
        }

        cout << endl;
    }

}