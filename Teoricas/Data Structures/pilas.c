#include <stdlib.h>
#include <stdio.h>
#include "listas.c"

typedef struct Pila{
    Lista_t * lista;
}Pila_t;


void push(Pila_t * pila, int dato){
    lista_insertar_primero(pila -> lista, dato);
}

int pop(Pila_t * pila){
    int value =  obtener_primero(pila -> lista);
    lista_borrar_primero(pila -> lista);
    return value; // te devuelve el elemento que borro
}

int peek(Pila_t * pila){
    return obtener_primero(pila -> lista);
}

Pila_t* iniciar_pila(){

    Nodo_t * nodo1 = (Nodo_t *)malloc (sizeof(Nodo_t));
    nodo1 -> value = 1;
    nodo1 -> next = NULL;
    //Lista_t * lista = inicializacion(nodo1);
    Lista_t * lista = inicializacion_();

    Pila_t * pila = (Pila_t *) malloc (sizeof(Pila_t));
    if (NULL == pila){
        return NULL;
    }

    pila -> lista = lista;

    return pila;

}

void destruir(Pila_t * pila){

    destruir_lista(pila -> lista);
    free(pila);

}

void print_reverse(int* array){ // lee una secuencia de ints hasta llegar a un 0

    Pila_t * pila = iniciar_pila();

    if (NULL == pila){
        return;
    }
    int i = 0;
    while(array[i] != 0){
        push(pila, array[i]);
        i++;
    }

    while ((pila -> lista) -> n != 0){
        printf(" %i ", pop(pila)); //el pop borra y retornea lo que borro
    }
    printf("\n");

    //destruir(pila);
}



bool stack_sorted_descending(Pila_t * pila) {
//verifica si los elementos de la pila estan ordenados en orden decreciente
    int anterior = pop(pila);
    while((pila -> lista) -> n != 0){
        int primero = pop(pila);
        if (primero > anterior ){
            return false;
        } // el que sale tiene que ser mas grande al anterior
        anterior = primero;
        
    }
    return true;
}



int main(){

    int * array = (int*)malloc(sizeof(int)*7);
    if (NULL == array){
        return 0;
    }
    array[0] = 4;
    array[1] = 3;
    array[2] = 2;

    //print_reverse(array);
    //free(array);

    Pila_t * pila = iniciar_pila();
    for (int i = 0; i < sizeof(array)/sizeof(int); i++){
        push(pila, array[i]);
    }

    printf(" %i ", (stack_sorted_descending(pila)));
}




