## 简介
字符串相关的算法题和自己的理解
## 1、字符串的全排列（剑指Offer）
给定一个字符串，求字符串的所有排列组合。
### 分析
n个字符串的全排列可以看作：第一个元素与其余n-1个元素的全排列组合。
### 关键代码分析
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

void permutation(string str, int begin, int end,
  vector<string> &result, unordered_set<string> &uni_str) {
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
- 1、判断字符串是否还有后继（字典生成的最后一个排列是每个字符从大到小排列的）
- 2、找到当前字符串的后继排列（后继是比当前排列大但是最小的那个）
具体做法是：
- 1、首先将字符串或者数字从小到大排序
- 2、从后往前找第一个a[i] > a[i-1] 的元素的下标为 i
- 3、从 i + 1 开始，从前往后找第一个比 a[i-1] 大的元素，下标为 k
- 4、交换 a[i-1] 和 a[k] 的位置
- 5、对 a[i] 之后的元素进行从小到大排序
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
***
## 2、数组中的数字排成最小的一个数
给定一个整型数组A[]，求组合成一个最小的数的一个排列
### 分析
数组由A0~An组成，排成最小数的排列一定是当前数和剩下的所有数排成最小的排列，那么就可以分别求A0、A1的排列后的[A1A0]排列，然后求[A1A0]排列组成的数字与剩下的A1+之后的数字组成的最小排列。考虑到大数问题，两种不同排列数字的大小可以通过字符串的比较来完成。
### 关键代码
```
class Solution {
public:
  static bool compare_str(string a, string b) {
      string c = a + b;
      string d = b + a;
      return c < d;
    }

  string PrintMinNumber(vector<int> numbers) {
    string result;
    int size = numbers.size();

    if (size < 1) {
      return result;
    }

    vector<string> str_num;
    for (int i = 0; i < size; i++) {
      stringstream ss;
      ss << numbers[i];
      /* 数字转换成字符串 */
      string s = ss.str();
      str_num.push_back(s);
    }

    sort(str_num.begin(), str_num.end(), compare_str);

    for (int i = 0; i < size; i++) {
      result += str_num[i];
    }

    return result;
  }
};
```
