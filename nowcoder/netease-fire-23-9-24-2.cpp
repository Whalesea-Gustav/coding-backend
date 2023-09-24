#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;

#define DEBUG

#if defined(DEBUG) && defined(GJY_SYSTEM)
#define MY_LOG(x) x
#else
#define MY_LOG(x)
#endif

struct Player
{
    double x, y;
    int buff;
    int region;
    unordered_set<int> grass;
};

vector<Player> players;

double distSqr(Player player, double x, double y)
{
    return (x - player.x) * (x - player.x) + (y - player.y) * (y - player.y);
}

bool inRec(Player player, double xmin, double ymin, double xmax, double ymax)
{
    double x = player.x;
    double y = player.y;

    if(x >= xmin && x <= xmax)
    {
        if(y >= ymin && y <= ymax)
        {
            return true;
        }
    }

    return false;
}

int main() {
    int n, m, q;

    cin >> n >> m >> q;

    for (int i = 0; i < n; ++i)
    {
        double x, y;
        int buff, region;

        cin >> x >> y;
        cin >> buff >> region;

        players.push_back({x, y, buff, region});
    }

    //grass id
    for (int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if(type == 0)
        {
            double cx, cy, cr;
            cin >> cx >> cy >> cr;

            for (auto& player : players)
            {
                if(distSqr(player, cx, cy) <= cr * cr)
                {
                    player.grass.insert(i);
                }
            }
        }
        else if (type == 1)
        {
            double xmin = 1000000, ymin = 1000000, xmax = -1000000, ymax = -1000000;

            for (int j = 0; j < 4; ++j)
            {
                double recx, recy;
                cin >> recx >> recy;

                xmin = min(xmin, recx);
                ymin = min(ymin, recy);

                xmax = max(xmax, recx);
                ymax = max(ymax, recy);
            }

            for (auto& player : players)
            {
                if(inRec(player, xmin, ymin, xmax, ymax))
                {
                    player.grass.insert(i);
                }
            }
        }
    }

    //query
    vector<vector<int>> query;

    for (int i = 0; i < q; ++i)
    {
        int id1, id2;
        cin >> id1 >> id2;
        query.push_back({id1, id2});
    }

    for (int i = 0; i < q; ++i)
    {
        int id1, id2;

        id1 = query[i][0] - 1;
        id2 = query[i][1] - 1;

        auto& player1 = players[id1];
        auto& player2 = players[id2];

        //buff
        if(player2.buff)
        {
            cout << 0 << endl;
        }
        else
        {
            //检查阵营
            if(player1.region == player2.region)
            {
                cout << 1 << endl;
            }
            else
            {
                if(player2.grass.empty())
                {
                    cout << 1 << endl;
                }
                else
                {
                    bool bGrass = false;
                    for (auto grass_id : player2.grass)
                    {
                        if(player1.grass.count(grass_id) > 0)
                        {
                            bGrass = true;
                            cout << 1 << endl;
                            break;
                        }
                    }
                    if(!bGrass) cout << 0 << endl;
                }
            }
        }
    }
}
