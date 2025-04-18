# 数据结构实验报告

## 题目：查找与排序算法比较

**班级**：xxxxx  
**姓名**：xxxx  
**学号**：xxxxx  
**完成日期**：xxxxx  

---

### 一、需求分析

1. 本实验程序需要处理的数据对象为10000个随机生成的整数。
2. 程序执行流程包括：
   - 随机生成10000个整数
   - 分别使用希尔排序、快速排序和锦标赛排序对数据进行排序
   - 测量并比较三种排序算法的执行时间
   - 实现折半查找算法，在排序后的数组中查找指定元素
3. 程序执行的命令包括：
   1）生成随机数数组
   2）执行希尔排序并计时
   3）执行快速排序并计时
   4）执行锦标赛排序并计时
   5）在排序后的数组中执行折半查找
4. 预期输出：
   - 三种排序算法的执行时间
   - 查找结果（找到时输出位置，未找到时提示）

---

### 二、概要设计

为实现上述功能，需要以下数据结构：

1. **数组结构**：
   - 用于存储随机生成的整数
   - 支持排序和查找操作

2. **排序算法抽象**：
   - 希尔排序：通过分组插入排序实现
   - 快速排序：通过分治策略实现
   - 锦标赛排序：通过堆结构实现

3. **查找算法抽象**：
   - 折半查找：在有序数组中高效查找

---

### 三、详细设计

#### 1. 数据结构定义
```c
#define SIZE 10000  // 数组大小
int numbers[SIZE];  // 原始数据数组
int shellSorted[SIZE], quickSorted[SIZE], tournamentSorted[SIZE];  // 排序后的数组
```

#### 2. 核心算法实现

**(1) 随机数生成**
```c
void generateRandomNumbers(int arr[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000;
    }
}
```

**(2) 希尔排序**
```c
void shellSort(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
```

**(3) 快速排序**
```c
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
```

**(4) 锦标赛排序（堆排序）**
```c
void heapify(int arr[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;

    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, size, largest);
    }
}

void tournamentSort(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    for (int i = size - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
```

**(5) 折半查找**
```c
int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```

---

### 四、调试分析

1. **初始问题**：
   - 快速排序递归深度过大导致栈溢出
   - 解决方案：优化分区算法，减少递归深度

2. **性能优化**：
   - 锦标赛排序（堆排序）实现时，初始构建堆的方式影响效率
   - 改进为从最后一个非叶子节点开始调整

3. **时间复杂度分析**：
   - 希尔排序：平均O(n log n)，最坏O(n^2)
   - 快速排序：平均O(n log n)，最坏O(n^2)
   - 锦标赛排序：稳定O(n log n)
   - 折半查找：O(log n)

4. **实验结果**：
   - 快速排序在随机数据上表现最佳
   - 锦标赛排序表现稳定
   - 希尔排序在中等规模数据上表现良好

---

### 五、用户使用说明

1. 运行程序后，自动生成10000个随机数
2. 程序自动执行三种排序算法并输出耗时
3. 输入要查找的数字
4. 程序输出在三种排序结果中的查找结果

---

### 六、测试结果

```
希尔排序完成，耗时: 0.0156秒
快速排序完成，耗时: 0.0042秒
锦标赛排序完成，耗时: 0.0078秒

请输入要查找的数字: 12345
在希尔排序结果中找到数字 12345，位置为: 4921
在快速排序结果中找到数字 12345，位置为: 4921
在锦标赛排序结果中找到数字 12345，位置为: 4921
```

---

### 七、实验总结

通过本次实验：
1. 实现了三种经典排序算法和折半查找算法
2. 比较了不同排序算法的性能差异
3. 验证了理论时间复杂度与实际运行时间的关系
4. 掌握了算法性能分析的基本方法

**改进方向**：
1. 实现更优化的快速排序（如三数取中法）
2. 增加数据规模测试算法的极限性能
3. 可视化展示排序过程和性能对比