#include "tp2.h"
#include <stdbool.h>
#include <stdlib.h>

struct node;
typedef struct node node_t;

struct node {
  void *value;
  node_t *next;
  node_t *prev;
};

struct list {
  node_t *head;
  node_t *tail;
  size_t size;
};

struct list_iter {
  list_t *list;
  node_t *curr;
};

list_t *list_new() {
  list_t *new_list = (list_t *) malloc(sizeof(list_t));
  if(!new_list) return NULL;
  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->size = 0;
  return new_list;
}

size_t list_length(const list_t *list) {return list->size;}

bool list_is_empty(const list_t *list) {
  if(list->size == 0) return true;
  else return false;
}

bool list_insert_head(list_t *list, void *value) {
  node_t *new_node = (node_t *) malloc(sizeof(node_t));
  if(!new_node) return false;
  new_node->value = value;
  new_node->next = list->head;
  new_node->prev = NULL;
  if(list->head != NULL) list->head->prev = new_node;
  list->head = new_node;
  if(!list->tail) list->tail = new_node;
  list->size++;
  return true;
}

bool list_insert_tail(list_t *list, void *value) {
  node_t *new_node = (node_t *) malloc(sizeof(node_t));
  if(!new_node) return false;
  new_node->value = value;
  new_node->next = NULL;
  new_node->prev = list->tail;
  if(list->tail != NULL) list->tail->next = new_node;
  list->tail = new_node;
  if(!list->head) list->head = new_node;
  list->size++;
  return true;
}

void *list_peek_head(const list_t *list) { //Duda
  if(list->size == 0) return NULL;
  return list->head->value;
}

void *list_peek_tail(const list_t *list) { //Duda
  if(list->size == 0) return NULL;
  return list->tail->value;
}

void *list_pop_head(list_t *list) {
  if(list->size == 0) return NULL; 
  node_t *aux_head = list->head;
  void *head_value = aux_head->value;
  list->head = aux_head->next;
  if(!list->head) list->tail = NULL;
  else list->head->prev = NULL;
  list->size--;
  free(aux_head);
  return head_value;
}

void *list_pop_tail(list_t *list) {
  if(list->size == 0) return NULL;
  node_t *aux_tail = list->tail;
  void *tail_value = aux_tail->value;
  list->tail = aux_tail->prev;
  if(!list->tail) list->head = NULL;
  else list->tail->next = NULL;
  list->size--;
  free(aux_tail);
  return tail_value;
}

void list_destroy(list_t *list, void destroy_value(void *)) {
  while(list->head != NULL) {
    if(destroy_value != NULL) destroy_value(list->head->value);
    list_pop_head(list);
  }
  free(list);
}

list_iter_t *list_iter_create_head(list_t *list) {
  list_iter_t *new_head_iter = (list_iter_t *) malloc(sizeof(list_iter_t));
  if(!new_head_iter) return NULL;
  new_head_iter->list = list;
  new_head_iter->curr = list->head;
  return new_head_iter;
}

list_iter_t *list_iter_create_tail(list_t *list) {
  list_iter_t *new_tail_iter = (list_iter_t *) malloc(sizeof(list_iter_t));
  if(!new_tail_iter) return NULL;
  new_tail_iter->list = list;
  new_tail_iter->curr = list->tail;
  return new_tail_iter;
}

bool list_iter_forward(list_iter_t *iter) { 
  if(!iter->curr || !iter->curr->next) return false;
  else iter->curr = iter->curr->next;
  return true;
}

bool list_iter_backward(list_iter_t *iter) { 
  if(!iter->curr || !iter->curr->prev) return false;
  else iter->curr = iter->curr->prev;
  return true;
}

void *list_iter_peek_current(const list_iter_t *iter) { // Duda -- Preguntar por el testeo if(!iter->curr) return NULL;
  if(iter->list->size == 0 || !iter->curr) return NULL;
  return iter->curr->value;
}

bool list_iter_at_last(const list_iter_t *iter) { // Ver
  if(iter->curr == iter->list->tail || iter->list->size == 0) return true;
  else return false;
}

bool list_iter_at_first(const list_iter_t *iter) { // Ver
  if(iter->curr == iter->list->head || iter->list->size == 0) return true;
  else return false;
}

void list_iter_destroy(list_iter_t *iter) {free(iter);}

bool list_iter_insert_after(list_iter_t *iter, void *value) {
  node_t *insert_node = (node_t *) malloc(sizeof(node_t));
  if(!insert_node) return false;
  if(iter->list->size == 0 || !iter->curr) {
    insert_node->value = value;
    insert_node->next = NULL;
    insert_node->prev = NULL;
    iter->curr = insert_node;
    iter->list->head = insert_node;
    iter->list->tail = insert_node;
    iter->list->size++;
    return true;
  }
  insert_node->value = value;
  insert_node->next = iter->curr->next;
  insert_node->prev = iter->curr;
  if(iter->curr->next != NULL) iter->curr->next->prev = insert_node;
  iter->curr->next = insert_node;
  if(iter->curr == iter->list->tail) iter->list->tail = insert_node;
  iter->list->size++;
  return true;
}

bool list_iter_insert_before(list_iter_t *iter, void *value) { // Ver
  node_t *insert_node = (node_t *) malloc(sizeof(node_t));
  if(!insert_node) return false;
  if(iter->list->size == 0 || !iter->curr) {
    insert_node->value = value;
    insert_node->next = NULL;
    insert_node->prev = NULL;
    iter->curr = insert_node;
    iter->list->head = insert_node;
    iter->list->tail = insert_node;
    iter->list->size++;
    return true;
  }
  insert_node->value = value;
  insert_node->next = iter->curr;
  insert_node->prev = iter->curr->prev;
  if(iter->curr->prev != NULL) iter->curr->prev->next = insert_node;
  iter->curr->prev = insert_node;
  if(iter->curr == iter->list->head) iter->list->head = insert_node;
  iter->list->size++;
  return true;
}

void *list_iter_delete(list_iter_t *iter) {
  if(iter->list->size == 0 || !iter->curr) return NULL; 
  node_t *delete_node = iter->curr;
  void *delete_value = delete_node->value;
  if(iter->curr->prev != NULL) iter->curr->prev->next = iter->curr->next;
  if(iter->curr->next != NULL) iter->curr->next->prev = iter->curr->prev;
  if(iter->curr == iter->list->head) iter->list->head = iter->curr->next;
  if(iter->curr == iter->list->tail) iter->list->tail = iter->curr->prev;
  if(!iter->curr->next) iter->curr = iter->curr->prev;
  else iter->curr = iter->curr->next;
  iter->list->size--;
  free(delete_node);
  return delete_value;
}