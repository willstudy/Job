class Solution {
public:
    bool bit_is_set(int num, int index) {
        num = num >> index;
        return num & 1;
    }
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        int size = data.size();
        if (size < 2) {
            return;
        }

        int OXR = 0;
        for (int i = 0; i < size; i++) {
            OXR ^= data[i];
        }

        /* 求OXR二进制中最右边为1的位 */
        int index = 0;
        while ((OXR & 1) == 0) {
            OXR = OXR >> 1;
            index++;
        }

        *num1 = 0;
        *num2 = 0;
        for (int i = 0; i < size; i++) {
            if (bit_is_set(data[i], index)) {
                *num1 ^= data[i];
            } else {
                *num2 ^= data[i];
            }
        }
    }
};
