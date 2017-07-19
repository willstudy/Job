class Solution {
public:
    void reverse_str(string &str, int left, int right) {
        int size = str.size();

        while (left < right) {
            char ch = str[left];
            str[left] = str[right];
            str[right] = ch;

            left++;
            right--;
        }
    }
    string ReverseSentence(string str) {
        int size = str.size();

        if (size < 2) {
            return str;
        } 

        string result(str);
        reverse_str(result, 0, size - 1);

        int left = 0;
        int right = 1;

        while (left < size && right < size) {
            while (result[left] == ' ' && left < size) {
                left++;
            }
            right = left+1;
            while (result[right] != ' ' && right < size) {
                right++;
            }
            reverse_str(result, left, right-1);
            left = right+1;
        }

        return result;
    }
};
