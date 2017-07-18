## 简介
链表相关的算法题和自己的理解
## 1、复杂链表的复制（剑指Offer）
复杂链表除了有一个next指针以外，每个节点还存在一个指向任意节点的sbling指针
### 思路分析
链表的复制比较简单，这题的难点在于复制链表的时候如何快速的定位sbling指针，剑指Offer上给出了一种比较好的解决方法，如下：
- 首先在原有链表的基础上复制每个节点，当前节点的next指针都是该节点的副本。
- 同样依据原有链表的基础上，初始化新构造节点的sbling指针，也就是原节点sbling指针的下一个位置。
- 拆分这两个链表
### 关键代码分析
```
LinkNode * cpoy_complex_linklist(LinkNode * head) {
  /* 在原有链表的基础上，clone每个节点 */
  clone_node(head);
  /* 初始化新节点的sbling指针 */
  init_sbling(head);
  /* 拆分链表 */
  return split_link(head);
}

void int_sbling(LinkNode * head) {
  LinkNode * pre = head;
  LinkNode * p = head->next;
  while (p) {
    if (pre->sbling != NULL) {
      p->sbling = pre->sbling->next;
    }
    pre = pre->next;
    p = p->next;
  }
}
```
时间复杂度是 O(n)
***
## 2、两个链表的第一个公共节点
求两个单链表的第一个公共节点
### 分析
因为单链表只有一个next节点，所以如果出现了公共节点，那么从公共节点往后的所有节点都是相同的，所以比较好的解决办法是从链表的尾部分别开始扫描两个链表，最后一个相同的节点即是链表第一个公共的节点。
### 关键代码
```
class Solution {
  public:
  ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
    if (pHead1 == NULL || pHead2 == NULL) {
      return NULL;
    }

    stack<ListNode *> S1;
    stack<ListNode *> S2;

    while (pHead1) {
      S1.push(pHead1);
      pHead1 = pHead1->next;
    }

    while (pHead2) {
      S2.push(pHead2);
      pHead2 = pHead2->next;
    }

    ListNode * result = NULL;
    while (!S1.empty() && !S2.empty()) {
      if (S1.top() == S2.top()) {
        result = S1.top();
        S1.pop();
        S2.pop();
      } else {
        break;
      }
    }

    return result;
  }
};
```
***
## 3、链表的倒数第k个节点
求一个单链表倒数第k个节点
### 分析
求倒数第k个节点的话，可以使用两个指针，两个指针的间隔是k，最后一个指针走到最后的时候，前一个指针所指向的就是倒数第k个节点
### 关键代码
```
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if (pListHead == NULL || k == 0) {
            return NULL;
        }

        ListNode * pre = pListHead;
        ListNode * ptr = pListHead;
        int i = 0;

        for (i = 0; i < k; i++) {
            if (ptr == NULL) {
                return NULL;
            }
            ptr = ptr->next;
        }

        while (ptr != NULL) {
            ptr = ptr->next;
            pre = pre->next;
        }
        return pre;
    }
};
```
