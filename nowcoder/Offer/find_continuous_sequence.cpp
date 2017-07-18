class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int> > result;
        if (sum < 2) {
            return result;
        }

        int left = 1;
        int right = 2;
        int end = (sum + 1) >> 1;

        while (right <= end) {
            int N = 0;
            for (int i = left; i <= right; i++) {
                N += i;
            }
            if (N < sum) {
                right++;
            } else if (N > sum) {
                left++;
            } else {
                vector<int> temp;
                for (int i = left; i <= right; i++) {
                    temp.push_back(i);
                }
                result.push_back(temp);
                left++;
            }
        }
        return result;
    }
};
