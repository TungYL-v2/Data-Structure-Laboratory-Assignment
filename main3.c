#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

// 生成随机数
void generateRandomNumbers(int arr[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000;
    }
}

// 希尔排序
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

// 快速排序分区函数
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// 快速排序
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 锦标赛排序（堆排序实现）
void heapify(int arr[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;

    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, size, largest);
    }
}

void tournamentSort(int arr[], int size) {
    // 构建最大堆
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    // 一个个提取元素
    for (int i = size - 1; i > 0; i--) {
        // 移动当前根到末尾
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // 在减小的堆上调用heapify
        heapify(arr, i, 0);
    }
}

// 折半查找
int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// 打印数组（用于测试）
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int numbers[SIZE];
    int shellSorted[SIZE], quickSorted[SIZE], tournamentSorted[SIZE];
    
    // 生成随机数
    generateRandomNumbers(numbers, SIZE);
    
    // 复制数组用于不同排序
    for (int i = 0; i < SIZE; i++) {
        shellSorted[i] = numbers[i];
        quickSorted[i] = numbers[i];
        tournamentSorted[i] = numbers[i];
    }
    
    // 测试希尔排序
    clock_t start = clock();
    shellSort(shellSorted, SIZE);
    double shellTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("希尔排序完成，耗时: %.4f秒\n", shellTime);
    
    // 测试快速排序
    start = clock();
    quickSort(quickSorted, 0, SIZE - 1);
    double quickTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("快速排序完成，耗时: %.4f秒\n", quickTime);
    
    // 测试锦标赛排序
    start = clock();
    tournamentSort(tournamentSorted, SIZE);
    double tournamentTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("锦标赛排序完成，耗时: %.4f秒\n", tournamentTime);
    
    // 折半查找演示
    int target;
    printf("\n请输入要查找的数字: ");
    scanf("%d", &target);
    
    // 在希尔排序结果中查找
    int pos = binarySearch(shellSorted, SIZE, target);
    if (pos != -1)
        printf("在希尔排序结果中找到数字 %d，位置为: %d\n", target, pos);
    else
        printf("在希尔排序结果中未找到数字 %d\n", target);
    
    // 在快速排序结果中查找
    pos = binarySearch(quickSorted, SIZE, target);
    if (pos != -1)
        printf("在快速排序结果中找到数字 %d，位置为: %d\n", target, pos);
    else
        printf("在快速排序结果中未找到数字 %d\n", target);
    
    // 在锦标赛排序结果中查找
    pos = binarySearch(tournamentSorted, SIZE, target);
    if (pos != -1)
        printf("在锦标赛排序结果中找到数字 %d，位置为: %d\n", target, pos);
    else
        printf("在锦标赛排序结果中未找到数字 %d\n", target);
    
    return 0;
}