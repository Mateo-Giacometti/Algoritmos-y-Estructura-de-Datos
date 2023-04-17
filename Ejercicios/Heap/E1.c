#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*Implementar el algoritmo heapify y dar su complejidad temporal.
1. Utilizando heapify up
2. Utilizando heapify down
*/

struct heap;
typedef struct heap heap_t;

struct heap {
    int *list;
    size_t size;
};

heap_t *new_heap(){
    heap_t *new_heap = (heap_t *) malloc(sizeof(heap_t));
    if(!new_heap) return NULL;
    new_heap->size = 0;
    return new_heap;
}

bool push(heap_t *heap, int value){
    if(!heap) return false;
    if(heap->size == 0){
        heap->list = (int *) malloc(sizeof(int));
        if(!heap->list) return false;
        heap->list[0] = value;
        heap->size++;
        return true;
    }
    heap->list = (int *) realloc(heap->list, sizeof(int) * (heap->size + 1));
    if(!heap->list) return false;
    heap->list[heap->size] = value;
    heap->size++;
    return true;
}

int pop(heap_t *heap){
    if(!heap) return -1;
    int value = heap->list[heap->size - 1];
    heap->list = (int *) realloc(heap->list, sizeof(int) * (heap->size - 1));
    if(!heap->list) return -1;
    heap->size--;
    return value;
}

int heapify_up(heap_t *heap){
    if(!heap) return -1;
    int i = heap->size - 1;
    while(i > 0){
        int parent = (i - 1) / 2;
        if(heap->list[parent] < heap->list[i]){
            int aux = heap->list[parent];
            heap->list[parent] = heap->list[i];
            heap->list[i] = aux;
            i = parent;
        } else {
            break;
        }
    }
    return 1;
}

int heapify_down(heap_t *heap){
    if(!heap) return -1;
    int i = 0;
    while(i < heap->size){
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int max = i;
        if(left < heap->size && heap->list[left] > heap->list[max]){
            max = left;
        }
        if(right < heap->size && heap->list[right] > heap->list[max]){
            max = right;
        }
        if(max != i){
            int aux = heap->list[max];
            heap->list[max] = heap->list[i];
            heap->list[i] = aux;
            i = max;
        } else {
            break;
        }
    }
    return 1;
}

void print_heap(heap_t *heap){
    if(!heap) return;
    for(int i = 0; i < heap->size; i++){
        printf("%d ", heap->list[i]);
    }
    printf("size: %d ", heap->size); 
    printf("  ");
}

int main(void){
    
}




