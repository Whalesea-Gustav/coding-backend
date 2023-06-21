#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    constexpr static const int dirs[8][2] = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    int flipChess(vector<string>& chessboard) {
        int m = chessboard.size();
        int n = chessboard[0].size();

        auto isValid = [m=m,n=n](int x, int y) -> bool
        {
            if (x >= m || x < 0) return false;
            if (y >= n || y < 0) return false;

            return true;
        };


        auto judge_dir = [isValid=isValid](const vector<string> chessboard, int x, int y, int dx, int dy) -> int
        {
            while(isValid(x, y))
            {
                if(chessboard[x][y] == 'O')
                {
                    x += dx;
                    y += dy;
                }
                else if (chessboard[x][y] == 'X')
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            return false;
        };

        int count = 0;

        auto bfs = [judge_dir=judge_dir, isValid=isValid](vector<string> chessboard, int x, int y) -> int
        {
            queue<pair<int,int>> q;

            q.push({x,y});

            int cur_count = 0;

            chessboard[x][y] = 'X';

            while(!q.empty())
            {
                auto[nx, ny] = q.front();
                q.pop();

                for (int d = 0; d < 8; ++d)
                {
                    int dx = dirs[d][0];
                    int dy = dirs[d][1];

                    int fx = nx + dx, fy = ny + dy;

                    if(judge_dir(chessboard, fx, fy, dx, dy))
                    {
                        while(isValid(fx, fy))
                        {
                            if(chessboard[fx][fy] == 'X')
                            {
                                break;
                            }
                            else if (chessboard[fx][fy] == 'O')
                            {
                                chessboard[fx][fy] = 'X';
                                q.push({fx, fy});
                                cur_count++;
                                fx += dx;
                                fy += dy;
                            }
                        }
                    }
                }
            }

            return cur_count;
        };

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if(chessboard[i][j] == '.')
                {
                    count = max(count, bfs(chessboard, i,j));
                }
            }
        }

        return count;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "LSP-41.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(flipChess)

    exc.run();
}