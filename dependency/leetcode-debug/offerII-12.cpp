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
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        vector<int> dir = {-1, 0, 1, 0, -1};

        function<bool(int, int, int)> dfs = [&] (int x, int y, int id) -> bool
        {
            if(x >= m || x < 0) return false;
            if(y >= n || y < 0) return false;

            if(id >= word.size()) return true;

            if(visited[x][y]) return false;

            visited[x][y] = true;
            if(board[x][y] != word[id]) return false;

            bool bValid = false;

            for(int d = 0; d < 4; ++d)
            {
                int next_x = x + dir[d];
                int next_y = y + dir[d];

                bValid = bValid || dfs(next_x, next_y, id+1);
            }

            visited[x][y] = false;
            return bValid;
        };

        function<bool(int, int, int)> dfs2 = [&](int x, int y, int id) -> bool

        {
            if(id >= word.size()) return true;

            if(board[x][y] != word[id]) return false;

            if(id == word.size()-1) return true;

            visited[x][y] = true;

            bool bValid = false;

            for(int d = 0; d < 4; ++d)
            {
                int next_x = x + dir[d];
                int next_y = y + dir[d+1];

                if(next_x >= m || next_x < 0) continue;
                if(next_y >= n || next_y < 0) continue;

                if(visited[next_x][next_y]) continue;

                if(board[next_x][next_y] != word[id+1]) continue;

                bValid = bValid || dfs2(next_x, next_y, id+1);
            }

            visited[x][y] = false;
            return bValid;
        };

        bool bValid = false;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if(board[i][j] != word[0]) continue;
                bValid = bValid || dfs2(i, j, 0);
                if(bValid) break;
            }

            if(bValid) break;
        }

        return bValid;
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offerII-12.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(exist)

    exc.run();
}