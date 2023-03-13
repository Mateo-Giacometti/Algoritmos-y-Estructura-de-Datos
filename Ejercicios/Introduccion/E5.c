#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
Implementar las siguientes funciones en C:

1. void crearArreglo(int v)
Crea un arreglo estático de enteros de tamaño 8, inicializando todos sus elementos
con v, y lo imprime en pantalla.

2. int* crearArregloDin(int n, int v)
Dado un natural n, crea un arreglo de enteros de ese tamaño, inicializando todos sus
elementos con v, y devuelve un puntero al mismo.

3. Invocar la siguiente función con cualquiera de los arreglos inicializados anteriormente
y convencerse de que sus elementos están ubicados de manera contigua en memoria.
Recordar que cada elemento de tipo int ocupa 4 bytes.

void mostrarMemoria(int* arr, int size){}
    for(int i=0; i<size; i++){
    printf("Elemento: %d, Direccion: %d\n", i, &arr[i]);
    }
}
*/

void crearArreglo(int v){
    int array[8];
    printf("[ ");
    for(int i = 0; i < 8; i++){
        array[i] = v;
        printf("%d ",array[i]);
    }
    printf("]\n");
}

int* crearArregloDin(int n, int v){
    int* array = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        array[i] = v;
    }
    return array;
}

void mostrarMemoria(int* arr, int size){
    for(int i=0; i<size; i++){
        printf("Elemento: %d, Direccion: %d\n", i, &arr[i]);
    }
}

int main(void){
    crearArreglo(6);
    int* array = crearArregloDin(8, 6);
    mostrarMemoria(array, 8);
    free(array);
    return EXIT_SUCCESS;
}
