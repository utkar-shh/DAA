#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap function for Quick Sort
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort algorithm
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge function for Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort algorithm
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Function to compare the performance of Merge Sort and Quick Sort
void performanceTest(int arr[], int size) {
    int *arr1 = (int*)malloc(size * sizeof(int));
    int *arr2 = (int*)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        arr1[i] = arr[i];
        arr2[i] = arr[i];
    }

    clock_t start, end;
    double time_merge, time_quick;

    // Measure performance of Merge Sort
    start = clock();
    mergeSort(arr1, 0, size - 1);
    end = clock();
    time_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Measure performance of Quick Sort
    start = clock();
    quickSort(arr2, 0, size - 1);
    end = clock();
    time_quick = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Display results
    printf("Merge Sort Time: %f seconds\n", time_merge);
    printf("Quick Sort Time: %f seconds\n", time_quick);

    free(arr1);
    free(arr2);
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Display array before sorting
    printf("Array before sorting: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Compare performance
    performanceTest(arr, size);

    return 0;
}
