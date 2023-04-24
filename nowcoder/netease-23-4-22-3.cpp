#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;

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


int main() {

    int T;
    cin >> T;
    
    for (int t = 0; t < T; ++t)
    {
        int n;
        cin >> n;
        
        vector<vector<int>> enemy(n);
        
        for (int i = 0; i < n; ++i)
        {
            bool bSD = false;
            bool bCF = false;
            int ATK = 0, HP = 0;

            string enemy_string;
            cin >> enemy_string;

            if (enemy_string.back() == '!')
            {
                bCF = true;
            }

            if (enemy_string[0] == '(')
            {
                bSD = true;
                ATK = enemy_string[1] - '0';
                if (enemy_string[2] == '/')
                {
                    HP = enemy_string[3] - '0';
                    if (enemy_string[4] != ')')
                    {
                        HP = 10;
                    }
                }
                else //[3] = '/'
                {
                    ATK = 10;
                    HP = enemy_string[4] - '0';
                    if (enemy_string[5] != ')')
                    {
                        HP = 10;
                    }
                }
            }
            else
            {
                ATK = enemy_string[0] - '0';

                if (enemy_string[1] != '/')
                {
                    ATK = 10;
                    HP = enemy_string[3] - '0';
                    if(enemy_string.size() >= 5 && enemy_string[4] != '!')
                    {
                        HP = 10;
                    }
                }
                else
                {
                    HP = enemy_string[2] - '0';
                    if (enemy_string.size() >= 4 && enemy_string[3] != '!')
                    {
                        HP = 10;
                    }
                }
            }

            enemy[i] = {ATK, HP, bSD, bCF};
        }

        cin >> n;

        vector<vector<int>> partner(n);

        for (int i = 0; i < n; ++i)
        {
            bool bSD = false;
            bool bCF = false;
            int ATK = 0, HP = 0;


            string enemy_string;
            cin >> enemy_string;

            if (enemy_string.back() == '!')
            {
                bCF = true;
            }

            if (enemy_string[0] == '(')
            {
                bSD = true;
                ATK = enemy_string[1] - '0';
                if (enemy_string[2] == '/')
                {
                    HP = enemy_string[3] - '0';
                    if (enemy_string[4] != ')')
                    {
                        HP = 10;
                    }
                }
                else //[3] = '/'
                {
                    ATK = 10;
                    HP = enemy_string[4] - '0';
                    if (enemy_string[5] != ')')
                    {
                        HP = 10;
                    }
                }
            }
            else
            {
                ATK = enemy_string[0] - '0';

                if (enemy_string[1] != '/')
                {
                    ATK = 10;
                    HP = enemy_string[3] - '0';
                    if(enemy_string.size() >= 5 && enemy_string[4] != '!')
                    {
                        HP = 10;
                    }
                }
                else
                {
                    HP = enemy_string[2] - '0';
                    if (enemy_string.size() >= 4 && enemy_string[3] != '!')
                    {
                        HP = 10;
                    }
                }
            }

            partner[i] = {ATK, HP, bSD, bCF};
        }

        //read finish, calculate min cost
        int cost = 8;

        int e_count = enemy.size();
        int p_count = partner.size();

        vector<vector<int>> hp_data(e_count + p_count);

        for (int i = 0; i < e_count; ++i)
        {
            hp_data[i] = {enemy[i][1], enemy[i][2]};
        }

        for (int i = 0; i < p_count; ++i) {
            hp_data[e_count + i] = {partner[i][1], partner[i][2]};
        }

        //从partner中选择两个单位进行攻击
        if (partner.size() == 1)
        {

            if (partner[0][0] != 0)
            {
                vector<int> enemy_cf;
                for (int e = 0; e < enemy.size(); ++e)
                {
                    auto e_data = enemy[e];
                    if (e_data[3])
                    {
                        enemy_cf.push_back(e);
                    }
                }


                if (!enemy_cf.empty())
                {
                    //选择嘲讽敌人进行攻击
                    for (auto e_id : enemy_cf)
                    {
                        vector<vector<int>> copy_hp_data = hp_data;
                        if(copy_hp_data[e_count][1] == 1)
                        {
                            copy_hp_data[e_count][1] = 0;
                        }
                        else
                        {
                            copy_hp_data[e_count][0] -= enemy[e_id][0];
                        }
                        if(copy_hp_data[e_id][1] == 1)
                        {
                            copy_hp_data[e_id][1] = 0;
                        }
                        else
                        {
                            copy_hp_data[e_id][0] -= partner[0][0];
                        }

                        //验证需要多少cost
                        cost = min(cost, calcCost(copy_hp_data, false));
                    }
                }
                else
                {
                    //选择敌人进行攻击
                    //选择嘲讽敌人进行攻击
                    for (int e_id = 0; e_id < enemy.size(); ++e_id)
                    {
                        vector<vector<int>> copy_hp_data = hp_data;
                        if(copy_hp_data[e_count][1] == 1)
                        {
                            copy_hp_data[e_count][1] = 0;
                        }
                        else
                        {
                            copy_hp_data[e_count][0] -= enemy[e_id][0];
                        }

                        if(copy_hp_data[e_id][1] == 1)
                        {
                            copy_hp_data[e_id][1] = 0;
                        }
                        else
                        {
                            copy_hp_data[e_id][0] -= partner[0][0];
                        }

                        //验证需要多少cost
                        cost = min(cost, calcCost(copy_hp_data, false));
                    }
                }
            }
            else
            {
                vector<vector<int>> copy_hp_data = hp_data;
                cost = min(cost, calcCost(copy_hp_data, false));
            }
        }
        else if(partner.empty())
        {
            vector<vector<int>> copy_hp_data = hp_data;
            cost = min(cost, calcCost(copy_hp_data, false));
        }
        else
        {
            vector<int> enemy_cf;
            for (int e = 0; e < enemy.size(); ++e)
            {
                auto e_data = enemy[e];
                if (e_data[3])
                {
                    enemy_cf.push_back(e);
                }
            }

            for (int p1 = 0; p1 < partner.size(); ++p1)
            {
                vector<vector<int>> copy_hp_data = hp_data;

                if (partner[p1][0] != 0)
                {
                    if (!enemy_cf.empty())
                    {
                        //选择嘲讽敌人进行攻击
                        for (auto e_id : enemy_cf)
                        {
                            if(copy_hp_data[e_count + p1][1] == 1)
                            {
                                copy_hp_data[e_count + p1][1] = 0;
                            }
                            else
                            {
                                copy_hp_data[e_count + p1][0] -= enemy[e_id][0];
                            }
                            if(copy_hp_data[e_id][1] == 1)
                            {
                                copy_hp_data[e_id][1] = 0;
                            }
                            else
                            {
                                copy_hp_data[e_id][0] -= partner[p1][0];
                            }
                        }
                    }
                    else
                    {
                        //选择敌人进行攻击
                        //选择嘲讽敌人进行攻击
                        for (int e_id = 0; e_id < enemy.size(); ++e_id)
                        {
                            if(copy_hp_data[e_count][1] == 1)
                            {
                                copy_hp_data[e_count][1] = 0;
                            }
                            else
                            {
                                copy_hp_data[e_count][0] -= enemy[e_id][0];
                            }

                            if(copy_hp_data[e_id][1] == 1)
                            {
                                copy_hp_data[e_id][1] = 0;
                            }
                            else
                            {
                                copy_hp_data[e_id][0] -= partner[p1][0];
                            }
                        }
                    }
                }
                else
                {
                    continue;
                }

                for (int p2 = p1; p2 < partner.size(); ++p2)
                {
                    vector<vector<int>> copy2_hp_data = copy_hp_data;
                    if (partner[p2][0] != 0)
                    {
                        bool bNotAttack = true;
                        if (!enemy_cf.empty())
                        {
                            //选择嘲讽敌人进行攻击
                            for (auto e_id : enemy_cf)
                            {
                                if(copy2_hp_data[e_id][0] <= 0) continue;

                                bNotAttack = false;

                                if(copy2_hp_data[e_count+p2][1] == 1)
                                {
                                    copy2_hp_data[e_count+p2][1] = 0;
                                }
                                else
                                {
                                    copy2_hp_data[e_count+p2][0] -= enemy[e_id][0];
                                }
                                if(copy_hp_data[e_id][1] == 1)
                                {
                                    copy2_hp_data[e_id][1] = 0;
                                }
                                else
                                {
                                    copy2_hp_data[e_id][0] -= partner[p2][0];
                                }
                            }
                        }

                        if(bNotAttack)
                        {
                            //选择敌人进行攻击
                            //选择嘲讽敌人进行攻击
                            for (int e_id = 0; e_id < enemy.size(); ++e_id)
                            {
                                if(copy2_hp_data[e_id][0] <= 0) continue;
                                if(copy2_hp_data[e_count][1] == 1)
                                {
                                    copy2_hp_data[e_count][1] = 0;
                                }
                                else
                                {
                                    copy2_hp_data[e_count][0] -= enemy[e_id][0];
                                }

                                if(copy2_hp_data[e_id][1] == 1)
                                {
                                    copy2_hp_data[e_id][1] = 0;
                                }
                                else
                                {
                                    copy2_hp_data[e_id][0] -= partner[p2][0];
                                }
                            }
                        }

                        cost = min(cost, calcCost(copy2_hp_data, false));
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }

        cout << cost << endl;
    }

    return 0;
}
