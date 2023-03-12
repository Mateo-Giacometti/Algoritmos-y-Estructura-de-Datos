#include <stdio.h>
#include <stdbool.h>

void swap(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
    return;
}

void bubble_sort(int *array, int length){
    if(array == NULL){
        return;
    }
    for (int step = 0; step < length - 1; step++){
        for (int i = 0; i < length - step - 1; ++i){
            if (array[i] > array[i + 1]) {
                swap(&array[i], &array[i + 1]);
            }
        }
    }
    return;
}

int main(){
    int array[] = {11, 2, 3, 4, 5, 23, 7, 8, 9, 10, 1, 0};
    int length = sizeof(array) / sizeof(array[0]);
    bubble_sort(array, length);
    for (int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    return 0;

}