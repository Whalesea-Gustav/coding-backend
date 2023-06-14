#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

namespace std
{
    template<>
    struct hash<pair<int, int>>
    {
        size_t operator()(pair<int, int> const & t) const
        {
            size_t h1 = hash<int>()(t.first);
            size_t h2 = hash<int>{}(t.second);
            return h1 ^ (h2 << 1);
        }
    };
}

using namespace std;

class Solution {
public:
    struct pos
    {
        int x,  y;
    };

    int movingCount(int m, int n, int k) {
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        vector<int> dir = {-1, 0, 1, 0, -1};

        queue<pos> q;

        q.push({0, 0});
        int count = 0;

        while(!q.empty())
        {
            pos p = q.front();
            q.pop();

            //一定要在队列pop处加入visited判断
            if(visited[p.x][p.y]) continue;

            visited[p.x][p.y] = true;
            count++;

            for(int d = 0; d < 4; ++d)
            {
                int next_x = p.x + dir[d];
                int next_y = p.y + dir[d+1];

                if(next_x >= m || next_x < 0) continue;
                if(next_y >= n || next_y < 0) continue;

                //在队列push处判断，会有一些已经进入队列
                //但是还没被标记为visited的位置
                //被重复加入队列
                if(visited[next_x][next_y]) continue;

                pos next = {next_x, next_y};

                if(isValid(next, k))
                {
                    q.push(next);
                }
            }
        }

        return count;
    }


    bool isValid(pos p, int k)
    {
        int v = 0;

        int x = p.x;

        while(x)
        {
            v += x % 10;
            x = x / 10;
        }

        x = p.y;

        while(x)
        {
            v += x % 10;
            x = x / 10;
        }

        if(v <= k) return true;
        return false;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offerII-13.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(movingCount)

    exc.run();
}