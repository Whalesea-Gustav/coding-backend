#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;

struct follower
{
    int ATK;
    int HP;
    bool bTaunt;
    bool bShield;
};

struct hpdata
{
    bool HP;
    bool bShield;
};

int calcCost(vector<vector<int>>& hp_data, bool free)
{
    int cur_cost = free ? 0 : 2;
    bool b_cur_free = false;

    bool bFinish = true;

    for (int i = 0; i < hp_data.size(); ++i)
    {
        if(hp_data[i][0] > 0)
        {
            bFinish = false;
        }
    }

    if (bFinish) return 0;

    for (int i = 0; i < hp_data.size(); ++i)
    {
        if(hp_data[i][1] == 1)
        {
            hp_data[i][1] = 0;
        }
        else
        {
            hp_data[i][0] -= 1;
            if (hp_data[i][0] == 0)
            {
                b_cur_free = true;
            }
        }
    }

    return cur_cost + calcCost(hp_data, b_cur_free);
}

int calc_cost(vector<follower>& data, bool free)
{
    bool bFinish = true;

    for (int i = 0; i < data.size(); ++i)
    {
        if(data[i].HP > 0)
        {
            bFinish = false;
        }
    }

    if(bFinish) return 0;

    int cost = free ? 0 : 2;
    int cur_free = false;

    for (int i = 0; i < data.size(); ++i)
    {
        if(data[i].bShield)
        {
            data[i].bShield = false;
        }
        else
        {
            data[i].HP -= 1;
            if (data[i].HP == 0)
            {
                cur_free = true;
            }
        }
    }

    return cost + calc_cost(data, cur_free);
}

int main() {

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t)
    {
        int n;
        cin >> n;

        int enemy_count = n;

        vector<follower> enemy(n);

        auto generate_follower = [](string& s) -> follower
        {
            bool bShield = false;
            bool bTaunt = false;
            int ATK, HP;

            int end = s.size() - 1;
            if (s.back() == '!')
            {
                bTaunt = true;
                --end;
            }

            int start = 0;
            int sep_pos = s.find_first_of('/', 0);


            if(s[0] == '(')
            {
                bShield = true;
                ++start;
                string ATK_s = s.substr(start, sep_pos - start);
                string HP_s = s.substr(sep_pos+1, end-sep_pos-1);
                ATK = stoi(ATK_s);
                HP = stoi(HP_s);
            }
            else
            {
                bShield = false;
                string ATK_s = s.substr(start, sep_pos - start);
                string HP_s = s.substr(sep_pos+1, end-sep_pos);
                ATK = stoi(ATK_s);
                HP = stoi(HP_s);
            }

            follower f;
            f.ATK = ATK;
            f.HP = HP;
            f.bShield = bShield;
            f.bTaunt = bTaunt;

            return f;
        };

        for (int i = 0; i < n; ++i)
        {

            string enemy_string;
            cin >> enemy_string;

            auto f = generate_follower(enemy_string);

            enemy[i] = f;
        }

        cin >> n;

        int ally_count = n;

        vector<follower> ally(n);

        for (int i = 0; i < ally_count; ++i)
        {
           string ally_string;
           cin >> ally_string;

           auto f = generate_follower(ally_string);

           ally[i] = f;
        }


        int cost = 8;

        vector<follower> all_follower = enemy;
        all_follower.insert(all_follower.end(), ally.begin(), ally.end());

        //从ally中选择两个随从进行攻击, 有顺序

        vector<unordered_set<int>> all_attacker;
        for (int i = 0; i < ally_count; ++i)
        {
            for (int j = 0; j < ally_count; ++j)
            {
                unordered_set<int> attacker;

                attacker.insert(i);
                attacker.insert(j);

                all_attacker.push_back(attacker);
            }
        }

        vector<unordered_set<int>> all_receiver;
        for (int i = 0; i < enemy_count; ++i)
        {

            for (int j = 0; j < enemy_count; ++j)
            {
                unordered_set<int> receivers;
                receivers.insert(i);
                receivers.insert(j);
                all_receiver.push_back(receivers);
            }
        }

        for (auto attackers : all_attacker)
        {
            for (auto receivers : all_receiver)
            {
                vector<follower> copy_followers = all_follower;

                if(attackers.size() != receivers.size()) continue;
                int local_sz = attackers.size();

                vector<int> attackers_vec = {attackers.begin(), attackers.end()};
                vector<int> receivers_vec = {receivers.begin(), receivers.end()};

                bool bLegal = true;

                for (int i = 0; i < local_sz; ++i)
                {
                    int attacker_id = attackers_vec[i];
                    int receiver_id = receivers_vec[i];

                    if (!enemy[receiver_id].bTaunt)
                    {
                        for(int e_id = 0; e_id < enemy_count; ++e_id)
                        {
                            //是否存在其他活着的嘲讽单位
                            if (enemy[e_id].bTaunt && enemy[e_id].HP > 0)
                            {
                                bLegal = false;
                            }
                        }
                    }

                    if (enemy[receiver_id].HP <= 0)
                    {
                        bLegal = false;
                    }

                    if (ally[attacker_id].ATK <= 0 || ally[attacker_id].HP <= 0)
                    {
                        bLegal = false;
                    }

                    if(bLegal)
                    {
                        attacker_id = enemy_count + attacker_id;

                        auto& ally_info = copy_followers[attacker_id];

                        auto& enemy_info = copy_followers[receiver_id];

                        if(ally_info.bShield)
                        {
                            ally_info.bShield = false;
                        }
                        else
                        {
                            ally_info.HP -= enemy_info.ATK;
                        }

                        if(enemy_info.bShield)
                        {
                            enemy_info.bShield = false;
                        }
                        else
                        {
                            enemy_info.HP -= ally_info.ATK;
                        }
                    }
                }

                if(bLegal)
                {
                     cost = min(cost, calc_cost(copy_followers, false));
                }
            }
        }

        cost = min(cost, calc_cost(all_follower, false));

        cout << cost << endl;
    }

    return 0;
}
