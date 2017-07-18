class Solution {
public:
    int TreeDepth(TreeNode* pRoot)
    {
        if (pRoot == NULL) {
            return 0;
        }

        if (pRoot->left == NULL || pRoot->right == NULL) {
            return 1;
        }

        return 1 + max(TreeDepth(pRoot->left), TreeDepth(pRoot->right));
    }
};
