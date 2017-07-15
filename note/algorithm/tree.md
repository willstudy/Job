## 简介
树相关的算法题以及自己的理解

## 二叉树中和为某一值的路径（剑指Offer）
### 分析
剑指Offer上的路径指的是从根节点到叶子节点的路径，这一点比较重要。关键做法是**从根节点开始，分别累加左右子树的值，如果左右子树为叶子节点的话，且累加值符合条件的话，把路径加进去，否则的话弹出这个节点的值**。
### 关键代码
```
private vector<vector<int> > result;
vector<vector<int> > find_path(TreeNode * root, int expect_num, int current_num, vector<int> &path) {
  /* 累加这个值 */
  path.push_back(root->val);
  current_num += root->val;
  /* 判断是否是符合要求的一条路径 */
  if  (root->left == NULL && root->right == NULL && current_num == expect_num) {
    result.push_back(path);
  }

  /* 分别累加左右子树 */
  if (current_num < expect_num) {
    if (root->left) {
      find_path(root->left, expect_num, current_num, path);
    }
    if (root->right) {
      find_path(root->right, expect_num, current_num, path);
    }
  }
  /* 弹出最后一个节点的值 */
  path.pop_back();
  current_num -= root->val;
}
```
### 时间复杂度
最好情况是O(n)，最坏情况是O(nlogn)

## 二叉搜索树转有序双向链表（剑指Offer）
将一颗二叉搜索树转成一个双向链表，左子数指向双向链表的前驱，右子数指向双向链表的后继。
### 分析
因为一颗二叉搜索树中序遍历是有序的，所以
- 最简单的做法是将二叉搜索树中序遍历后的节点放进一个vector中，然后遍历vector构造双向链表（在牛客网上会超出运行内存）
- 非递归的做法是中序遍历二叉搜索树，记录前一个遍历节点的值和首节点的值，每次遍历的时候构造left和right指针。
### 关键代码分析
```
/* 非递归版本 */
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


/* 递归解法 */
TreeNode* Convert(TreeNode* pRootOfTree) {
            if (pRootOfTree == NULL) {
                return NULL;
            }

            if (pRootOfTree->left == NULL && pRootOfTree->right == NULL) {
                return pRootOfTree;
            }
            /* 转换左子树，返回的是最左节点，需要找到最大的节点 */
            TreeNode *left = Convert(pRootOfTree->left);
            TreeNode *p = left;
            while (left && p->right) {
                p = p->right;
            }

            if (left != NULL) {
                p->right = pRootOfTree;
                pRootOfTree->left = p;
            }
            /* 转换右子树找到最小节点 */
            TreeNode *right = Convert(pRootOfTree->right);
            if (right != NULL) {
                pRootOfTree->right = right;
                right->left = pRootOfTree;
            }
            /* 返回最小的节点 */
            return left == NULL ? pRootOfTree:left;
        }
```
