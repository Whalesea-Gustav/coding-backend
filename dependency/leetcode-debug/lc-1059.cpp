#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        // 1.从起点出发的所有路径都必须可以到达终点
        // 2.有向图
        // 3.考虑从终点开始反向拓扑序
        vector<vector<int>> g(n);
        vector<int> indeg(n,0);

        for(auto& e:edges){
            int a = e[0],b = e[1];
            g[b].push_back(a);
            indeg[a] ++;
        }

        if(indeg[destination]) return false;

        queue<int> q;
        q.push(destination);

        while(q.size()){
            auto u = q.front();
            if(u == source) return true;
            q.pop();
            for(auto& ne:g[u]){
                if(--indeg[ne] == 0){
                    q.push(ne);
                }
            }
        }

        return false;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-1059.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(leadsToDestination)

    exc.run();
}