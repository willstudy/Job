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
    bool isSymmetric(TreeNode* root) {
        return symmetric(root, root);
    }

private:
    bool symmetric(TreeNode* left, TreeNode* right) {
        if (left == NULL && right == NULL) {
            return true;
        } else if (left && right && left->val == right->val) {
           return symmetric(left->left, right->right) &&
              symmetric(left->right, right->left); 
        } else {
            return false;
        }
    }
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) {
            return true;
        }

        queue<TreeNode*> Q;

        Q.push(root->left);
        Q.push(root->right);

        while (!Q.empty()) {
            TreeNode *node1 = Q.front();
            Q.pop();
            TreeNode *node2 = Q.front();
            Q.pop();

            if (node1 == NULL && node2 == NULL) continue;
            if (node1 == NULL || node2 == NULL) return false;
            if (node1 && node2 && node1->val != node2->val) {
                return false;
            }

            Q.push(node1->left);
            Q.push(node2->right);
            Q.push(node1->right);
            Q.push(node2->left);
        }

        return true;
    }
};
