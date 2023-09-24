//
// Created by whalesea on 2023/5/15.
//

#include <bits/stdc++.h>

using namespace std;



int main() {

    int n;
    cin >> n;

    vector<int> key(n);

    for (int i = 0; i < n; ++i)
    {
        key[i] = i + 1;
    }

    priority_queue<int, vector<int>, greater<int>> pq;


    int j = 0;

    for (int i = 1; i <= n; ++i)
    {
        int data;
        cin >> data;

        pq.push(data);

        while(j < n && key[j] == pq.top())
        {
            j++;
            pq.pop();
            cout << i << " ";
        }
    }
}
