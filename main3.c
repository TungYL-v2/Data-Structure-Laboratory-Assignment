#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

// ���������
void generateRandomNumbers(int arr[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000;
    }
}

// ϣ������
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

// ���������������
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

// ��������
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ���������򣨶�����ʵ�֣�
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
    // ��������
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    // һ������ȡԪ��
    for (int i = size - 1; i > 0; i--) {
        // �ƶ���ǰ����ĩβ
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // �ڼ�С�Ķ��ϵ���heapify
        heapify(arr, i, 0);
    }
}

// �۰����
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

// ��ӡ���飨���ڲ��ԣ�
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int numbers[SIZE];
    int shellSorted[SIZE], quickSorted[SIZE], tournamentSorted[SIZE];
    
    // ���������
    generateRandomNumbers(numbers, SIZE);
    
    // �����������ڲ�ͬ����
    for (int i = 0; i < SIZE; i++) {
        shellSorted[i] = numbers[i];
        quickSorted[i] = numbers[i];
        tournamentSorted[i] = numbers[i];
    }
    
    // ����ϣ������
    clock_t start = clock();
    shellSort(shellSorted, SIZE);
    double shellTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("ϣ��������ɣ���ʱ: %.4f��\n", shellTime);
    
    // ���Կ�������
    start = clock();
    quickSort(quickSorted, 0, SIZE - 1);
    double quickTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("����������ɣ���ʱ: %.4f��\n", quickTime);
    
    // ���Խ���������
    start = clock();
    tournamentSort(tournamentSorted, SIZE);
    double tournamentTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("������������ɣ���ʱ: %.4f��\n", tournamentTime);
    
    // �۰������ʾ
    int target;
    printf("\n������Ҫ���ҵ�����: ");
    scanf("%d", &target);
    
    // ��ϣ���������в���
    int pos = binarySearch(shellSorted, SIZE, target);
    if (pos != -1)
        printf("��ϣ�����������ҵ����� %d��λ��Ϊ: %d\n", target, pos);
    else
        printf("��ϣ����������δ�ҵ����� %d\n", target);
    
    // �ڿ����������в���
    pos = binarySearch(quickSorted, SIZE, target);
    if (pos != -1)
        printf("�ڿ������������ҵ����� %d��λ��Ϊ: %d\n", target, pos);
    else
        printf("�ڿ�����������δ�ҵ����� %d\n", target);
    
    // �ڽ������������в���
    pos = binarySearch(tournamentSorted, SIZE, target);
    if (pos != -1)
        printf("�ڽ��������������ҵ����� %d��λ��Ϊ: %d\n", target, pos);
    else
        printf("�ڽ�������������δ�ҵ����� %d\n", target);
    
    return 0;
}