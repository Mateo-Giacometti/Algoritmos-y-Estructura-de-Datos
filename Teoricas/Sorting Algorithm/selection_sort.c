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

void selection_sort(int array[], int size) {
  for (int step = 0; step < size - 1; step++) {
    int min_idx = step;
    for (int i = step + 1; i < size; i++) {
      if (array[i] < array[min_idx])
        min_idx = i;
    }
    swap(&array[min_idx], &array[step]);
  }
}

int main() {
  int data[] = {20, 12, 10, 15, 2};
  int size = sizeof(data) / sizeof(data[0]);
  selection_sort(data, size);
  printf("Sorted array: ");
  printArray(data, size);
}