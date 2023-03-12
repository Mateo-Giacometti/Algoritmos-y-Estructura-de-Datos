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

bool integer_anagrams(const int *array1, int length1,
                      const int *array2, int length2){
    if(array1 == NULL || array2 == NULL){
        return false;
    }
    if(length1 != length2){
        return false;
    }
    bubble_sort(array1, length1);
    bubble_sort(array2, length2);
    for(int i = 0; i < length1; i++){
        if (array1[i] != array2[i]){
            return false;
        }
    }
    return true;
}

int main(){
    int array1[] = {1, 2, 3, 4, 5};
    int array2[] = {5, 4, 3, 2, 1};
    int length1 = sizeof(array1)/sizeof(array1[0]);
    int length2 = sizeof(array2)/sizeof(array2[0]);
    printf("array1: ");
    for(int i = 0; i < length1; i++){
        printf("%d ", array1[i]);
    }
    printf(" array2: ");
    for(int i = 0; i < length2; i++){
        printf("%d ", array2[i]);
    }
    printf(" son anagramas? %s ", integer_anagrams(array1, length1, array2, length2) ? "true" : "false");

    printf("array1: ");
    for(int i = 0; i < length1; i++){
        printf("%d ", array1[i]);
    }
    printf(" array2: ");
    for(int i = 0; i < length2; i++){
        printf("%d ", array2[i]);
    }

    return 0;


}