#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// simplemente enlazadas

typedef struct Nodo {
int value;
struct Nodo *next;
}Nodo_t;

typedef struct Lista {
Nodo_t *head; // solo tiene el inicio
int n;
}Lista_t;

//doblemente enlazadas

typedef struct Nodo2 {
int value;
struct Nodo2 *next;
struct Nodo2 *prev;
}Nodo2_t;

typedef struct Lista2 {
Nodo2_t *head; //tiene el primer nodo
Nodo2_t *tail; //tiene el ultimo nodo
int n;
}Lista2_t;

//simplemente enlazadas

Lista_t * inicializacion(Nodo_t * primer_nodo){ // se lo paso por puntero &

    if (NULL == primer_nodo){
        return NULL;
    }
    Lista_t * lista =  (Lista_t *) malloc (sizeof( Lista_t));

    if (NULL == lista){
        return NULL;
    }
    lista->head = primer_nodo;
    lista->n = 1;

    return lista;
}

Lista_t * inicializacion_(){ // inicializarla sin nodo

    Lista_t * lista =  (Lista_t *) malloc (sizeof( Lista_t));
    if (NULL == lista){
        return NULL;
    }
    lista->head = NULL;
    lista->n = 0;

    return lista;
}

// doblemente enlazadas

Lista2_t * inicializacion2(Nodo2_t * primer_nodo){ // se lo paso por puntero &

    if (NULL == primer_nodo){
        return NULL;
    }
    Lista2_t * lista =  (Lista2_t *) malloc (sizeof( Lista2_t));
    if (NULL == lista){
        return NULL;
    }
    lista->head = primer_nodo;
    lista->tail = primer_nodo;
    lista->n = 1;

    return lista;
}

//Con el operador ”→” C/C++ nos proporciona una manera más sencilla de escribir el acceso a un atributo 
//a través de un puntero. En la función anterior accedemos al atributo inicio mediante el puntero lista.

//simplemente enlazadas

int insertar_ultimo(Lista_t * lista, int v){

    Nodo_t * nodo = (Nodo_t *) malloc (sizeof(Nodo_t)); //Asignación de la memoria para el nuevo elemento.

    if (NULL == nodo){
        return 0;
    }
    nodo -> value = v; //Introducción del contenido del campo de datos
    nodo -> next = NULL;  //Actualización de los punteros hacia último elemento --> en este caso a NULL porque va a ser el ultimo
    Nodo_t * actual = lista -> head; // Estamos posicionando en el primer elemento de la lista en la que vamos a insertar
    
   while ( (actual -> next) != NULL) { // mientras no sea NULL
        actual = actual -> next; // te moves al siguiente
        
    }
    //estamos ubicados en el ultimo de la lista

    actual -> next  = nodo; // este ya apunta a NULL
    lista -> n += 1; // se le agrego un elemento

    return 1;
}

//doblemente enlazadas

void insertar_ultimo2(Lista2_t * lista, int v){

    Nodo2_t * nodo = (Nodo2_t *) malloc (sizeof(Nodo2_t)); //Asignación de la memoria para el nuevo elemento.

    if (NULL == nodo){
        return;
    }
    nodo -> value = v; //Introducción del contenido del campo de datos
    nodo -> next = NULL;  //Actualización de los punteros hacia último elemento --> en este caso a NULL porque va a ser el ultimo
    Nodo2_t * ultimo = lista -> tail; // Estamos guardando el ultimo elemento de la lista en la que vamos a insertar

    ultimo -> next = nodo; //primer paso: asignamos el nodo al next del ultimo
    nodo -> prev = ultimo; //segundo paso: el nuevo nodo tiene que apuntar al previus que era el ultimo
    lista -> tail = nodo; // tercero: el tail va a ser el nuevo nodo (si lo haciamos antes perdiamos el ultimo)
    lista -> n += 1; // se le agrego un elemento

}

//simplemente enlazadas

void destruir_lista(Lista_t * lista){

    if (lista-> n == 0){
        free(lista);
    }

    Nodo_t * actual = lista -> head;
    Nodo_t * siguiente = lista -> head;

    while ( actual -> next) { // mientras no sea NULL
        siguiente = actual -> next; // te moves al siguiente
        free(actual);
        actual = siguiente;
    }

    free(actual); //destruyo el ultimo elemento (que apunta a NULL --> no entra al while)
    free(lista); // destruyo lista
}

//doblemente enlazadas

void destruir_lista2(Lista2_t * lista){

    Nodo2_t * actual = lista -> head;
    Nodo2_t * siguiente = lista -> head;

    while ( actual -> next) { // mientras no sea NULL
        siguiente = actual -> next; // te moves al siguiente
        free(actual);
        actual = siguiente;
    }

    free(actual); //destruyo el ultimo elemento (que apunta a NULL --> no entra al while)
    free(lista); // destruyo lista
}

//simplemente

int obtener_primero(Lista_t * lista){
    return lista->head -> value;
}

//doblemente

int obtener_primero2(Lista2_t * lista){
    return lista->head -> value;
}

int obtener_ultimo2(Lista2_t * lista){
    return lista->tail -> value;
}

//simplemente

void lista_insertar_primero(Lista_t * lista, int dato){
    Nodo_t * nuevo_primero = (Nodo_t *) malloc(sizeof(Nodo_t));
    nuevo_primero -> value = dato;
    nuevo_primero -> next = lista -> head;
    lista -> head = nuevo_primero;

    lista -> n +=1;
}

void lista_insertar_primero_(Lista_t * lista, int dato){
    Nodo_t * nuevo_primero = (Nodo_t *) malloc(sizeof(Nodo_t));

    nuevo_primero -> value = dato;
    nuevo_primero -> next = lista -> head;
    lista -> head = nuevo_primero;

    lista -> n +=1;
}

//doblemente

void lista_insertar_primero2(Lista2_t * lista, int dato){
    Nodo2_t * nuevo_primero = (Nodo2_t *) malloc(sizeof(Nodo2_t));
    if (NULL == nuevo_primero){
        return;
    }
    nuevo_primero -> value = dato;
    nuevo_primero -> next = lista -> head;
    lista -> head -> prev = nuevo_primero;
    nuevo_primero -> prev = NULL;
    lista -> head = nuevo_primero;

    lista -> n +=1;
}

//simplemente

void lista_borrar_primero(Lista_t * lista){

    Nodo_t * primero = lista -> head;
    lista -> head = primero -> next;
    lista-> n --;
    free(primero);
}

//doblemente

void lista_borrar_primero2(Lista2_t * lista){
    
    Nodo2_t * primero = lista -> head; 
    Nodo2_t * segundo = primero -> next;
    segundo -> prev = NULL;
    lista -> head = segundo;
    lista -> n --;
    free(primero);
}

//EJERCICIO 5.2 PALINDROMO

bool is_palindrome(Lista2_t * lista){
    if (lista->n == 1){
        return true;
    }
    int q = (int)(lista->n/2); // PAR: N/2 CHEQUEOS, IMPAR N-1 / 2 CHEQUEOS --> INT REDONDEA PARA ABAJO
    Nodo2_t * n1 = lista -> head;
    Nodo2_t * n2 = lista -> tail;

    for (int i = 0; i < q; i++) {
        if (n1 -> value != n2-> value ){
            return false;
        }
        n1 = n1 -> next;
        n2 = n2 -> prev;
    }

    return true;

}



//EJERCICIO 5.3.1

Lista2_t* concatenate (Lista2_t* l1, Lista2_t* l2){ 

    Lista2_t * new_list = ( Lista2_t *) malloc (sizeof(Lista2_t));
    if (NULL == new_list){
        return NULL;
    }

    l1->tail->next = l2->head;
    l2->head->prev = l1->tail;

    new_list -> head = l1 -> head;
    new_list -> tail = l2 -> tail;
    new_list -> n = l1 -> n + l2 -> n;
    free(l1);
    free(l2);

    return new_list;
}

////EJERCICIO 5.3.2

Lista2_t* intercalate (Lista2_t* l1, Lista2_t* l2){ //MISMO TAMANO L1 Y L2

    // va de a dos porque es nodo de l1 + nodo de l2 pero el proximo paso
    // como estas parado en nodo de l2 vas a tener que unir con nodo de l1

    Lista2_t * new_list = ( Lista2_t *) malloc (sizeof(Lista2_t));
    if (NULL == new_list){
        return NULL;
    }

    Nodo2_t* act1 = l1->head;
    Nodo2_t* act2 = l2->head;

    while(act1->next){

        Nodo2_t* sig1 = act1 -> next;
        Nodo2_t* sig2 = act2 -> next;
            
        act1->next = act2;
        act2->prev = act1;

        act2->next = sig1;
        sig1->prev = act2;

        act1 = sig1;
        act2 = sig2;
    }

    l1->tail->next = act2;
    act2->prev =  l1->tail;
   
    new_list -> head = l1 -> head;
    new_list -> tail = l2 -> tail;
    new_list -> n = l1 -> n + l2 -> n;
    free(l1);
    free(l2);

    return new_list;
}

Lista2_t * sandwich (Lista2_t* l1, Lista2_t* l2){

    if (l1->n == l2->n)
        return intercalate(l1, l2);
    

    Lista2_t *lista_larga = l1->n > l2->n ? l1 : l2;
    Lista2_t *lista_corta = lista_larga == l1 ? l2 : l1;

    
    Nodo2_t * aux;
    Nodo2_t * tail_aux = l1->tail;
    Nodo2_t * actual = l1->head;

        for(int i = 0; i < l2->n; i++){ // hasta l2 -> van a ser iguales en tamano
           
            if (i == l2->n - 1 ){
                aux = actual->next;
                aux -> prev = NULL;

                actual -> next = NULL; //Cuando hago intercalate las dos listas parecen del mismo largo porq terminan cuando apunta a null
                l1->tail = actual; // el tail de l1 (el largo) va a ser el elemento q apunta a null (simular el mismo largo de l2)
            }

            actual = actual -> next;
        }

        Lista2_t * new_list = intercalate (l1, l2);

        new_list->tail->next = aux;
        aux -> prev =  new_list->tail;
        new_list->tail = tail_aux;

        free(l1);
        free(l2);

        return new_list;


    
}




void funciones_simplemente_enlazadas(){

    Nodo_t * nodo1 = (Nodo_t *)malloc (sizeof(Nodo_t));
    nodo1 -> value = 1;
    nodo1 -> next = NULL;
    Lista_t * lista = inicializacion(nodo1);
    insertar_ultimo(lista, 2);
    insertar_ultimo(lista, 2);
    insertar_ultimo(lista, 5);

    //printf( "el primer elemento de la lista es %i", *((int *)obtener_primero(lista)));
    printf( "el primer elemento de la lista es %i\n", obtener_primero(lista));
    lista_insertar_primero(lista, 8);
    printf( "el primer elemento de la lista es %i\n", obtener_primero(lista));
    lista_borrar_primero(lista);
    printf( "el primer elemento de la lista es %i\n", obtener_primero(lista));
    destruir_lista(lista);
}

void funciones_doblemente_enlazadas(){

    Nodo2_t * nodo1 = (Nodo2_t *)malloc (sizeof(Nodo2_t));
    nodo1 -> value = 1;
    nodo1 -> next = NULL;
    nodo1 -> prev = NULL;
    Lista2_t * lista = inicializacion2(nodo1);

    printf( "el primer elemento de la lista es %i\n", obtener_primero2(lista));
    insertar_ultimo2(lista, 3);
    printf( "el ultimo elemento de la lista es %i\n", obtener_ultimo2(lista) ); //lista->tail->value
    lista_insertar_primero2(lista, 5);
    printf( "el primer elemento de la lista es %i\n", obtener_primero2(lista));
    lista_borrar_primero2(lista);
    printf( "el primer elemento de la lista es %i\n", obtener_primero2(lista));
    destruir_lista2(lista);
}

void ej5_2(){
    Nodo2_t * nodo1 = (Nodo2_t *)malloc(sizeof(Nodo2_t));
    nodo1 -> value = 1;
    nodo1 -> next = NULL;
    nodo1 -> prev = NULL;
    Lista2_t * lista = inicializacion2(nodo1);
    insertar_ultimo2(lista, 3);
    insertar_ultimo2(lista, 3);
    insertar_ultimo2(lista, 1);

    if (is_palindrome(lista)){
        printf("ES PALINDROMA\n");
    }

    destruir_lista2(lista);

    
}

void ej5_3_1(){
    Nodo2_t * nodo1 = (Nodo2_t *)malloc(sizeof(Nodo2_t));
    nodo1 -> value = 1;
    nodo1 -> next = NULL;
    nodo1 -> prev = NULL;
    Lista2_t * lista1 = inicializacion2(nodo1);
    insertar_ultimo2(lista1, 3);

    Nodo2_t * nodo2 = (Nodo2_t *)malloc(sizeof(Nodo2_t));
    nodo2 -> value = 1;
    nodo2 -> next = NULL;
    nodo2 -> prev = NULL;
    Lista2_t * lista2 = inicializacion2(nodo2);
    insertar_ultimo2(lista2, 3);

    Lista2_t * new = concatenate(lista1, lista2);
    
    Nodo2_t * actual = new->head;
    while(actual){
        printf(" %i ,", actual-> value );
        actual = actual -> next;
    }
    printf("\n");

    destruir_lista2(new);
    
}

void ej5_3_2(){
    Nodo2_t * nodo1 = (Nodo2_t *)malloc(sizeof(Nodo2_t));
    nodo1 -> value = 1;
    nodo1 -> next = NULL;
    nodo1 -> prev = NULL;
    Lista2_t * lista1 = inicializacion2(nodo1);
    insertar_ultimo2(lista1, 3);

    Nodo2_t * nodo2 = (Nodo2_t *)malloc(sizeof(Nodo2_t));
    nodo2 -> value = 1;
    nodo2 -> next = NULL;
    nodo2 -> prev = NULL;
    Lista2_t * lista2 = inicializacion2(nodo2);
    insertar_ultimo2(lista2, 3);

    Lista2_t * new = intercalate(lista1, lista2);
    
    Nodo2_t * actual = new->head;
    while(actual){
        printf(" %i ,", actual-> value );
        actual = actual -> next;
    }
    printf("\n");

    destruir_lista2(new);
}

void ej5_3_22(){
    Nodo2_t * nodo1 = (Nodo2_t *)malloc(sizeof(Nodo2_t));
    nodo1 -> value = 1;
    nodo1 -> next = NULL;
    nodo1 -> prev = NULL;
    Lista2_t * lista1 = inicializacion2(nodo1);
    insertar_ultimo2(lista1, 3);
    insertar_ultimo2(lista1, 3);

    Nodo2_t * nodo2 = (Nodo2_t *)malloc(sizeof(Nodo2_t));
    nodo2 -> value = 1;
    nodo2 -> next = NULL;
    nodo2 -> prev = NULL;
    Lista2_t * lista2 = inicializacion2(nodo2);
    insertar_ultimo2(lista2, 3);

    Lista2_t * new = sandwich(lista1, lista2);

    
    Nodo2_t * actual = new->head;
    while(actual){
        printf(" %i ,", actual-> value );
        actual = actual -> next;
    }
    printf("\n");

    destruir_lista2(new);
}
// int main(){
//     //funciones_simplemente_enlazadas();
//     //funciones_doblemente_enlazadas();
//     ej5_3_22();



// }

