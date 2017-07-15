/**
  * Definition for binary tree
  * struct TreeNode {
  *     int val;
  *     TreeNode *left;
  *     TreeNode *right;
  *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  * };
  */

class Solution {
    /* 递归做法 */
    public void preorder(TreeNode * T, vector<int> &result) {
        if (T == NULL) {
            return;
        }
        result.push_back(T->value);
        preorder(T->left, result);
        preorder(T->right, result);
    }

    /* 非递归做法 */
    public void preorder(TreeNode * T, vector<int> &result) {
        if (T == NULL) {
            return;
        }

        stack<TreeNode *> S;
        TreeNode * node = S.top();
        S.pop();

        while (!S.empty() || node) {
            while (node) {
                result.push_back(node->value);
                S.push(node);
                node = node->left;
            }
            S.pop();
            node = S.top();
            node = node->right;
        }
    }
};
