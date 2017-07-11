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
    public:
        TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
            int preNum = pre.size();
            int vinNum = vin.size();
            
            if (preNum == 0 || vinNum == 0) {
                return NULL;
            }

            int root_value = pre[0];
            int index = 0;
            TreeNode * node = new TreeNode(root_value);

            for (int i = 0; i < vinNum; i++) {
                if (vin[i] == root_value) {
                    break;
                }
                index++;
            }

            if (index == 0) {
                node->left = NULL;
            } else {
                vector<int> leftPre(pre.begin()+1, pre.begin()+1+index);
                vector<int> leftVin(vin.begin(), vin.begin()+index);
                node->left = reConstructBinaryTree(leftPre, leftVin);
            }

            if (index == (vinNum - 1)) {
                node->right = NULL;
            } else {
                vector<int> rightPre(pre.begin()+1+index, pre.end());
                vector<int> rightVin(vin.begin()+index+1, vin.end());
                node->right = reConstructBinaryTree(rightPre, rightVin);
            }

            return node;
        }
};
