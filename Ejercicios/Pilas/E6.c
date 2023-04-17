#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
Escribir un programa que lee una secuencia de caracteres y verifica que
todos los parentesis, corchetes y llaves están balanceados.
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

bool is_balanced(char *string){
    pila_t *pila = new_pila();
    int i = 0;
    while(string[i] != '\0'){
        if(string[i] == '(' || string[i] == '[' || string[i] == '{'){
            push(pila, string[i]);
        }
        if(string[i] == ')' || string[i] == ']' || string[i] == '}'){
            if(pop(pila) == '\0') return false;
        }
        i++;
    }
    if(pila->size == 1) return true;
    else return false;
}

int main(){
    char string[100];
    printf("Ingrese una secuencia de caracteres: ");
    scanf("%s", string);
    if(is_balanced(string)) printf("La secuencia de caracteres está balanceada.\n");
    else printf("La secuencia de caracteres no está balanceada.\n");
    return 0;
}

