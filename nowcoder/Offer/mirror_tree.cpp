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
        void Mirror(TreeNode *pRoot) {
            if (pRoot == NULL) {
                return;
            }

            queue<TreeNode *> Q;
            Q.push(pRoot);

            while(!Q.empty()) {
                int size = Q.size();
                for (int i = 0; i < size; i++) {
                    TreeNode * node = Q.front();
                    if (node->left != NULL) {
                        Q.push(node->left);
                    } 
                    if (node->right != NULL) {
                        Q.push(node->right);
                    }
                    TreeNode * temp = node->left;
                    node->left = node->right;
                    node->right = temp;
                    Q.pop();
                }
            }
        }
};
