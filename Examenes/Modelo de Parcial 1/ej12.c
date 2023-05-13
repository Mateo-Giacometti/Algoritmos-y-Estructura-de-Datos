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
    new_pila->list[0] = '\0';
    new_pila->size = 1;
    return new_pila;
}

bool push(pila_t *pila, char value){
    if(!pila) return false;
    pila->list = (char *) realloc(pila->list, sizeof(char) * (pila->size + 1));
    if(!pila->list) return false;
    pila->list[pila->size] = value;
    pila->size++;
    return true;
}

char pop(pila_t *pila){
    if(!pila) return '\0';
    char value = pila->list[pila->size - 1];
    pila->list = (char *) realloc(pila->list, sizeof(char) * (pila->size - 1));
    if(!pila->list) return '\0';
    pila->size--;
    return value;
}

bool is_palindrome(char *string){
    pila_t *pila = new_pila();
    int i = 0;
    while(string[i] != '\0'){
        push(pila, string[i]);
        i++;
    }
    i = 0;
    while(string[i] != '\0'){
        if(string[i] != pop(pila)) return false;
        i++;
    }
    return true;
}

int main(){
    char *string = "neuquen";
    if(is_palindrome(string)) printf("Es palindromo\n");
    else printf("No es palindromo\n");
    return 0;
}





