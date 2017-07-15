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

            stack<TreeNode *> S;
            TreeNode * p = pRootOfTree;
            TreeNode * pre = pRootOfTree;
            TreeNode * first = NULL;

            while (p || !S.empty()) {
                while (p) {
                    S.push(p);
                    p = p->left;
                }

                S.pop();
                p = S.top();
                if (first == NULL) {
                    first = p;
                } else {
                    pre->right = p;
                    p->left = pre;
                }
                pre = p;
                p = p->right;
            }

            return first;
        }
};
