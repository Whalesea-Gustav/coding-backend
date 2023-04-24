#include <bits/stdc++.h>

using namespace std;



int main() {


    int C, N;

    cin >> C >> N;

    //当前无人机数量
    int cur_C = C;

    queue<int> cq;
    vector<int> dispatch_command(N);

    int prev_re_id = -1;
    vector<int> re_command(N);

    priority_queue<int, vector<int>, greater<int>> rc_pq;

    unordered_map<int, int> order_hash;
    int real_order = 0;

    for (int i = 0; i < N; ++i)
    {
        int a, b;
        cin >> a >> b;

        //派遣
        if (a >= 0)
        {
            //a: 命令id， b派遣无人机个数
            dispatch_command[a] = b;
            int dispatch_num = 0;
            if (cur_C >= b)
            {
                dispatch_num = b;
                cur_C -= b;
                order_hash[a] = real_order++;
            }
            else
            {
                if (cur_C == C)
                {
                    //扩容操作
                    dispatch_num = b;
                    C = b;
                    cur_C = 0;
                    order_hash[a] = real_order++;
                }
                else
                {
                    //派遣失败
                    //记录失败的命令
                    cq.push(a);
                }
            }

            cout << dispatch_num << endl;
        }
        else
        //回收
        {
            int re_id = b;
            int real_re_id = order_hash[b];

            if (prev_re_id + 1 == real_re_id)
            {
                //立刻执行回收命令

                int re_num = dispatch_command[re_id];
                cur_C += re_num;

                prev_re_id = real_re_id;
                //遍历rc_pq
                while(!rc_pq.empty())
                {
                    int front_ele = rc_pq.top();

                    if (front_ele == prev_re_id + 1)
                    {
                        rc_pq.pop();
                        int local_id = front_ele;
                        int local_num = dispatch_command[local_id];
                        cur_C += local_num;
                        prev_re_id = front_ele;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                //加入rc_pq
                rc_pq.push(real_re_id);
            }

            int dispatch_num = 0;

            while(!cq.empty())
            {
                auto c_id = cq.front();
                int dispatch_C = dispatch_command[c_id];
                if (dispatch_C > cur_C)
                {
                    if (cur_C != C)
                    {
                        break;
                    }
                }

                cq.pop();

                if (dispatch_C <= cur_C)
                {
                    dispatch_num += dispatch_C;
                    cur_C -= dispatch_C;
                }
                else
                {
                    if (cur_C == C)
                    {
                        C = dispatch_C;
                        cur_C = 0;
                        dispatch_num += dispatch_C;
                    }
                }
            }

            cout << dispatch_num << endl;
        }
    }

    return 0;
}
