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
        int right_son = 2*i + 1;
        int left_son = 2*i + 2;
        if(right_son < size && left_son < size){
            if(pos_heap[right_son] > pos_heap[i] || pos_heap[left_son] > pos_heap[i]) return false;
        }
        if(right_son > size){
            if(pos_heap[left_son] > pos_heap[i]) return false;
        }
        if(left_son > size){
            if(pos_heap[right_son] > pos_heap[i]) return false;
        }

    }
    return true;
}