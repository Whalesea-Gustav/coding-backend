#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<TreeNode*> res;

        unordered_set<int> to_delete_set = {to_delete.begin(), to_delete.end()};

        function<TreeNode*(TreeNode*)> post_iter = [&](TreeNode* node) -> TreeNode*
        {
            if(node == nullptr) return nullptr;

            TreeNode* left = post_iter(node->left);
            TreeNode* right = post_iter(node->right);

            if(to_delete_set.count(node->val) > 0)
            {
                if(left) res.push_back(left);
                if(right) res.push_back(right);
                return nullptr;
            }

            node->left = left;
            node->right = right;

            return node;
        };

        auto node = post_iter(root);

        if(node) res.push_back(node);

        return res;
    }


};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-1110.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(delNodes)

    exc.run();
}