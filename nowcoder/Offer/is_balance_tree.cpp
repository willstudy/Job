class Solution {
public:
    /* 通过求左右子树的高度来判断是否是平衡二叉树 */
    int DepthTree(TreeNode* pRoot) {
        if (pRoot == NULL) {
            return 0;
        }

        return 1 + max(DepthTree(pRoot->left), DepthTree(pRoot->right));
    }
    bool IsBalanced_Solution(TreeNode* pRoot) {
        if (pRoot == NULL) {
            return true;
        }

        if (!IsBalanced_Solution(pRoot->left) || !IsBalanced_Solution(pRoot->right)) {
            return false;
        }

        int left = DepthTree(pRoot->left);
        int right = DepthTree(pRoot->right);
        int diff = left - right;

        if (diff > 1 || diff < -1) {
            return false;
        }
        
        return true; 
    }

    /* 通过后序遍历判断树是否为平衡二叉树，每次遍历的时候记录下该节点的深度 */
    bool IsBalanced_Solution(TreeNode* pRoot) {
        int depth = 0;
        return balance_tree(pRoot, depth);
    }

    bool balance_tree(TreeNode * pRoot, int &depth) {
        if (pRoot == NULL) {
            depth = 0;
            return true;
        }

        int left, right;
        if (balance_tree(pRoot->left, left) && balance_tree(pRoot->right, right)) {
            int diff = left - right;
            if (diff > 1 || diff < -1) {
                return false;
            }
            depth = 1 + max(left, right);
            return true;
        }

        return false;
    }
};
