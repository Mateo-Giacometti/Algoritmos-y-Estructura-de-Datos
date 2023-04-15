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

bool circ_list_insert(circ_list_t *list, void *value) {
  node_t *new_node = node_new(value);
  if(!new_node) return false;
  if(!list->curr) {
    list->curr = new_node;
    new_node->next = new_node;
  }
  else {
    new_node->next = list->curr->next;
    list->curr->next = new_node;
  }
  list->size++;
  return true;
}

bool circ_list_find(circ_list_t *list, int value) {
  if(list->curr == NULL) return false;
  node_t *curr = list->curr;
  do {
    if(*(int *)curr->value == value) return true;
    curr = curr->next;
  } while(curr != list->curr);
  return false;
}



