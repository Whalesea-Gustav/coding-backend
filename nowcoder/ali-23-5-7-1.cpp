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
    int N;
    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        string s;
        cin >> s;

        unordered_map<char, int> count_map;
        int max_count = 0;
        for (auto c : s)
        {
            count_map[c]++;

            max_count = max(max_count, count_map[c]);
        }

        if (isPrime(max_count))
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }

    }
}