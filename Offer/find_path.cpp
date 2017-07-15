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
    private:
        vector<vector<int> > result;
    public:
        vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
            vector<int> path;
            if (root == NULL) {
                return result;
            }

            int currentSum = 0;
            return FindPathWithCurrentSum(root, expectNumber, currentSum, path);
        }

        vector<vector<int> > FindPathWithCurrentSum(
                TreeNode* root, int expectNumber, 
                int currentSum, vector<int> &path) {
            path.push_back(root->val);
            currentSum += root->val;
            if (root->left == NULL && root->right == NULL && currentSum == expectNumber) {
                result.push_back(path);
            }
            if (currentSum < expectNumber && root->left) {
                FindPathWithCurrentSum(root->left, expectNumber, currentSum, path);
            }
            if (currentSum < expectNumber && root->right) {
                FindPathWithCurrentSum(root->right, expectNumber, currentSum, path);
            }

            path.pop_back();
            currentSum -= root->val;
        }
};
