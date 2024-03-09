#include <stdio.h>

void bubbleSort(int arr[], int n, int swaps[]) {
    int i, j, temp, totalSwaps = 0;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swaps[arr[j]]++;
                swaps[arr[j+1]]++;
                totalSwaps += 2;
            }
        }
    }
    printf("Total number of swaps for Bubble Sort: %d\n", totalSwaps);
}

void selectionSort(int arr[], int n, int swaps[]) {
    int i, j, minIndex, temp, totalSwaps = 0;
    for (i = 0; i < n-1; i++) {
        minIndex = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            swaps[arr[i]]++;
            swaps[arr[minIndex]]++;
            totalSwaps += 2;
        }
    }
    printf("Total number of swaps for Selection Sort: %d\n", totalSwaps);
}

int main() {
    int array1[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int array2[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int n1 = sizeof(array1) / sizeof(array1[0]);
    int n2 = sizeof(array2) / sizeof(array2[0]);
    int swaps1[100] = {0}; // Assuming the range of values is 0-99
    int swaps2[100] = {0}; // Assuming the range of values is 0-99

    printf("array1:\n");
    bubbleSort(array1, n1, swaps1);
    for (int i = 0; i < n1; i++) {
        printf("%d: # of times %d is swapped\n", array1[i], array1[i]);
    }
    printf("\n");

    printf("array2:\n");
    selectionSort(array2, n2, swaps2);
    for (int i = 0; i < n2; i++) {
        printf("%d: # of times %d is swapped \n", array2[i], array2[i]);
    }
    printf("\n");

    return 0;
}
