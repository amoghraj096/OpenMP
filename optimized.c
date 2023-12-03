// Heap Sort Optimized
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}


void heapSort(int arr[], int n) {
#pragma omp parallel for default(none) shared(arr, n)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

#pragma omp parallel for default(none) shared(arr, n)
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}


int main() {
    omp_set_num_threads(16);
    srand(time(NULL)); // Seed for random values

    const int size = 100000000; // Size of the array
    int *arr = (int *)malloc(size * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Randomly initialize the array
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000000; // Random values between 0 and 999999
    }

    clock_t start = clock();

    heapSort(arr, size); // Sort the array using heapsort

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Time taken to sort %d elements: %f seconds\n", size, time_spent);

    free(arr); // Free the dynamically allocated memory

    return 0;
}
