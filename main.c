
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
void swap(uint32_t* a, uint32_t* b)
{
    uint32_t tmp = *a;
    *a = *b;
    *b = tmp;
}
int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}
void array_filling(uint32_t a[], int size)
{
    for (int i = 0; i < size; ++i) {
        a[i] = getrand(0, 100000);
    }
}
int getMax(uint32_t arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
void countSort(uint32_t arr[], int n, int exp)
{
    uint32_t output[n];
    uint32_t count[10] = {0};
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
void radix_sort(uint32_t arr[], int n)
{
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
void odd_even_sort(uint32_t a[], int size)
{
    for (int k = 0; k < size; ++k) {
        if (k % 2 == 0) {
            for (int i = k % 2; i + 1 < size; i += 2) {
                if (a[i] > a[i + 1]) {
                    swap(&a[i], &a[i + 1]);
                }
            }
        }
        if (k % 2 == 1) {
            for (int i = k % 2; i + 1 < size; i += 2) {
                if (a[i] > a[i + 1]) {
                    swap(&a[i], &a[i + 1]);
                }
            }
        }
    }
}
void heapify(uint32_t arr[], int n, int i)
{
    int largest = i;   //наибольший =  корень
    int l = 2 * i + 1; //левый доч элемент
    int r = 2 * i + 2; //правый доч элемент
    if (l < n && arr[l] > arr[largest]) //если левый доч элемент больше корня
        largest = l;
    if (r < n && arr[r] > arr[largest]) //если правый доч элемент больше, чем
                                        //самый большой элемент на данный момент
        largest = r;
    if (largest != i) {
        swap(&arr[i], &arr[largest]); //если самый большой элемент не был
                                      //коренем на старте
        heapify(arr, n, largest);
    }
}
void heapSort(uint32_t arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) //построение кучи
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) { //извлекаем элементы из кучи поочередно
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0); //хипи на ум куче//макс эл первый
    }
}
int is_sorted(uint32_t* a, int n)
{
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            return 0;
        }
    }
    return 1;
}
void print(uint32_t arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}
int main()
{
    int SortFlag;
    printf("Radix Sort\n");
    for (int size = 50000; size < 1000001; size += 50000) {
        uint32_t a[size];
        array_filling(a, size);
        const double begin = wtime();
        radix_sort(a, size);
        const double end = wtime();
        SortFlag = is_sorted(&a[0], size);
        printf("Time for %d: %.6f", size, end - begin);
        if (SortFlag == 1) {
            printf("  Sorted  \n");
        } else {
            printf("  Not Sorted  \n");
        }
    }
    printf("\nHeap Sort\n");
    for (int size = 50000; size < 1000001; size += 50000) {
        uint32_t a[size];
        array_filling(a, size);
        const double begin = wtime();
        heapSort(a, size);
        const double end = wtime();
        SortFlag = is_sorted(&a[0], size);
        printf("Time for %d: %.6f", size, end - begin);
        if (SortFlag == 1) {
            printf("  Sorted  \n");
        } else {
            printf("  Not Sorted  \n");
        }
    }
    printf("\nOdd Even Sort\n");
    for (int size = 50000; size < 1000001; size += 50000) {
        uint32_t a[size];
        array_filling(a, size);
        const double begin = wtime();
        odd_even_sort(a, size);
        const double end = wtime();
        SortFlag = is_sorted(&a[0], size);
        printf("Time for %d: %.6f", size, end - begin);
        if (SortFlag == 1) {
            printf("  Sorted  \n");
        } else {
            printf("  Not Sorted  \n");
        }
    }
    return 0;
}
