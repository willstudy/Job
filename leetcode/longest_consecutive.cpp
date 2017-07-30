class Solution {
    public:
        int longestConsecutive(const vector<int> &nums) {
            unordered_map<int, bool> used;
            int size_num = nums.size();
            for (int i = 0; i < size_num; i++) {
                used[nums[i]] = false;
            }
            int longest = 0;
            for (int i = 0; i < size_num; i++) {
                if (used[nums[i]]) continue;

                int length = 1;
                for (int next = nums[i] + 1; used.find(next) != used.end(); next++) {
                    used[next] = true;
                    length++;
                }

                for (int pre = nums[i] - 1; used.find(pre) != used.end(); pre--) {
                    used[pre] = true;
                    length++;
                }

                longest = max(longest, length);
            } 
            return longest;
        }
};
