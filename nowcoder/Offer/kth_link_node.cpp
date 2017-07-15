/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};*/
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
