#ifndef QUICK_SORT_H
#define QUICK_SORT_H

void swapQuick(int *a, int *b, long long *movs)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    (*movs)++;
}

int partitionQuick(int arr[], int low, int high, long long *movs)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swapQuick(&arr[i], &arr[j], movs);
        }
    }

    swapQuick(&arr[i + 1], &arr[high], movs);
    return i + 1;
}

void quickSort(int arr[], int low, int high, long long *movs)
{
    if (low < high)
    {
        int pi = partitionQuick(arr, low, high, movs);

        quickSort(arr, low, pi - 1, movs);
        quickSort(arr, pi + 1, high, movs);
    }
}

#endif