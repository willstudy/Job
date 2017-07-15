/*
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};*/
class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if (pRootOfTree == NULL) {
            return NULL;
        }

        if (pRootOfTree->left == NULL && pRootOfTree->right == NULL) {
            return pRootOfTree;
        }

        TreeNode *left = Convert(pRootOfTree->left);
        TreeNode *p = left;
        while (left && p->right) {
            p = p->right;
        }

        if (left != NULL) {
            p->right = pRootOfTree;
            pRootOfTree->left = p;
        }

        TreeNode *right = Convert(pRootOfTree->right);
        if (right != NULL) {
            pRootOfTree->right = right;
            right->left = pRootOfTree;
        }

        return left == NULL ? pRootOfTree:left;
    }
};

