#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* heap;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* create_max_heap(int capacity) {
    MaxHeap* max_heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    max_heap->heap = (int*)malloc(sizeof(int) * capacity);
    max_heap->size = 0;
    max_heap->capacity = capacity;
    return max_heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heap_up(MaxHeap* max_heap){
    int index = max_heap->size; //no le sume que le agregue (n-1)
    int parent_index = (index - 1) / 2; //formula de encontrar padre
    while (index > 0 && max_heap->heap[index] > max_heap->heap[parent_index]) { // si el hijo es mayor al padre:
        swap(&max_heap->heap[index], &max_heap->heap[parent_index]);
        index = parent_index;
        parent_index = (index - 1) / 2;
    }
}

void heap_up2(int* max_heap, int n){
    int index = n-1 ; 
    int parent_index = (index - 1) / 2; //formula de encontrar padre
    while (index > 0 && max_heap[index] > max_heap[parent_index]) { // si el hijo es mayor al padre:
        swap(&(max_heap[index]), &(max_heap[parent_index]));
        index = parent_index;
        parent_index = (index - 1) / 2;
    }
}

void insert(MaxHeap* max_heap, int item) {
    if (max_heap->size == max_heap->capacity) {
        printf("Error: heap is full\n");
        return;
    }
    int index = max_heap->size;
    (max_heap->heap)[index] = item; //inserto el item en el ultimo lugar del vector
    heap_up(max_heap);
    max_heap->size++;
}

void heapify_down(int *array, int index, int n){

    int largest = index;
    int k1 = 2*index+1;
    int k2 = 2*index+2;

    if (k1 < n && array[k1] > array[largest]){
        largest = k1;
    }
    if (k2 < n && array[k2] > array[largest]){
        largest = k2;
    }

    if (largest != index) { //si hay alguno mayor
        //hago swap con el nodo que se pasa y sus hijos si se requiere
        swap(&array[largest], &array[index]);
        heapify_down(array, largest, n); //llamo a la funcion con el indice de donde se intercambio
    } 
    
}

int remove_max(MaxHeap* heap){
    int max_val = heap-> heap[0];
    heap->heap[0] = heap->heap[heap->size - 1];  // Movemos el último elemento al lugar del máximo.
    heap->size --;  // Decrementamos el tamaño del heap.
    heapify_down(heap -> heap, heap -> heap[0], heap->size);  // Reordenamos el heap hacia abajo.
    return max_val;
}

int* ej_3( int* a1, int *a2, int len_a1, int len_a2, int n){ // n total de elementos, m arreglos
    MaxHeap* max_heap = create_max_heap(2);
    int *new_a = (int *) malloc (n*sizeof(int)); //creo el nuevo arreglo que va a ser el ordenado
    int i1 = 0;
    int i2 = 0;
    int idx = 0;
    insert(max_heap, a1[0]);
    insert(max_heap, a2[0]);
    while (max_heap -> size){ //mientras el heap no este vacio
        int aux = remove_max(max_heap); //saco el maximo
        new_a[idx] = aux; //lo agrego al nuevo arreglo
        if (a1[i1] == aux){ //si el maximo es del arreglo 1
            i1 ++;
            if (i1 < len_a1){ //si ese arreglo sigue teniendo elementos para insertar
                insert(max_heap, a1[i1]);
            }
        } else if (a2[i2] == aux){ //si el maximo es del arreglo 2
            i2 ++;
            if (i2 < len_a2){ //si ese arreglo sigue teniendo elementos para insertar
                insert(max_heap, a2[i2]);
            }
        }
        idx ++; //aumento el indice del arreglo ordenado para insertar el siguiente
    }
    return new_a;
}

int main3() {
    MaxHeap* max_heap = create_max_heap(10);
    insert(max_heap, 5);
    insert(max_heap, 3);
    insert(max_heap, 8);
    insert(max_heap, 10);
    for (int i = 0; i < max_heap->size; i++) {
        printf("%d ", max_heap->heap[i]);
    }
    free(max_heap->heap);
    free(max_heap);
    return 0;
}


int main() {
    int arr[] = {3, 8, 2, 10, 4, 6, 1, 7, 5, 200, 3452, 3787, 336282, 33827, -10, -15, -500, -1000};

    int n = sizeof(arr) / sizeof(arr[0]);
    //Convertir el arreglo en un heap válido llamando a heap_down desde el ultimo padre
    for (int i = (n - 1)/2 ; i >= 0; i--){
       heapify_down(arr, i, n);
    }

    for (int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }

    // Imprimir el arreglo ordenado
    // printf("Arreglo ordenado: ");


    // while (n > 0) {

    //     printf("%d ", arr[n]);
    //     arr[0] = arr[n-1];
    //     n--;
    //     heapify_down(arr, 0, n);
    // }
    // printf("\n");

    // return 0;
}


int main2(){

    int a1[] = {8, 6, 4, 2};
    int a2[] = {9, 7, 5, 3};

    int *ord = ej_3(a1, a2, 4, 4, 8);
    for (int i = 0; i < 8; i++){
        printf("%i ", ord[i]);
    }

}