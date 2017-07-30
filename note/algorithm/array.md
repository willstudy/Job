## 简介
这个是数组相关类型的算法题目
## 1、找出两个排序后的数据第k个最小的数
有两个排序好的数组，求在两个数组中第k个最小的数，时间复杂度要求是O(lg(m+n))
### 分析
简单的做法是将这两个数组合并排序好之后求第k个数字，这样的时间复杂度度是O(m+n)。另一种做法是分别对两个数组进行二分查找，以此降低时间复杂度。

假设两个数组的长度都大于 k 的情况：
- A[k/2] > B[k/2] ：那么第 k 小的数字一定不在 B[0 ~ k/2] 之间
- A[k/2] < B[k/2] ：那么第 k 小的数字一定不在 A[0 ~ k/2] 之间
- A[k/2] = B[k/2] ：那么 A[k/2] 就是第 k 小的数字
### 关键代码
```
class Solution {
    public:
        double findKthSortedArrays(const vector<int>& A, const vector<int>& B) {
            const int size_A = A.size();
            const int size_B = B.size();
            int size_total = size_A + size_B;

            if (size_total & 1) {
                return find_kth(A.begin(), size_A, B.begin(), size_B, size_total / 2 + 1);
            } else {
                return (find_kth(A.begin(), size_A, B.begin(), size_B, size_total / 2) 
                        + find_kth(A.begin(), size_A, B.begin(), size_B, size_total / 2 + 1)) / 2.0;
            }
        }
    private:
        double find_kth(vector<int>::const_iterator A, int size_A, 
                vector<int>::const_iterator B, int size_B, int k) {
            // size_A should be less than size_B
            if (size_A > size_B) return find_kth(B, size_B, A, size_A, k);
            if (size_A == 0) return *(B + k - 1);
            if (k == 1) return min(*A, *B);

            // the k/2 in array A
            int index_A = min(k/2, size_A);
            int index_B = size_B - index_A;
            if (*(A + index_A - 1) < *(B + index_B - 1)) {
                return find_kth(A + index_A, size_A - index_A, B, size_B, k - index_A);
            } else if (*(A + index_A - 1) > *(B + index_B - 1)) {
                return find_kth(A, size_A, B + index_B, size_B - index_B, k - index_B);
            } else {
                return *(A + index_A - 1);
            }
        }
};
```
## 2、求一个未排序数组中数字连续的最长序列
给定一个未排序的数组，求这个数组中连续数字的最长序列长度，比如给定数组： [200, 4, 201, 3, 2, 1] 结果是 4 最长的连续序列是 [1, 2, 3, 4]
### 分析
通过排序算法可以O(nlgn)时间复杂度解决这个问题，如果想要O(n)时间复杂度解决这个问题的话，需要借助辅助空间，标记数组中每个数字的使用情况，然后以这个数为起点往左和往右查找连续的序列，时间复杂度是O(n)，空间复杂度是O(n)
### 关键代码
```
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
```
## 3、求数组中三个数和最接近的目标值的数
给定一个未排序的数组和一个目标值，求这个数组中三个数的和最接近目标值的数。举例数组 S = {-1 2 1 -4} target = 1，那么和最接近 2 的三个数为（-1 + 2 + 1）= 2
### 分析
先把数组排序，然后遍历每一个数字，对剩下的数字利用左右逼近求两个数的和为target的方法，时间复杂度为O(n^2)，空间复杂度为O(1)
### 关键代码
```
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
```