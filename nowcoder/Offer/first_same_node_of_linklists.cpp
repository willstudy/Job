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
