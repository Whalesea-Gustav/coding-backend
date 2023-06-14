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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

        int n = preorder.size();

        if (n == 0) return nullptr;

        unordered_map<int, int> pos2_map;

        int m = inorder.size();

        for (int i = 0; i < m; ++i)
        {
            pos2_map[inorder[i]] = i;
        }

        function<TreeNode*(int, int, int)> build = [&](int root_pos1, int left, int right) -> TreeNode* {
            if(left > right)
            {
                return nullptr;
            }

            if(left == right)
            {
                return new TreeNode(preorder[root_pos1]);
            }

            TreeNode* root = new TreeNode(preorder[root_pos1]);

            int root_pos2 = pos2_map[preorder[root_pos1]];


            int left_root = root_pos1 + 1;
            int right_root = root_pos1 + root_pos2 - left;

            root->left = build(left_root, left, root_pos2-1);
            root->right = build(right_root, root_pos2+1, right);

            return root;
        };

        return build(0, 0, n-1);
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offer-07.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(buildTree)

    exc.run();
}