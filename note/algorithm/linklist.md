### 简介
链表相关的算法题和自己的理解
### 复杂链表的复制（剑指Offer）
复杂链表除了有一个next指针以外，每个节点还存在一个指向任意节点的sbling指针
#### 分析
链表的复制比较简单，这题的难点在于复制链表的时候如何快速的定位sbling指针，剑指Offer上给出了一种比较好的解决方法，如下：
- 首先在原有链表的基础上复制每个节点，当前节点的next指针都是该节点的副本。
- 同样依据原有链表的基础上，初始化新构造节点的sbling指针，也就是原节点sbling指针的下一个位置。
- 拆分这两个链表
#### 关键代码分析
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
####
时间复杂度是 O(n)
