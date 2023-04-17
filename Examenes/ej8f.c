#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
Dada una lista simplemente enlazada crear una función que elimine el “n-ésimo” nodo
contando desde el último elemento. (por ejemplo si n =0 tiene que eliminar el último nodo, si
n=1 tiene que eliminar el ante-último nodo, etc).
Codificar la función bool remove_nth_last(struct Node* head) en O(n).
Muchos puntos extras: Hacer la función recorriendo la lista una sola vez.
*/

struct node;
typedef struct node node_t;
struct list;
typedef struct list list_t;

struct node {
  void *value;
  node_t *next;
};

struct list {
  node_t *head;
  size_t size;
};

list_t *list_new() {
  list_t *new_list = (list_t *) malloc(sizeof(list_t));
  if(!new_list) return NULL;
  new_list->head = NULL;
  new_list->size = 0;
  return new_list;
}

node_t *node_new(void *value) {
  node_t *new_node = (node_t *) malloc(sizeof(node_t));
  if(!new_node) return NULL;
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

size_t list_length(const list_t *list) {return list->size;}

bool list_is_empty(const list_t *list) {
  if(list->size == 0) return true;
  else return false;
}

bool remove_nth_last(list_t *list, size_t n_elem){
    if(list_is_empty(list)) return false;
    int count = 0;
    int count2 = 1;
    node_t *aux = list->head;
    node_t *aux2 = list->head;
    while(aux != NULL) {
        aux = aux->next;
        count++;
    }
    if(count < n_elem) return false;
    if(count == n_elem){
        list->head = NULL;
        free(aux);
        free(aux2);
        return true;
    }
    while(count2 < (count - n_elem)){
        aux = aux2;
        aux2 = aux2->next;
        count2++;
    }
    if(count2 == count){
        aux->next = NULL;
        free(aux2);
        return true;
    }
    aux->next = aux2->next;
    free(aux2);
    return true;
}
