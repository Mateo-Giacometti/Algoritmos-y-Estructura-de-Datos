#include "tp1.h"
#include <stdlib.h>

/*
 * Determina si un número es primo.
 */
bool is_prime(int x){
    for(int i = 2; i < x; i++){
        if (x % i == 0){
            return false;
        }
    }
    return true;
}

/*
 * Dado el volumen de un deposito D y el volumen de un producto V
 * la función calcula cuantos productos entran en el depósito.
 */
int storage_capacity(float d, float v){
    return (int) (d / v);
}

/*
 * Intercambia dos valores de enteros.
 */
void swap(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
    return;
}

/*
 * Devuelve el máximo de un arreglo de enteros.
 */
int array_max(const int *array, int length){
    int max_array = array[0];
    for(int i = 1; i < length; i++){
        if(array[i] > max_array){
            max_array = array[i];
        }
    }
    return max_array;
}

/*
 * Aplica la función a cada elemento de un arreglo de enteros.
 */
void array_map(int *array, int length, int f(int)){
    if (array == NULL || f == NULL || length <= 0){
        return;
    }
    for (int i = 0; i < length; i++) {
        array[i] = f(array[i]);
    }
    return;
}

/*
 * Copia un arreglo de enteros en memoria dinámica.
 * Si el arreglo es NULL devuelve NULL.
 */
int *copy_array(const int *array, int length){
    if(array == NULL){
        return NULL;
    }
    int *array_copy = malloc(length * sizeof(int));
    if(array_copy == NULL){
        return NULL;
    }
    for (int i = 0; i < length; i++) {
        array_copy[i] = array[i];
    }
    return array_copy;
}

/*
 * Hace bubble sort sobre un arreglo de enteros ascendentemente.
 * Si el arreglo es NULL, no hace nada.
 */
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

/*
 * Determina si dos arreglos de enteros son identicamente iguales.
 * En el caso de que alguno sea NULL solo devuelve true si el otro tambien lo es.
 */
bool array_equal(const int *array1, int length1,
                 const int *array2, int length2){
    if(array1 == NULL && array2 == NULL){
        return true;
    }
    if(length1 != length2 || array1 == NULL || array2 == NULL){
        return false;
    }
    for (int i = 0; i < length1; i++) {
        if(array1[i] != array2[i]){
            return false;
        }
    }
    return true;

}

/*
 * Determina si dos arrays de enteros son análogos a un anagrama para textos (en algun orden particular, son el mismo arreglo).
 * Si alguno es NULL devuelve false.
 */
bool integer_anagrams(const int *array1, int length1,
                      const int *array2, int length2){
    if(array1 == NULL || array2 == NULL){
        return false;
    }
    if(length1 != length2){
        return false;
    }
    int *array1_copy = copy_array(array1, length1);
    int *array2_copy = copy_array(array2, length2);
    bubble_sort(array1_copy, length1);
    bubble_sort(array2_copy, length2);
    bool result = array_equal(array1_copy, length1, array2_copy, length2);
    free(array1_copy);
    free(array2_copy);
    return result;
}

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
    if(array_of_arrays == NULL || array_lenghts == NULL){
        return NULL;
    }
    int **array_of_arrays_copy = malloc(array_amount * sizeof(int *));
    if(array_of_arrays_copy == NULL){
        return NULL;
    }
    for (int i = 0; i < array_amount; i++) {
        array_of_arrays_copy[i] = copy_array(array_of_arrays[i], array_lenghts[i]);
    }
    return array_of_arrays_copy;
}

/*
 * Libera toda la memoria asociada a un arreglo de arreglos.
 *
 * array_of_arrays: un arreglo de punteros a arreglos de enteros
 * array_lenghts: un arreglo con los largos de cada arreglo en array_of_arrays
 * array_amount: la cantidad de arreglos
 */
void free_array_of_arrays(int **array_of_arrays, int *array_lenghts, int array_amount){
    if(array_of_arrays == NULL || array_lenghts == NULL){
        return;
    }
    for (int i = 0; i < array_amount; i++) {
        free(array_of_arrays[i]);
    }
    free(array_of_arrays);
    free(array_lenghts);
    return;
}
