#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
Implementar las siguientes funciones
1. int stack_sorted_descending(pila_t* pila); que verifica si los elementos de la
pila están ordenados en orden decreciente
2. int stack_sorted_ascending(pila_t* pila); que verifica si los elementos de la
pila están ordenados en orden creciente
*/

struct pila;
typedef struct pila pila_t;

struct pila {
    int *list;
    size_t size;
};

pila_t *new_pila(){
    pila_t *new_pila = (pila_t *) malloc(sizeof(pila_t));
    if(!new_pila) return NULL;
    new_pila->size = 0;
    return new_pila;
}

bool push(pila_t *pila, int value){
    if(!pila) return false;
    if(pila->size == 0){
        pila->list = (int *) malloc(sizeof(int));
        if(!pila->list) return false;
        pila->list[0] = value;
        pila->size++;
        return true;
    }
    pila->list = (int *) realloc(pila->list, sizeof(int) * (pila->size + 1));
    if(!pila->list) return false;
    pila->list[pila->size] = value;
    pila->size++;
    return true;
}

int pop(pila_t *pila){
    if(!pila) return -1;
    int value = pila->list[pila->size - 1];
    pila->list = (int *) realloc(pila->list, sizeof(int) * (pila->size - 1));
    if(!pila->list) return -1;
    pila->size--;
    return value;
}

int stack_sorted_descending(pila_t* pila){
    if(!pila) return -1;
    for(int i = 0; i < pila->size - 1; i++){
        if(pila->list[i] < pila->list[i + 1]) return 0;
    }
    return 1;
}

int stack_sorted_ascending(pila_t* pila){
    if(!pila) return -1;
    for(int i = 0; i < pila->size - 1; i++){
        if(pila->list[i] > pila->list[i + 1]) return 0;
    }
    return 1;
}

int main(void){
    pila_t *pila = new_pila();
    pila_t *pila2 = new_pila();
    pila_t *pila3 = new_pila();

    push(pila, 1);
    push(pila, 2);
    push(pila, 3);
    push(pila, 4);

    push(pila2, 10);
    push(pila2, 9);
    push(pila2, 8);
    push(pila2, 7);

    push(pila3, 1);
    push(pila3, 3);
    push(pila3, 2);
    push(pila3, 4);

    if(stack_sorted_descending(pila)) printf("La pila está ordenada en orden decreciente (descendente).\n");
    else printf("La pila no está ordenada en orden decreciente (descendente). \n");
    if(stack_sorted_ascending(pila)) printf("La pila está ordenada en orden creciente (ascendente).\n");
    else printf("La pila no está ordenada en orden creciente (ascendente).\n");

    if(stack_sorted_descending(pila2)) printf("La pila está ordenada en orden decreciente (descendente).\n");
    else printf("La pila no está ordenada en orden decreciente (descendente).\n");
    if(stack_sorted_ascending(pila2)) printf("La pila está ordenada en orden creciente (ascendente).\n");
    else printf("La pila no está ordenada en orden creciente (ascendente).\n");

    if(stack_sorted_descending(pila3)) printf("La pila está ordenada en orden decreciente (descendente).\n");
    else printf("La pila no está ordenada en orden decreciente (descendente).\n");
    if(stack_sorted_ascending(pila3)) printf("La pila está ordenada en orden creciente (ascendente).\n");
    else printf("La pila no está ordenada en orden creciente (ascendente).\n");

    return 0;
}