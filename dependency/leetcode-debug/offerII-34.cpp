#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:

    vector<vector<int>> dfs_method(TreeNode* root, int target)
    {
        vector<vector<int>> res;
        vector<int> path;

        function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int left) -> void
        {

            if(node == nullptr) return;

            left = left - node->val;

            //if(left < 0) return;

            path.push_back(node->val);

            if(left == 0 && !node->left && !node->right)
            {
                res.push_back(path);
            }
            else
            {
                if(node->left) dfs(node->left, left);
                if(node->right) dfs(node->right, left);
            }

            path.pop_back();
        };

        dfs(root, target);

        return res;
    }

    vector<vector<int>> bfs_method(TreeNode* root, int target)
    {
        vector<vector<int>> res;
        if(!root) return res;

        unordered_map<TreeNode*, TreeNode*> father_map;

        queue<pair<TreeNode*, int>> q;

        q.push({root, target});

        vector<TreeNode*> node_res;

        while(!q.empty())
        {
            auto [node, val] = move(q.front());
            q.pop();

            int left = val - node->val;

            if(left == 0 && !node->left && !node->right)
            {
                node_res.push_back(node);
            }

            if(node->left)
            {
                father_map[node->left] = node;
                q.push({node->left, left});
            }

            if(node->right)
            {
                father_map[node->right] = node;
                q.push({node->right, left});
            }
        }



        for (auto son : node_res)
        {
            vector<int> path;

            TreeNode* iter = son;

            while(iter)
            {
                path.push_back(iter->val);

                iter = father_map[iter];
            }

            res.push_back({path.rbegin(), path.rend()});
        }

        return res;
    }

    vector<vector<int>> pathSum(TreeNode* root, int target) {
        return bfs_method(root, target);
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offerII-34.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(pathSum)

    exc.run();
}