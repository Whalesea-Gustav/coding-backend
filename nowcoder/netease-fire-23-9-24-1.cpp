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
    int n;

    cin >> n;

    string ta;
    string tb;

    cin >> ta >> tb;

    unordered_map<string, int> playerScore;
    unordered_map<string, int> teamScore;
    int max_score = 0;
    vector<string> mvp_players;
    string mvp_player;

    for (int i = 0; i < n; ++i)
    {
        string name, team;
        int score;

        cin >> name >> team;
        cin >> score;

        playerScore[name] += score;
        teamScore[team] += score;

        if(playerScore[name] > max_score)
        {
            max_score = playerScore[name];
            mvp_player = name;
        }
    }

    if(teamScore[ta] == teamScore[tb])
    {
        cout << "ended in a draw" << endl;
    }
    else if(teamScore[ta] > teamScore[tb])
    {
        cout << ta << endl;
    }
    else
    {
        cout << tb << endl;
    }

    cout << mvp_player << endl;
}
