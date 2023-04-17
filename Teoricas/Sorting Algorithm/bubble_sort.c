#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Función de Swapping
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

//Función de representación del array
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

void bubble_sort(int arr[], int n) {
    bool swapped = false;
    for (int i = 0; i < n-1; i++) {     
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                swapped = true;
            }
        }
        if (swapped == false) break;
        swapped = false;
    }
}

int main() {
    int arr[] = {5, 1, 4, 2, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, n);
    printf("Sorted array: ");
    printArray(arr, n);
    return EXIT_SUCCESS;
}

