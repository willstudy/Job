class Solution {
public:
    int threeSumClosest(vector<int &nums, int target>) {
        int result = 0;
        int size = nums.size();
        int min_gap = INT_MAX;

        if (size < 4) {
            for (int i = 0; i < size; i++) {
                result += nums[i];
            }
            return result;
        }

        sort(nums.begin(), nums.end());

        for (i = 0; i < size - 2; i++) {
            int next = i + 1;
            int last = size - 1;

            while (b < c) {
                int sum = nums[i] + nums[next] + nums[last]; 
                int gap = abs(sum - target);
                if (gap < min_gap) {
                    result = sum;
                    min_gap = gap;
                }
                if (sum == target) {
                    return result;
                } else if (sum < target) {
                    next++;
                } else {
                    latest--;
                }
            }
        }
    }
};
