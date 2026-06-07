#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stdlib.h>

void merge(int arr[], int left, int mid, int right, long long *movs)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
        (*movs)++;
    }

    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[mid + 1 + i];
        (*movs)++;
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];

        (*movs)++;
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
        (*movs)++;
    }

    while (j < n2)
    {
        arr[k++] = R[j++];
        (*movs)++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right, long long *movs)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, movs);
        mergeSort(arr, mid + 1, right, movs);

        merge(arr, left, mid, right, movs);
    }
}

#endif