#include "tp3.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct node;
typedef struct node node_t;
struct list;
typedef struct list list_t;
struct iterator;
typedef struct list_iter list_iter_t;

struct node {
  const char *key;
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

struct dictionary {
  destroy_f destroy;
  size_t size;
  size_t capacity;
  list_t *buckets[10];
};

// Funcion adicional para crear un nodo
node_t *node_new(const char* key, void *value) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (!new_node)
    return NULL;
  new_node->key = key;
  new_node->value = value;
  new_node->next = NULL;
  new_node->prev = NULL;
  return new_node;
}

list_t *list_new() {
  list_t *new_list = (list_t *)malloc(sizeof(list_t));
  if (!new_list)
    return NULL;
  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->size = 0;
  return new_list;
}

size_t list_length(const list_t *list) { return list->size; }

bool list_is_empty(const list_t *list) {
  if (list->size == 0)
    return true;
  else
    return false;
}

bool list_insert_head(list_t *list, const char* key, void *value) {
  node_t *new_node = node_new(key, value);
  if (!new_node)
    return false;
  new_node->next = list->head;
  if (list->head != NULL)
    list->head->prev = new_node;
  list->head = new_node;
  if (!list->tail)
    list->tail = new_node;
  list->size++;
  return true;
}

bool list_insert_tail(list_t *list, const char* key, void *value) {
  node_t *new_node = node_new(key, value);
  if (!new_node)
    return false;
  new_node->prev = list->tail;
  if (list->tail != NULL)
    list->tail->next = new_node;
  list->tail = new_node;
  if (!list->head)
    list->head = new_node;
  list->size++;
  return true;
}

void *list_peek_head(const list_t *list) {
  if (list_is_empty(list))
    return NULL;
  return list->head->value;
}

void *list_peek_tail(const list_t *list) {
  if (list_is_empty(list))
    return NULL;
  return list->tail->value;
}

void *list_pop_head(list_t *list) {
  if (list_is_empty(list))
    return NULL;
  node_t *aux_head = list->head;
  void *head_value = aux_head->value;
  list->head = aux_head->next;
  if (!list->head)
    list->tail = NULL;
  else
    list->head->prev = NULL;
  list->size--;
  free(aux_head);
  return head_value;
}

void *list_pop_tail(list_t *list) {
  if (list_is_empty(list))
    return NULL;
  node_t *aux_tail = list->tail;
  void *tail_value = aux_tail->value;
  list->tail = aux_tail->prev;
  if (!list->tail)
    list->head = NULL;
  else
    list->tail->next = NULL;
  list->size--;
  free(aux_tail);
  return tail_value;
}

void list_destroy(list_t *list, void destroy_value(void *)) {
  while (list->head != NULL) {
    if (destroy_value != NULL) destroy_value(list->head->value);
    list_pop_head(list);
  }
  free(list);
}

list_iter_t *list_iter_create_head(list_t *list) {
  list_iter_t *new_head_iter = (list_iter_t *)malloc(sizeof(list_iter_t));
  if (!new_head_iter) return NULL;
  new_head_iter->list = list;
  new_head_iter->curr = list->head;
  return new_head_iter;
}

list_iter_t *list_iter_create_tail(list_t *list) {
  list_iter_t *new_tail_iter = (list_iter_t *)malloc(sizeof(list_iter_t));
  if (!new_tail_iter) return NULL;
  new_tail_iter->list = list;
  new_tail_iter->curr = list->tail;
  return new_tail_iter;
}

bool list_iter_forward(list_iter_t *iter) {
  if (!iter->curr || !iter->curr->next) return false;
  else iter->curr = iter->curr->next;
  return true;
}

bool list_iter_backward(list_iter_t *iter) {
  if (!iter->curr || !iter->curr->prev) return false;
  else iter->curr = iter->curr->prev;
  return true;
}

void *list_iter_peek_current_value(const list_iter_t *iter) {
  if (list_is_empty(iter->list)) return NULL;
  return iter->curr->value;
}


const char *list_iter_peek_current_key(const list_iter_t *iter) {
  if (list_is_empty(iter->list)) return NULL;
  return iter->curr->key;
}

bool list_iter_at_last(const list_iter_t *iter) {
  if (iter->curr == iter->list->tail)
    return true;
  else
    return false;
}

bool list_iter_at_first(const list_iter_t *iter) {
  if (iter->curr == iter->list->head)
    return true;
  else
    return false;
}

void list_iter_destroy(list_iter_t *iter) { free(iter); }

bool list_iter_insert_after(list_iter_t *iter, const char* key, void *value) {
  node_t *insert_node = node_new(key, value);
  if (!insert_node)
    return false;
  if (list_is_empty(iter->list)) {
    iter->curr = insert_node;
    iter->list->head = insert_node;
    iter->list->tail = insert_node;
    iter->list->size++;
    return true;
  } else {
    insert_node->next = iter->curr->next;
    insert_node->prev = iter->curr;
    if (iter->curr->next != NULL)
      iter->curr->next->prev = insert_node;
    iter->curr->next = insert_node;
    if (iter->curr == iter->list->tail)
      iter->list->tail = insert_node;
    iter->list->size++;
    return true;
  }
}

bool list_iter_insert_before(list_iter_t *iter, const char* key, void *value) {
  node_t *insert_node = node_new(key, value);
  if (!insert_node)
    return false;
  if (list_is_empty(iter->list)) {
    iter->curr = insert_node;
    iter->list->head = insert_node;
    iter->list->tail = insert_node;
    iter->list->size++;
    return true;
  } else {
    insert_node->next = iter->curr;
    insert_node->prev = iter->curr->prev;
    if (iter->curr->prev != NULL)
      iter->curr->prev->next = insert_node;
    iter->curr->prev = insert_node;
    if (iter->curr == iter->list->head)
      iter->list->head = insert_node;
    iter->list->size++;
    return true;
  }
}

void *list_iter_delete(list_iter_t *iter) {
  if (list_is_empty(iter->list))
    return NULL;
  node_t *delete_node = iter->curr;
  void *delete_value = delete_node->value;
  if (iter->curr->prev != NULL)
    iter->curr->prev->next = iter->curr->next;
  if (iter->curr->next != NULL)
    iter->curr->next->prev = iter->curr->prev;
  if (iter->curr == iter->list->head)
    iter->list->head = iter->curr->next;
  if (iter->curr == iter->list->tail)
    iter->list->tail = iter->curr->prev;
  if (!iter->curr->next)
    list_iter_backward(iter);
  else
    list_iter_forward(iter);
  iter->list->size--;
  free(delete_node);
  return delete_value;
}

//Función de Hashing
unsigned long hash_function(const char *str) {
    unsigned long hash = 0;
    size_t length = strlen(str);
    size_t i;

    for (i = 0; i < length; ++i) {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash % 10; // Tamaño de la tabla de hash
}

dictionary_t *dictionary_create(destroy_f destroy) { 
  dictionary_t *dic = malloc(sizeof(dictionary_t));
  if (!dic) return NULL;
  for(int i = 0; i < 10; i++){
    dic->buckets[i] = list_new();
    if (!dic->buckets[i]) return NULL;
  }
  dic->destroy = destroy;
  dic->size = 0;
  dic->capacity = 10;
  return dic;
}

bool dictionary_put(dictionary_t *dictionary, const char *key, void *value) {
  long unsigned int index = hash_function(key);
  if(list_is_empty(dictionary->buckets[index])){
    if(!list_insert_head(dictionary->buckets[index], key, value)) return false;
    dictionary->size++;
    return true;
  }
  list_iter_t *iter = list_iter_create_head(dictionary->buckets[index]);
  if(!iter) return false;
  while(!list_iter_at_last(iter)){
    if(strcmp(list_iter_peek_current_key(iter), key) == 0){
      if(!list_iter_insert_after(iter, key, value)) return false;
      list_iter_delete(iter);
      dictionary->size++;
      return true;
    }
    list_iter_forward(iter);
  }
  if(strcmp(list_iter_peek_current_key(iter), key) == 0){
    if(!list_iter_insert_after(iter, key, value)) return false;
    list_iter_delete(iter);
    dictionary->size++;
    return true;
  }
  if(!list_iter_insert_after(iter, key, value)) return false;
  list_iter_delete(iter);
  dictionary->size++;
  return true;
}

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  long unsigned int index = hash_function(key);
  if(list_is_empty(dictionary->buckets[index])){
    *err = true;
    return NULL;
  }
  list_iter_t *iter = list_iter_create_head(dictionary->buckets[index]);
  if(!iter){
    *err = true;
    return NULL;
  }
  while(!list_iter_at_last(iter)){
    if(strcmp(list_iter_peek_current_key(iter), key) == 0){
      void *value = list_iter_peek_current_value(iter);
      list_iter_destroy(iter);
      *err = false;
      return value;
    }
    list_iter_forward(iter);
  }
  if(strcmp(list_iter_peek_current_key(iter), key) == 0){
    void *value = list_iter_peek_current_value(iter);
    list_iter_destroy(iter);
    *err = false;
    return value;
  }
  list_iter_destroy(iter);
  *err = true;
  return NULL;
};

bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  long unsigned int index = hash_function(key);
  if(list_is_empty(dictionary->buckets[index])) return false;
  list_iter_t *iter = list_iter_create_head(dictionary->buckets[index]);
  if(!iter) return false;
  while(!list_iter_at_last(iter)){
    if(strcmp(list_iter_peek_current_key(iter), key) == 0){
      list_iter_delete(iter);
      dictionary->size--;
      return true;
    }
    list_iter_forward(iter);
  }
  if(strcmp(list_iter_peek_current_key(iter), key) == 0){
    list_iter_delete(iter);
    dictionary->size--;
    return true;
  }
  list_iter_destroy(iter);
  return false;
}
void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
  long unsigned int index = hash_function(key);
  if(list_is_empty(dictionary->buckets[index])){
    *err = true;
    return NULL;
  }
  list_iter_t *iter = list_iter_create_head(dictionary->buckets[index]);
  if(!iter){
    *err = true;
    return NULL;
  }
  while(!list_iter_at_last(iter)){
    if(strcmp(list_iter_peek_current_key(iter), key) == 0){
      void *value = list_iter_delete(iter);
      list_iter_delete(iter);
      dictionary->size--;
      *err = false;
      return value;
    }
    list_iter_forward(iter);
  }
  

  return NULL;
};

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  return true;
};

size_t dictionary_size(dictionary_t *dictionary) { return dictionary->size; };

void dictionary_destroy(dictionary_t *dictionary){};
