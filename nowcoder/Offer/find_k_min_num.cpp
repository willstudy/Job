class Solution {
private:
    int partition(vector<int> input, int begin, int end) {
        int i = begin - 1;
        int priot = result[end-1];
        
        for (int j = begin; j < end-1; j++) {
            if (result[j] < priot) {
                i++;
                int val = result[j];
                result[j] = result[i];
                result[i] = result[j];
            }
        }
        int val = result[i+1];
        result[i+1] = priot;
        result[end-1] = val;
        return i+1;
    }
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> result;
        int len = input.size();

        if (len < 1 || k < 1) {
            return result;
        }

        int index = partition(input, 0, len);
        while(index != k-1) {
            if (index > k-1) {
                index = partition(input, 0, index-1);
            } else {
                index = partition(input, index+1, len);
            }
        }

        for (int i = 0; i < k; i++) {
            result.push_back(input[i]);
        }

        return result;
    }
};
