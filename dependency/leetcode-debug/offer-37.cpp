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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:

    //this method have a space question, because it stores the complete binary tree (with null)
    // Encodes a tree to a single string, like what it presents in leetcode
    string serialize_like_what_it_presents(TreeNode* root) {
        if(!root) return "";

        int max_id = 0;
        unordered_map<TreeNode*, int> id_map;

        id_map[root] = 0;

        function<void(TreeNode*)> dfs = [&](TreeNode* node) -> void
        {
            if(!node) return;

            if(node->left)
            {
                id_map[node->left] = 2 * id_map[node] + 1;
                max_id = max(max_id, id_map[node->left]);
            }

            if(node->right)
            {
                id_map[node->right] = 2 * id_map[node] + 2;
                max_id = max(max_id, id_map[node->right]);
            }

            dfs(node->left);
            dfs(node->right);

        };

        dfs(root);

        vector<string> data;
        data.resize(max_id+1, "null");

        for (auto idp : id_map)
        {
            auto node = idp.first;
            int id = idp.second;

            if(node)
            {
                data[id] = to_string(node->val);
            }
        }

        string res;

        for (int i = 0; i < data.size() - 1; ++i)
        {
            res += data[i];
            res += ",";
        }

        res += data.back();

        return res;
    }
    // Decodes your encoded data to tree, like what it presents in leetcode
    TreeNode* deserialize_like_what_it_presents(string data) {

        int n = data.size();

        if(n == 0) return nullptr;

        vector<string> nodes;

        for (int i = 0; i < n;)
        {
            int right = i;

            while(right < n && data[right] != ',')
            {
                right++;
            }

            nodes.push_back(data.substr(i, right - i));

            i = right + 1;
        }

        TreeNode* head;

        unordered_map<int, TreeNode*> node_map;

        for (int i = 0; i < nodes.size(); ++i)
        {
            TreeNode* cur;
            if(i == 0)
            {
                cur = new TreeNode(stoi(nodes[i]));
                head = cur;
                node_map[i] = cur;
            }
            else if (nodes[i] == "null")
            {
                continue;
            }
            else
            {
                cur = new TreeNode(stoi(nodes[i]));
                node_map[i] = cur;

                int father_id = (i + 1) / 2 - 1;

                if(i % 2 == 0)
                {
                    node_map[father_id]->right = cur;
                }
                else
                {
                    node_map[father_id]->left = cur;
                }
            }
        }

        return head;
    }

    
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offer-37.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    //REGISTER(serialize)
    REGISTER(deserialize_like_what_it_presents)

    exc.run();
}