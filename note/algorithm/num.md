## 简介
关于数字相关的算法题目
## 1、在一堆数中取出k个最小的数
有一堆数字，取出这些数中最小的k个数字
### 分析
取出最小的k个数，有两种实现方法：
- 通过快排中的partition方法，直到分割的位置是k-1，这样的话从0到k-1的位置就是k个最小的数字
- 通过构造一个k个值的小根堆，然后从剩下的数字中继续维持这个小根堆
### 关键代码分析
```
/* partition 方法 */
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

/* 小根堆方法 */
vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
  vector<int> result;
  int len = input.size();

  if (len < 1 || k < 1 || k > len) {
    return result;
  }
  for (int i = 0; i < k; i++) {
    result.push_back(input[i]);
  }

  make_heap(result.begin(), result.end());
  for (int i = k; i < len; i++) {
    if (input[i] < result[0]) {
      pop_heap(result.begin(), result.end());
      result.pop_back();
      result.push_back(input[i]);
      push_heap(result.begin(), result.end());
    }
  }
  return result;
```
