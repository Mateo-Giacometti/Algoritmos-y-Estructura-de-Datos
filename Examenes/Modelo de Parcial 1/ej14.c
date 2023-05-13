#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
Programar una función que busque si un cierto número existe en una lista circular.
*/

struct node;
typedef struct node node_t;
struct circ_list;
typedef struct circ_list circ_list_t;

struct node {
  void *value;
  node_t *next;
};

struct circ_list {
  node_t *curr;
  size_t size;
};

circ_list_t *circ_list_new() {
  circ_list_t *new_list = (circ_list_t *) malloc(sizeof(circ_list_t));
  if(!new_list) return NULL;
  new_list->curr = NULL;
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

size_t circ_list_length(const circ_list_t *list) {return list->size;}

bool circ_list_is_empty(const circ_list_t *list) {
  if(list->size == 0) return true;
  else return false;
}

bool circ_list_insert(circ_list_t *list, node_t *node) {
  if(!node) return false;
  if(circ_list_is_empty(list)){
    list->curr = node;
    node->next = NULL;
    list->size++;
    return true;
  }
  else{
    node->next = list->curr->next;
    list->curr->next = node;
    list->size++;
    return true;
  }
}

bool circ_list_find(circ_list_t *list, node_t *node) {
  if(circ_list_is_empty(list)) return false;
  node_t *aux = list->curr;
  do{
    if(aux->value == node->value) return true;
    aux = aux->next;
  }while(aux != list->curr && aux != NULL);
  return false;
}

int main(){
    circ_list_t *list = circ_list_new();
    int a = 1;
    float b = 2.34;
    char c = 'c';
    long int d = 4;
    double e = 5;
    bool f = true;

    node_t *A = node_new(&a);
    node_t *B = node_new(&b);
    node_t *C = node_new(&c);
    node_t *D = node_new(&d);
    node_t *E = node_new(&e);
    node_t *F = node_new(&f);

    circ_list_insert(list, A);
    circ_list_insert(list, B);
    circ_list_insert(list, C);
    circ_list_insert(list, D);
    circ_list_insert(list, E);

    if(circ_list_find(list, D)) printf("Encontrado\n");
    else printf("No encontrado\n");
    if(circ_list_find(list, F)) printf("Encontrado\n");
    else printf("No encontrado\n");
    return 0;
}
    





