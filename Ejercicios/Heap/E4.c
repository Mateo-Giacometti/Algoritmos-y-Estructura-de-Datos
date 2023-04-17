#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
Implementar un algoritmo que verifique si un arreglo de números
representa a un heap.
*/

bool heap_validation(int *pos_heap, size_t size){
    if(!pos_heap) return false;
    for(int i = 0; i < size; i++){
        if(i == 0) continue;
        int parent = (i - 1) / 2;
        if(pos_heap[parent] < pos_heap[i]) return false;
    }
    return true;
}


int main(void){
    int heap[] = {50, 30, 20, 10, 8, 16, 14};
    int heap2[] = {10, 8, 7, 5, 4, 6, 3, 2, 1, 9};
    
    if(heap_validation(heap, 7)) printf("Es un heap\n");
    else printf("No es un heap\n");

    if(heap_validation(heap2, 10)) printf("Es un heap\n");
    else printf("No es un heap\n");

    return 0;
}