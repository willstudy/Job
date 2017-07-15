int partition(int data[], int length, int start, int end) {
    if (data == NULL || length <= 0 || start < 0 || end < 0) {
        throw new Exception("Invaild Parameters");
    }

    int index = RandomInRange(start, end);
    Swap(&data[index], &data[end]);

    int small = start - 1;
    for (index = start; index < end; index++) {
        if (data[index] < data[end]) {
            small++;
            if (small != index)
                Swap(&data[small], &data[index]);
        }
    }

    small++;
    Swap(&data[small], &data[end]);
    
    return small;
}

/* 递归方式的实现 */
void quick_sort(int data[], int length, int start, int end) {
    if (start == end)
        return;

    int index = partition(data, length, start, end);
    if (index > start) {
        quick_sort(data, length, start, index - 1);
    }
    if (index < end) {
        quick_sort(data, length, index + 1, end);
    }
}

/* 非递归方式的实现 */
void quick_sort(int data[], int length, int start, int end) {
    Stack<int> S;
    if (start < end) {
        int index = partition(data, length, start, end);
        if (start < index - 1) {
            S.push(start);
            S.push(index-1);
        }
        if (index + 1 < end) {
            S.push(index+1);
            S.push(end);
        }

        while(!S.empty()) {
            int left = S.pop();
            int right = S.pop();
            int index = partition(data, length, left, right);

            if (left < index - 1) {
                S.push(left);
                S.push(index - 1);
            }
            if (index + 1 < right) {
                S.push(index+1);
                S.push(right);
            }
        }
    }
}
