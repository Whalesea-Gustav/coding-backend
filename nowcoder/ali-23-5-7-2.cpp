#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int k;

    cin >> n;

    vector<int> data(n, 0);

    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    cin >> k;

    vector<int> new_data(n, -1);

    k = k % n;

    for (int i = 0; i < n; ++i)
    {
        int pos = i - k;

        while (pos < 0)
        {
            pos += n;
        }

        new_data[pos] = data[i];
    }

    for (int i = 0; i < n; ++i)
    {
        cout << new_data[i];

        if (i != n-1)
        {
            cout << " ";
        }
    }

    cout << endl;
}