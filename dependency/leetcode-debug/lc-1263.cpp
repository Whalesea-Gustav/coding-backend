#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    struct Coord
    {
        int x;
        int y;
    };

    struct State
    {
        Coord p;
        Coord b;
        int step;
    };

    int dir[5] = {-1, 0, 1, 0, -1};

    int minPushBox(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        Coord p_start;
        Coord b_start;
        Coord Term;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if(grid[i][j] == 'S')
                {
                    p_start = {i, j};
                }

                if(grid[i][j] == 'B')
                {
                    b_start = {i, j};
                }

                if(grid[i][j] == 'T')
                {
                    Term = {i, j};
                }

            }
        }

        //search b surrounding position

        auto is_top = [](Coord& p, Coord& b) -> bool
        {
            if (p.x == b.x - 1 && p.y == b.y)
            {
                return true;
            }

            return false;
        };

        auto is_bottom = [](Coord& p, Coord& b) -> bool
        {
            if (p.x == b.x + 1 && p.y == b.y)
            {
                return true;
            }

            return false;
        };

        auto is_right = [](Coord& p, Coord& b) -> bool
        {
            if (p.x == b.x && p.y == b.y + 1)
            {
                return true;
            }

            return false;
        };

        auto is_left = [](Coord& p, Coord& b) -> bool
        {
            if (p.x == b.x && p.y == b.y - 1)
            {
                return true;
            }

            return false;
        };

        auto is_valid = [&](Coord& pos) -> bool
        {
            if (pos.x < 0 || pos.x >= m) return false;
            if (pos.y < 0 || pos.y >= n) return false;
            if (grid[pos.x][pos.y] == '#') return false;

            return true;
        };

        auto search_dir = [&](Coord& p, Coord& b) -> array<int,4>
        {
            array<int, 4> res = {0, 0, 0, 0};

            queue<Coord> mq;

            mq.push(p);

            vector<vector<bool>> visited(m, vector<bool>(n, false));

            while(!mq.empty())
            {
                Coord cur_p = mq.front();
                mq.pop();
                if (visited[cur_p.x][cur_p.y]) continue;

                res[0] = res[0] || is_bottom(cur_p, b);
                res[1] = res[1] || is_top(cur_p, b);
                res[2] = res[2] || is_right(cur_p, b);
                res[3] = res[3] || is_left(cur_p, b);

                visited[cur_p.x][cur_p.y] = true;

                for (int d = 0; d < 4; ++d)
                {
                    Coord tmp_p;

                    tmp_p.x = cur_p.x + dir[d];
                    tmp_p.y = cur_p.y + dir[d + 1];

                    if (is_valid(tmp_p) && !(tmp_p.x == b.x && tmp_p.y == b.y) && !visited[tmp_p.x][tmp_p.y])
                    {
                        mq.push(tmp_p);
                    }
                };
            }

            return res;
        };


        State state_start = { p_start, b_start, 0};

        queue<State> state_queue;

        state_queue.push(state_start);

        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(4, false)));

        while(!state_queue.empty())
        {
            State cur_state = state_queue.front();
            state_queue.pop();

            Coord& cur_p = cur_state.p;
            Coord& cur_b = cur_state.b;
            int cur_step = cur_state.step;

            if (cur_b.x == Term.x && cur_b.y == Term.y) return cur_step;

            array<int, 4> future_dir = search_dir(cur_p, cur_b);

            for (int d = 0; d < 4; ++ d)
            {
                if (future_dir[d] && !visited[cur_b.x][cur_b.y][d])
                {
                    visited[cur_b.x][cur_b.y][d] = true;
                    State fur_state;
                    Coord next_b;
                    int dx = 0, dy = 0;

                    if (d == 0) dx = -1;
                    if (d == 1) dx = 1;
                    if (d == 2) dy = -1;
                    if (d == 3) dy = 1;
                    next_b.x = cur_b.x + dx;
                    next_b.y = cur_b.y + dy;
                    if (is_valid(next_b))
                    {
                        fur_state.p = cur_b;
                        fur_state.b = next_b;
                        fur_state.step = cur_step + 1;
                        state_queue.push(fur_state);
                    }
                }
            }
        }

        return -1;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-1263.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(minPushBox)

    exc.run();
}