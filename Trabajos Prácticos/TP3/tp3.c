#include "tp3.h"
#include <string.h>
#include <stdlib.h>

typedef struct dic_node dic_node_t;

struct dic_node{
  char *key;
  void *value;
  bool in_use;
};
struct dictionary {
  destroy_f destroy;
  size_t size;
  size_t capacity;
  dic_node_t *nodes;
};

unsigned long hash_function(const char *str, size_t dic_capacity) {
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

    return hash % dic_capacity; // Tamaño de la tabla de hash
}

dictionary_t *dictionary_create(destroy_f destroy) { 
  dictionary_t *dic = malloc(sizeof(dictionary_t));
  if (!dic) return NULL;
  dic->nodes = malloc(sizeof(dic_node_t) * 100);
  if (!dic->nodes) {
    free(dic);
    return NULL;
  }
  for (int i = 0; i < 100; i++) { //Alguna forma de inicializar a todos en false?
    dic->nodes[i].in_use = false;
  }
  if (destroy != NULL) dic->destroy = destroy;
  if (!destroy) dic->destroy = NULL; //No se si es necesario
  dic->size = 0;
  dic->capacity = 100;
  return dic;
};

bool rehash(dictionary_t *dictionary){
  dic_node_t *new_node = malloc(sizeof(dic_node_t) * (dictionary->capacity * 2)); 
  if (!new_node) return false;
  for (int i = 0; i < dictionary->capacity * 2; i++) {
    new_node[i].in_use = false;
  }
  for(long unsigned int i = 0; i < dictionary->capacity; i++){
    if(dictionary->nodes[i].in_use == true){
      long unsigned int hash = hash_function(dictionary->nodes[i].key, dictionary->capacity * 2);
      for(long unsigned int j = 0; j < dictionary->capacity * 2; j++){
        long unsigned int index = (hash + j) % (dictionary->capacity * 2);
        if(new_node[index].in_use == false || strcmp(new_node[index].key, dictionary->nodes[i].key) == 0){
          hash = index;
          break;
        }
      }
      if(new_node[hash].in_use == false){
      new_node[hash].key = malloc(sizeof(char) * (strlen(dictionary->nodes[i].key) + 1));
      if (!dictionary->nodes[hash].key) return false;
      strcpy(new_node[hash].key, dictionary->nodes[i].key);
      new_node[hash].value = dictionary->nodes[i].value; 
      new_node[hash].in_use = true;
      }
      else{
        if(dictionary->destroy != NULL) dictionary->destroy(new_node[hash].value);
        new_node[hash].value = dictionary->nodes[i].value;
      }
    }
  }
  for(int i = 0; i < dictionary->capacity; i++){
    if(dictionary->nodes[i].in_use == true){
      if(dictionary->destroy != NULL) dictionary->destroy(dictionary->nodes[i].value);
      free(dictionary->nodes[i].key);
    }
  }
  free(dictionary->nodes);
  dictionary->nodes = new_node;
  dictionary->capacity = dictionary->capacity * 2;
  return true;
}


bool dictionary_put(dictionary_t *dictionary, const char *key, void *value) {
  if(dictionary->capacity == dictionary->size){
    if(!rehash(dictionary)) return false;
  }
  long unsigned int hash = hash_function(key, dictionary->capacity);
  for(long unsigned int i = 0; i < dictionary->capacity; i++){
    long unsigned int index = (hash + i) % dictionary->capacity;
    if(dictionary->nodes[index].in_use == false || strcmp(dictionary->nodes[index].key, key) == 0){
      hash = index;
      break;
    }
  }
  if(dictionary->nodes[hash].in_use == false){
    dictionary->nodes[hash].key = malloc(sizeof(char) * (strlen(key) + 1));
    if (!dictionary->nodes[hash].key) return false;
    strcpy(dictionary->nodes[hash].key, key);
    dictionary->nodes[hash].value = value;
    dictionary->size++;
    dictionary->nodes[hash].in_use = true;
  }
  else{
    if(dictionary->destroy != NULL) dictionary->destroy(dictionary->nodes[hash].value);
    dictionary->nodes[hash].value = value;
  }
  return true;

};


void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  long unsigned int hash = hash_function(key, dictionary->capacity);
  for(long unsigned int i = hash; i < dictionary->capacity; i++){
    if((dictionary->nodes[i].in_use == true) && (strcmp(dictionary->nodes[i].key, key) == 0)){
      *err = false;
      return dictionary->nodes[i].value;
    }
  }
  for(long unsigned int j = 0; j < hash; j++){
    if((dictionary->nodes[j].in_use == true) && (strcmp(dictionary->nodes[j].key, key) == 0)){
      *err = false;
      return dictionary->nodes[j].value;
    }
  }
  *err = true;
  return NULL;
};
  
bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  long unsigned int hash = hash_function(key, dictionary->capacity);
  for(long unsigned int i = hash; i < dictionary->capacity; i++){
    if(dictionary->nodes[i].in_use == true && strcmp(dictionary->nodes[i].key, key) == 0){
      free(dictionary->nodes[i].key);
      if(dictionary->destroy != NULL) dictionary->destroy(dictionary->nodes[i].value);
      dictionary->nodes[i].in_use = false;
      dictionary->size--;
      return true;
    }
  }
  for(long unsigned int i = 0; i < hash; i++){
    if(dictionary->nodes[i].in_use == true && strcmp(dictionary->nodes[i].key, key) == 0){
      if(dictionary->destroy != NULL) dictionary->destroy(dictionary->nodes[i].value);
      free(dictionary->nodes[i].key);
      dictionary->nodes[i].in_use = false;
      dictionary->size--;
      return true;
    }
  }
  return false;
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
  long unsigned int hash = hash_function(key, dictionary->capacity);
  for(long unsigned int i = 0; i < dictionary->capacity; i++){
    long unsigned int index = (hash + i) % dictionary->capacity;
    if(dictionary->nodes[index].in_use == true && strcmp(dictionary->nodes[index].key, key) == 0){
      void *value = dictionary->nodes[index].value;
      dictionary->nodes[index].in_use = false; 
      dictionary->size--;
      free(dictionary->nodes[index].key);
      *err = false;
      return value;
    }
  }
  *err = true;
  return NULL;
};

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  long unsigned int hash = hash_function(key, dictionary->capacity);
  for(long unsigned int i = 0; i < dictionary->capacity; i++){
    long unsigned int index = (hash + i) % dictionary->capacity;
    if(dictionary->nodes[index].in_use == true && strcmp(dictionary->nodes[index].key, key) == 0){
      return true;
    }
  }
  return false;
};


size_t dictionary_size(dictionary_t *dictionary) { return dictionary->size; };

void dictionary_destroy(dictionary_t *dictionary){
  for(int i = 0; i < dictionary->capacity; i++){
    if(dictionary->nodes[i].in_use == true){
      if(dictionary->destroy != NULL) dictionary->destroy(dictionary->nodes[i].value);
      free(dictionary->nodes[i].key);
    }
  }
  free(dictionary->nodes);
  free(dictionary);
};
