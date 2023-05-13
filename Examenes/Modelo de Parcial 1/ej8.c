#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
Dada una lista simplemente enlazada crear una función que elimine el “n-ésimo”
nodo contando desde el último elemento. (por ejemplo si n =0 tiene que eliminar
el último nodo, si n=1 tiene que eliminar el ante-último nodo, etc). Codificar
la función bool remove_nth_last(struct Node* head) en O(n). Muchos puntos
extras: Hacer la función recorriendo la lista una sola vez.
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
  list_t *new_list = (list_t *)malloc(sizeof(list_t));
  if (!new_list) return NULL;
  new_list->head = NULL;
  new_list->size = 0;
  return new_list;
}

node_t *node_new(void *value) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (!new_node) return NULL;
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

size_t list_length(const list_t *list) { return list->size; }

bool list_is_empty(const list_t *list) {
  if (list->size == 0) return true;
  else return false;
}

bool list_insert_head(list_t *list, void *value) {
  node_t *new_node = node_new(value);
  if(!new_node) return false;
  new_node->next = list->head;
  list->head = new_node;
  list->size++;
  return true;
}

bool remove_nth_last(list_t *list, size_t n_elem) {
  if(list_is_empty(list)) return false;
  int count = 0;
  node_t *aux = list->head;
  while(aux != NULL) {
    aux = aux->next;
    count++;
  }
  if(count < n_elem) return false;
  if(count == n_elem) {
    list->head = NULL;
    return true;
  }
  aux = list->head;
  for(int i = 0; i < count - n_elem - 1; i++) {
    aux = aux->next;
  }
  aux->next = NULL;
  return true;
}

bool remove_nth_last_ef(list_t *list, size_t n_elem) {
  if(list_is_empty(list)) return false;
  node_t *aux = list->head;
  node_t *aux2 = list->head;
  for(size_t i = 0; i < n_elem; i++) {
    aux2 = aux2->next;
  }
  if(aux2 == NULL) {
    list->head = NULL;
    return true;
  }
  while(aux2->next != NULL) {
    aux = aux->next;
    aux2 = aux2->next;
  }
  aux->next = NULL;
  return true;
}

void list_destroy(list_t *list) {
  node_t *aux = list->head;
  while (aux != NULL) {
    node_t *next = aux->next;
    free(aux);
    aux = next;
  }
  free(list);
}

void list_print(const list_t *list) {
  node_t *aux = list->head;
  while (aux != NULL) {
    printf("%d ", *(int *)aux->value);
    aux = aux->next;
  }
}

int main(void) {
  list_t *list = list_new();
  list_t *list2 = list_new();
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  int e = 5;
  int f = 6;

  int g = 7;
  int h = 8;
  int i = 9;
  int j = 10;
  int k = 11;
  int l = 12;

  list_insert_head(list, &a);
  list_insert_head(list, &b);
  list_insert_head(list, &c);
  list_insert_head(list, &d);
  list_insert_head(list, &e);
  list_insert_head(list, &f);

  list_insert_head(list2, &g);
  list_insert_head(list2, &h);
  list_insert_head(list2, &i);
  list_insert_head(list2, &j);
  list_insert_head(list2, &k);
  list_insert_head(list2, &l);

  //Primer prueba de remove_nth_last
  list_print(list);
  puts("");

  remove_nth_last(list, 6);

  list_print(list);
  puts("");

  list_destroy(list);

  //Segunda prueba de remove_nth_last_ef

  list_print(list2);
  puts("");

  remove_nth_last_ef(list2, 3);

  list_print(list2);
  puts("");

  return 0;
}
