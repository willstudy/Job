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
***
## 7、求二叉树的深度
给定一颗二叉树就其深度
### 分析
二叉树的深度是根节点到叶子节点最长的一条路径，本题有两种解法：
- 一种是层次遍历时，没遍历一层即树的深度加1
- 递归遍历左右子树，左右子树的深度的较大者加1，即为二叉树的深度
### 关键代码分析
```
class Solution {
public:
    int TreeDepth(TreeNode* pRoot)
    {
        if (pRoot == NULL) {
            return 0;
        }

        return 1 + max(TreeDepth(pRoot->left), TreeDepth(pRoot->right));
    }
};
```
***
## 8、判断一棵树是否是平衡二叉树
平衡二叉树的特点是左右子树的高度之差不超过2
### 分析
这道题简单的做法是分别求出该节点的左右子树的高度，判断高度之差是否大于1，这种做法会导致某些节点被遍历多次，时间复杂度为O(n^2)。另外一种比较好的做法是先分别求出左右子树的高度，然后在此基础上求父节点的高度，在求的过程中来判断是否满足平衡二叉树，时间复杂度为O(n)。
### 关键代码
```
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
```
***
## 9、求二叉树两个节点的最低公共祖先
### 分析
1、这一题需要先判断是否是二叉搜索树，如果是二叉搜索树：
- 从根节点遍历，如果两个节点的值都大于跟节点，那么公共祖先在右子树
- 如果都小于根节点的话，那么公共祖先在左子树
- 反之根节点就是最低的公共祖先
详情解法一

2、如果不是二叉搜索树，且有指向父节点的指针，那么求最低的公共祖先，可以转换成求两个链表的公共节点（通过压栈弹栈的方式）

3、如果是普通的二叉树，首先遍历的时候分别保存根节点到两个节点的路径，然后转换成求两个链表公共节点的问题

这里只给出情况3的解法
### 关键代码
```
/* 保存根节点到两个节点的路径 */
bool GetNodePath(TreeNode* pHead, TreeNode* pNode, std::list<TreeNode*>& path)
{
    if(pHead == pNode)
        return true;
 
    path.push_back(pHead);
 
    bool found = false;
    if(pHead->m_pLeft != NULL)
        found = GetNodePath(pHead->m_pLeft, pNode, path);
    if(!found && pHead->m_pRight)
        found = GetNodePath(pHead->m_pRight, pNode, path);
	/* 没找到的话，就弹出来 */
    if(!found)
        path.pop_back();
 
    return found;
}
/* 求两个路径的公共节点 */
TreeNode* LastCommonNode
(
    const std::list<TreeNode*>& path1,
    const std::list<TreeNode*>& path2
)
{
    std::list<TreeNode*>::const_iterator iterator1 = path1.begin();
    std::list<TreeNode*>::const_iterator iterator2 = path2.begin();
   
    TreeNode* pLast = NULL;
 
    while(iterator1 != path1.end() && iterator2 != path2.end())
    {
        if(*iterator1 == *iterator2)
            pLast = *iterator1;
 
        iterator1++;
        iterator2++;
    }
 
    return pLast;
}
```
***
## 10、判断一颗树是否是左右对称的
一棵树对称的判断是，它的左孩子等于右孩子的（值也相同）
### 分析
这一题有两种做法，递归的做法是将树分成左右子树看待，完全的比较左右子树。非递归的做法是通过两个队列的形式，判断每一层次的遍历队列的首尾元素是否相同。
### 关键代码
```
/* 递归版本 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return symmetric(root, root);
    }

private:
    bool symmetric(TreeNode* left, TreeNode* right) {
        if (left == NULL && right == NULL) {
            return true;
        } else if (left && right && left->val == right->val) {
           return symmetric(left->left, right->right) &&
              symmetric(left->right, right->left); 
        } else {
            return false;
        }
    }
};

/* 非递归版本 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) {
            return true;
        }

        queue<TreeNode*> Q;

        Q.push(root->left);
        Q.push(root->right);

        while (!Q.empty()) {
            TreeNode *node1 = Q.front();
            Q.pop();
            TreeNode *node2 = Q.front();
            Q.pop();

            if (node1 == NULL && node2 == NULL) continue;
            if (node1 == NULL || node2 == NULL) return false;
            if (node1 && node2 && node1->val != node2->val) {
                return false;
            }

            Q.push(node1->left);
            Q.push(node2->right);
            Q.push(node1->right);
            Q.push(node2->left);
        }

        return true;
    }
};
```