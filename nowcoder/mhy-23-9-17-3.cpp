#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;

#define DEBUG

#if defined(DEBUG) && defined(GJY_SYSTEM)
#define MY_LOG(x) x
#else
#define MY_LOG(x)
#endif

int main() {
    int n, m;

    cin >> n >> m;

    int odd, even;

    if(n % 2 == 0)
    {
        odd = n / 2;
        even = n / 2;
    }
    else {
        even = n / 2;
        odd = even + 1;
    }

    vector<pair<int, int>> odd_card;
    vector<pair<int, int>> even_card;
    for (int i = 0; i < n; ++i)
    {
        int id, x, y;
        cin >> id >> x >> y;

        if(id == 1)
        {
            odd_card.push_back({x, y});
        }
        else if(id == 2)
        {
            even_card.push_back({x, y});
        }
    }

    int damage = 0;

    if(odd_card.size() > odd)
    {
        sort(odd_card.begin(), odd_card.end(), [&](pair<int,int>& a, pair<int,int>& b) -> bool { return a.second > b.second;});

        for (int i = 0; i < odd; ++i)
        {
            damage += odd_card[i].first + odd_card[i].second;
        }

        for (int i = odd; i < odd_card.size(); ++i)
        {
            damage += odd_card[i].first;
        }

        for (int i = 0; i < even_card.size(); ++i)
        {
            damage += even_card[i].first;
        }
    }
    else if (even_card.size() > even)
    {
        sort(even_card.begin(), even_card.end(), [&](pair<int,int>& a, pair<int,int>& b) -> bool { return a.second > b.second;});

        for (int i = 0; i < even; ++i)
        {
            damage += even_card[i].first + even_card[i].second;
        }

        for (int i = even; i < even_card.size(); ++i)
        {
            damage += even_card[i].first;
        }

        for (int i = 0; i < odd_card.size(); ++i)
        {
            damage += odd_card[i].first;
        }
    }
    else {
        for (int i = 0; i < odd_card.size(); ++i)
        {
            damage += odd_card[i].first + odd_card[i].second;
        }
        for (int i = 0; i < even_card.size(); ++i)
        {
            damage += even_card[i].first + even_card[i].second;
        }
    }

    cout <<damage << endl;
}