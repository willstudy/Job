## 简介
树相关的算法题以及自己的理解

## 1、二叉树中和为某一值的路径（剑指Offer）
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
***
## 2、二叉搜索树转有序双向链表（剑指Offer）
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
***

## 3、二叉树的镜像
将一颗二叉树转成它的镜像树形式
### 分析
二叉树的镜像树的形式是左右孩子均相互交换了位置，可以通过树的层次遍历来交换每层节点的左右孩子的位置。
### 关键代码分析
```
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
```
***
## 4、重建二叉树
根据树的先序遍历和中序遍历还原二叉树
### 分析
先序遍历的第一个节点是根节点，而对于中序遍历来说根节点左边的值都属于左子树，根节点右边的值都属于右子树，所以依据这个属性可以递归的构造二叉树。
### 关键代码分析
```
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
				/* 找到根节点在中序遍历中的位置 */
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
				/* 构造左子树 */
                node->left = reConstructBinaryTree(leftPre, leftVin);
            }

            if (index == (vinNum - 1)) {
                node->right = NULL;
            } else {
                vector<int> rightPre(pre.begin()+1+index, pre.end());
                vector<int> rightVin(vin.begin()+index+1, vin.end());
				/* 构造右子树 */
                node->right = reConstructBinaryTree(rightPre, rightVin);
            }

            return node;
        }
};
```
***
## 5、二叉树的子树
判断一颗二叉树是否是另一颗二叉树的子树
### 分析
首先从二叉树A中找到一个与二叉树B根节点相同的节点，然后分别判断A的左右孩子是否与B的相同，如果相同的话那么B就是A的子树。这一题用递归的方法更为的简单
### 关键代码
```
class Solution {
public:
    bool HasSubTree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if (pRoot1 == NULL || pRoot2 == NULL) {
            return false;
        }

        bool result = false;
		/* 找到一个节点是相同的 */
        if (pRoot1->value == pRoot2->value) {
			/* 从此节点开始判断是否是子树 */
            result = DoesHasSubTree(pRoot1, pRoot2);
        }
		/* 不是子树的话，再从左子树开始查找 */
        if (result != true) {
            result = HasSubTree(pRoot1->left, pRoot2);
        }
		/* 不是子树的话，再从右子树开始查找 */
        if (result != true) {
            result = HasSubTree(pRoot1->right, pRoot2);
        }

        return result;
    }
	/* 判断一棵树是否是另一颗的子树 */
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
```
***
## 6、后序遍历判断是否是二叉搜索树
给定二叉树一个后序遍历的结果，判断该二叉树是否是二叉搜索树。
### 分析
由于二叉搜索树的根节点一定大于其左子树，小于其右子树，所以只要根据根节点的位置，来判断左右孩子遍历的情况，一旦不满足根节点大于左孩子，小于右孩子，就不是二叉搜索树。
### 关键代码
```
class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        int node_num = sequence.size();
        if (node_num == 0) {
            return false;
        }

        return isLastOrder((int *)&sequence[0], node_num);
    }

private:
    bool isLastOrder(int sequence[], int len) {

        if (sequence == NULL || len < 0) {
            return false;
        } 

        int root_value = sequence[len - 1];
        int index = 0;

        for (; index < len-1; index++) {
            if (sequence[index] > root_value) {
                break;
            }
        }

        for (int i = index; i < len; i++) {
            if (sequence[i] < root_value) {
                return false;
            }
        }

        bool result = true;
        if (index >= 1) {
			/* 继续判断左孩子 */
            result = result && isLastOrder(sequence, index);
        }
        if (index < len - 1) {
			/* 继续判断右孩子 */
            result = result && isLastOrder(sequence+index, len-index- 1); 
        }

        return true;
    }
};
```