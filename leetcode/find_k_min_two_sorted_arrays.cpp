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
