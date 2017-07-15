class Solution {
    public:
        vector<string> Permutation(string str) {
            vector<string> result;
            unordered_set<string> uni_str;

            int len = str.size();
            if (len < 1) {
                return result;
            }

            permutation(str, 0, len, result, uni_str);
            return result;
        }
    private:
        void permutation(string str, int begin, int end, vector<string> &result, unordered_set<string> &uni_str) {
            if (begin == end) {
                /* 保证每次的输出，都是唯一的 */
                if (uni_str.find(str) == uni_str.end()) {
                    uni_str.insert(str);
                    result.push_back(str);
                }
            } else {
                sort(str.begin()+begin, str.end());
                for (int i = begin; i < end; i++) {
                    char c = str[begin];
                    str[begin] = str[i];
                    str[i] = c;

                    permutation(str, begin+1, end, result);

                    char ch = str[begin];
                    str[begin] = str[i];
                    str[i] = ch;
                }
            }
        }

};
