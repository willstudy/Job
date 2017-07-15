### 简介
字符串相关的算法题和自己的理解
### 字符串的全排列（剑指Offer）
给定一个字符串，求字符串的所有排列组合。
#### 分析
n个字符串的全排列可以看作：第一个元素与其余n-1个元素的全排列组合。
#### 关键代码分析
```
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

        void permutation(string str, int begin, int end, vector<string> &result, unordered_set<string> &uni_str) {
                    if (begin == end-1) {
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
```
非递归的实现方式，可以通过字典排序生成算法。核心思想有两个：
1、判断字符串是否还有后继（字典生成的最后一个排列是每个字符从大到小排列的）
2、找到当前字符串的后继排列（后继是比当前排列大但是最小的那个）
具体做法是：
1、首先将字符串或者数字从小到大排序
2、从后往前找第一个a[i] > a[i-1] 的元素的下标为 i
3、从 i + 1 开始，从前往后找第一个比 a[i-1] 大的元素，下标为 k
4、交换 a[i-1] 和 a[k] 的位置
5、对 a[i] 之后的元素进行从小到大排序
```
vector<vector<int> > permutation(vector<int> &array[]) {
    vector<vector<int> > result;
    int len = array.size();
    int index = len-1;
    int i, k;

    while (true) {
        for (i = len-1; i >= 1; i--) {
          /* 从后往前找第一个a[i] > a[i-1] 的元素的下标为 i */
            if (array[i] > array[i-1]) {
                index = i;
                break;
            }
        }
        if (i == 0) break;
        /* 从 i + 1 开始，从前往后找第一个比 a[i-1] 大的元素，下标为 k */
        for (int k = i+1; k < len; k++) {
            if (array[k] > array[index-1]) {
                break;
            }
        }
        /* 交换 a[i-1] 和 a[k] 的位置 */
        int value = array[index-1];
        array[index-1] = array[k];
        array[k] = value;
        /* 对 a[i] 之后的元素进行从小到大排序 */
        sort(array.begin()+index, array.end());
        result.push_back(array);
    }
    return result;
}
```
