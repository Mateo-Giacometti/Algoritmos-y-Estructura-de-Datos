#include <stdio.h>

void printArray(int array[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void binary_insertion_sort(int arr[], int n) {
   int left, right, mid, key;

   for(int i = 1; i < n; ++i) {
      key = arr[i];
      left = 0;
      right = i - 1;
      while (left <= right) {
         mid = (left + right) / 2;
         if (arr[mid] > key) {
            right = mid - 1;
         } else {
            left = mid + 1;
         }
      }

      for(int j = i - 1; j >= left; --j) {
         arr[j + 1] = arr[j];
      }
      arr[left] = key;
   }
}

int main() {
    int arr[] = {10, 5, 20, 3, 7, 2, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    binary_insertion_sort(arr, n);
    printf("Sorted array: ");
    printArray(arr, n);
    return 0;
}
