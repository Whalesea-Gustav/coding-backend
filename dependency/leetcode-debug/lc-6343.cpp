#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

namespace std
{
    template<>
    struct hash<pair<int, int>>
    {
        std::size_t operator()(pair<int, int> const& s) const noexcept
        {
            std::size_t h1 = std::hash<int>{}(s.first);
            std::size_t h2 = std::hash<int>{}(s.second);
            return h1 ^ (h2 << 1); // or use boost::hash_combine
        }
    };
}

class Solution {
public:

    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        unordered_map<pair<int, int>, vector<int>> indices;

        int special_min_cost = 1e6;

        for (int i = 0; i < specialRoads.size(); ++i)
        {

            special_min_cost = min(special_min_cost, specialRoads[i][4]);

            int x = specialRoads[i][2];
            int y = specialRoads[i][3];
            pair<int,int> key = {x, y};
            indices[key].push_back(i);
        }

        auto dist_to = [](int x1, int y1, int x2, int y2) -> int
        {
            return abs(x1 - x2) + abs(y1 - y2);
        };

        auto one_step = [&](int x, int y) -> int
        {
            int min_dist = 1e6;

            for (int i = 0; i < specialRoads.size(); ++i)
            {
                int end_x = specialRoads[i][2];
                int end_y = specialRoads[i][3];
                int cost = specialRoads[i][4];

                min_dist = min(min_dist, dist_to(x,y,end_x,end_y) + cost);
            }

            return min_dist;
        };

        vector<int> visited(specialRoads.size(), false);

        function<int(int, int)> dfs = [&](int x, int y) -> int
        {

            if(x == start[0] && y == start[1]) return 0;

            int min_dist = abs(x - start[0]) + abs(y - start[1]);

            if (min_dist <= one_step(x, y)) return min_dist;

            for (int i = 0; i < specialRoads.size(); ++i)
            {
                if(visited[i] == true) continue;

                int start_x = specialRoads[i][0];
                int start_y = specialRoads[i][1];
                int end_x = specialRoads[i][2];
                int end_y = specialRoads[i][3];
                int cost = specialRoads[i][4];
                visited[i] = true;
                min_dist = min(min_dist, dist_to(x,y,end_x,end_y) + cost + dfs(start_x, start_y));
                visited[i] = false;
            }

            return min_dist;
        };

        return dfs(target[0], target[1]);

    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-6343.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(minimumCost)

    exc.run();
}