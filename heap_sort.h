#ifndef HEAP_SORT_H
#define HEAP_SORT_H

void swapHeap(int *a, int *b, long long *movs)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    (*movs)++;
}

void heapify(int arr[], int n, int i, long long *movs)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swapHeap(&arr[i], &arr[largest], movs);
        heapify(arr, n, largest, movs);
    }
}

void heapSort(int arr[], int n, long long *movs)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, movs);

    for (int i = n - 1; i > 0; i--)
    {
        swapHeap(&arr[0], &arr[i], movs);
        heapify(arr, i, 0, movs);
    }
}

#endif