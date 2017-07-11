/*
struct TreeNode {
int value;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};*/
class Solution {
public:
    bool HasSubTree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if (pRoot1 == NULL || pRoot2 == NULL) {
            return false;
        }

        bool result = false;
        if (pRoot1->value == pRoot2->value) {
            result = DoesHasSubTree(pRoot1, pRoot2);
        }

        if (result != true) {
            result = HasSubTree(pRoot1->left, pRoot2);
        }

        if (result != true) {
            result = HasSubTree(pRoot1->right, pRoot2);
        }

        return result;
    }

    bool DoesHasSubTree(TreeNode * pRoot1, TreeNode * pRoot2) {
        if (pRoot2 == NULL) {
            return true;
        }

        if (pRoot1 == NULL) {
            return false;
        }

        if (pRoot1->value != pRoot2->value) {
            return false;
        }

        return DoesHasSubTree(pRoot1->left, pRoot2->left) &&
            DoesHasSubTree(pRoot1->right, pRoot2->right);
    }
};
