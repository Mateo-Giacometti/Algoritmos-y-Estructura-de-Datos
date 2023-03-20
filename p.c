#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/*
bool integer_anagrams(const int *array1, int length1,
                      const int *array2, int length2){
    if(!array1 || !array2){
        return false;
    }
    if(length1 != length2){
        return false;
    }
    int *counter = malloc(length1 * sizeof(int));
    if(!counter){
        return false;
    }
    for (int i = 0; i < length1; i++){
        counter[array1[i]]++;
        counter[array2[i]]--;
    }
    for (int i = 0; i < length1; i++){
        if(counter[i] != 0){
            free(counter);
            return false;
        }
    }
    free(counter);
    return true;
}
*/
/*
bool integer_anagrams(const int *array1, int length1,
                      const int *array2, int length2){
    if(!array1 || !array2){
        return false;
    }
    if(length1 != length2){
        return false;
    }
    int *array1_copy = copy_array(array1, length1);
    int *array2_copy = copy_array(array2, length2);
    if (!array1_copy || !array2_copy){
        free(array1_copy);
        free(array2_copy);
        return false;
    }
    bubble_sort(array1_copy, length1);
    bubble_sort(array2_copy, length2);
    bool result = array_equal(array1_copy, length1, array2_copy, length2);
    free(array1_copy);
    free(array2_copy);
    return result;
}
*/

/*
 * Copia un arreglo de arreglos de enteros en memoria dinámica.
 * Si alguno de ellos en NULL, continua siendo NULL.
 * Si el arreglo de arreglos es NULL, devuelve NULL.
 *
 * array_of_arrays: un arreglo de punteros a arreglos de enteros
 * array_lenghts: un arreglo con los largos de cada arreglo en array_of_arrays
 * array_amount: la cantidad de arreglos
 */
int **copy_array_of_arrays(const int **array_of_arrays, const int *array_lenghts, int array_amount){
    if(!array_of_arrays || !array_lenghts || array_amount <= 0){
        return NULL;
    }
    int **array_of_arrays_copy = (int **) malloc(sizeof(int *) * array_amount);
    if(!array_of_arrays_copy){
        return NULL;
    }
    for (int i = 0; i < array_amount; i++){
        if (!array_of_arrays[i]){
            array_of_arrays_copy[i] = NULL;
        }
        else{
            array_of_arrays_copy[i] = (int *) malloc(sizeof(int) * array_lenghts[i]);
            if(!array_of_arrays_copy[i]){
                for(int j = 0; j < i; j++){
                    free(array_of_arrays_copy[j]);
                }
                free(array_of_arrays_copy);
                return NULL;
            }
            for (int k = 0; k < array_lenghts[i]; k++){
                array_of_arrays_copy[i][k] = array_of_arrays[i][k];
            }
        }
    }
    return array_of_arrays_copy;
}

int main(void){
    
    int **array_of_arrays = (int **) malloc(sizeof(int *) * 3);
    int *array_lenghts = (int *) malloc(sizeof(int) * 3);
    array_of_arrays[0] = (int *) malloc(sizeof(int) * 3);
    array_of_arrays[1] = (int *) malloc(sizeof(int) * 3);
    array_of_arrays[2] = (int *) malloc(sizeof(int) * 3);
    array_lenghts[0] = 3;
    array_lenghts[1] = 3;
    array_lenghts[2] = 3;
    array_of_arrays[0][0] = 1;
    array_of_arrays[0][1] = 2;
    array_of_arrays[0][2] = 3;
    array_of_arrays[1][0] = 1;
    array_of_arrays[1][1] = 2;
    array_of_arrays[1][2] = 3;
    array_of_arrays[2][0] = 1;
    array_of_arrays[2][1] = 2;
    array_of_arrays[2][2] = 3;

    int **array_of_arrays_copy = copy_array_of_arrays((const int **) array_of_arrays, array_lenghts, 3);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < array_lenghts[i]; j++){
            printf("%d ", array_of_arrays_copy[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < 3; i++){
        free(array_of_arrays[i]);
        free(array_of_arrays_copy[i]);
    }
    free(array_of_arrays);
    free(array_of_arrays_copy);
    free(array_lenghts);

    return EXIT_SUCCESS;
}