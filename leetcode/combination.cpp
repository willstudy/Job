class Solution {
public:
    /* 求字符串的所有组合 */
    vector<string> Combination(string str) {
        int size = str.size();
        if (size < 2) {
            return str;
        }

        vector<string> result;
        for (int i = 1; i <= size; i++) {
            /* 从str中取i个元素的组合 */
            combination_str(str, i, result);
        }
        return result; 
    }

    void combination_str(string str, int num, vector<string> &result) {
        if (num == 0 || str.size() < 1) {
            return;
        }

        result.push_back(str);
        string str1(str);
        /* 加入到当前组合 */
        combination_str(str1, num-1, result);

        result.pop_back();
        string str2(str.begin()+1, str.end());
        /* 不加入到当前组合 */
        combination_str(str2, num, result);
    }
};
