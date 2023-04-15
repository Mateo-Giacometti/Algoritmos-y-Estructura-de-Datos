#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
Usando únicamente una pila escriba una función que determine si un string es un
palíndromo o capicúa. Por ejemplo “neuquen” es un palíndromo, “mendoza” no.
*/


struct pila;
typedef struct pila pila_t;

struct pila {
    char *list;
    size_t size;
};

pila_t *new_pila(){
    pila_t *new_pila = (pila_t *) malloc(sizeof(pila_t));
    if(!new_pila) return NULL;
    new_pila->list = (char *) malloc(sizeof(char));
    if(!new_pila->list) return NULL;
    new_pila->size = 0;
    return new_pila;
}

bool push(pila_t *pila, char letter){
    if(!pila) return false;
    char *new_list = (char *) realloc(pila->list, sizeof(char) * (pila->size + 1));
    if(!new_list) return false;
    pila->list = new_list;
    pila->list[pila->size] = letter;
    pila->size++;
    return true;
}


//Hacer un arreglo dinamico de chars



