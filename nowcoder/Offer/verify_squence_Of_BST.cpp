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
            result = result && isLastOrder(sequence, index);
        }
        if (index < len - 1) {
            result = result && isLastOrder(sequence+index, len-index- 1); 
        }

        return true;
    }
};

