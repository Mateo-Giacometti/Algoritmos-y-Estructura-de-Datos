#include "tp3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dic_node dic_node_t;


struct dic_node{
  char *key;
  void *value;
  bool deleted;
};

struct dictionary {
  destroy_f destroy;
  size_t size;
  size_t capacity;
  float charge_factor;
  dic_node_t *nodes;
};

/*
unsigned long int hash_function(const char* data, size_t dic_capacity){
    unsigned long int hash = 0xcbf29ce484222325; 

    while (*data != '\0') {
        hash ^= (unsigned long int)*data++; 
        hash *= 0x100000001b3; 
    }

    return hash % dic_capacity; 
}
*/

unsigned long hash_function(const char *str, size_t dic_capacity) {
    unsigned long hash = 0;
    size_t length = strlen(str);
    size_t i;
    for(i = 0; i < length; ++i) {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash % dic_capacity; 
};


long unsigned int find_index(dictionary_t *dictionary, const char *key){ //Las virificaciones siguen sin convencerme 
  long unsigned int hash = hash_function(key, dictionary->capacity);
  bool pos_rep = false;
  if(dictionary->nodes[hash].key == NULL && dictionary->nodes[hash].deleted == false) return -1;
  else if(dictionary->nodes[hash].key == NULL && dictionary->nodes[hash].deleted == true) pos_rep = true;
  for(long unsigned int i = 1; i < dictionary->capacity; i++){
    long unsigned int index = (hash + i) % dictionary->capacity;
    if(dictionary->nodes[index].key != NULL && strcmp(dictionary->nodes[index].key, key) == 0) return index;
    else if(dictionary->nodes[index].key == NULL && dictionary->nodes[index].deleted == false && pos_rep == true) return -1;
  }
  return -1; //Lo rompe ?
};

/*
bool rehash(dictionary_t *dictionary){
  dic_node_t *new_nodes = calloc((dictionary->capacity * 2), sizeof(dic_node_t));
  if(!new_nodes) return false;
  for(int i = 0; i < dictionary->capacity; i++){
    if(dictionary->nodes[i].key){
      long unsigned int hash = hash_function(dictionary->nodes[i].key, dictionary->capacity * 2);
      for(int j = 0; j < dictionary->capacity * 2; j++){
        long unsigned int index = (hash + j) % (dictionary->capacity * 2);
        if(!new_nodes[index].key){
          new_nodes[index].key = dictionary->nodes[i].key;
          new_nodes[index].value = dictionary->nodes[i].value;
          break;
        }
      }
    }
  }
  free(dictionary->nodes);
  dictionary->nodes = new_nodes;
  dictionary->capacity = dictionary->capacity * 2;
  return true;
}

*/
bool rehash(dictionary_t *dictionary){
  dictionary_t aux;
  aux.nodes = calloc((dictionary->capacity * 2), sizeof(dic_node_t));
  if(!aux.nodes) return false;
  aux.capacity = dictionary->capacity * 2;
  aux.size = 0;
  aux.destroy = dictionary->destroy;
  aux.charge_factor = dictionary->charge_factor;
  for(int i = 0; i < dictionary->capacity; i++){
    if(!dictionary_put(&aux, dictionary->nodes[i].key, dictionary->nodes[i].value)){
      free(aux.nodes);
      return false;
    }
    free(dictionary->nodes[i].key);
    if(aux.size == dictionary->size) break;
  }
  free(dictionary->nodes);
  dictionary->nodes = aux.nodes;
  dictionary->capacity = aux.capacity;
  return true;
};


dictionary_t *dictionary_create(destroy_f destroy) { 
  dictionary_t *dic = malloc(sizeof(dictionary_t));
  if(!dic) return NULL;
  dic->nodes = calloc(18, sizeof(dic_node_t));
  if(!dic->nodes) {
    free(dic);
    return NULL;
  }
  if(destroy != NULL) dic->destroy = destroy;
  else dic->destroy = NULL;
  dic->size = 0;
  dic->capacity = 18;
  dic->charge_factor = 0.75;
  return dic;
};


bool dictionary_put(dictionary_t *dictionary, const char *key, void *value) {
  if((dictionary->size / dictionary->capacity) >= (dictionary->charge_factor)){
    if(!rehash(dictionary)) return false;
  }
  long unsigned int aux = -1;
  long unsigned int hash = hash_function(key, dictionary->capacity);
  for(int i = 0; i < dictionary->capacity; i++){
    long unsigned int index = (hash + i) % dictionary->capacity;
    if(!dictionary->nodes[index].key){
      if(dictionary->nodes[index].deleted == true && aux == -1){
        aux = index;
      }
      else if(dictionary->nodes[index].deleted == false){
        if(aux != -1) hash = aux;
        else hash = index;
        dictionary->nodes[hash].key = malloc(sizeof(char) * (strlen(key) + 1));
        if(!dictionary->nodes[hash].key) return false;
        strcpy(dictionary->nodes[hash].key, key);
        dictionary->nodes[hash].value = value;
        if(dictionary->nodes[hash].deleted) dictionary->nodes[hash].deleted = false;
        dictionary->size++;
        return true;
      }
    }
    else if(strcmp(dictionary->nodes[index].key, key) == 0){
      if(dictionary->nodes[index].value != NULL){
        if(dictionary->destroy != NULL) dictionary->destroy(dictionary->nodes[index].value);
      }
      dictionary->nodes[index].value = value;
      return true;
    }
  }
  return false; //Va ?
};

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  long unsigned int index = find_index(dictionary, key);
  if(index == -1){
    *err = true;
    return NULL;
  }
  *err = false;
  return dictionary->nodes[index].value;
};
  
bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  long unsigned int index = find_index(dictionary, key);
  if(index == -1) return false;
  free(dictionary->nodes[index].key);
  dictionary->nodes[index].key = NULL;
  if(dictionary->nodes[index].value != NULL) {
    if(dictionary->destroy != NULL) dictionary->destroy(dictionary->nodes[index].value);
    dictionary->nodes[index].value = NULL;
  }
  dictionary->nodes[index].deleted = true;
  dictionary->size--;
  return true;
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
  long unsigned int index = find_index(dictionary, key);
  if(index == -1){
    *err = true;
    return NULL;
  }
  free(dictionary->nodes[index].key);
  dictionary->nodes[index].key = NULL;
  dictionary->nodes[index].deleted = true;
  dictionary->size--;
  *err = false;
  return dictionary->nodes[index].value;
};

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  long unsigned int index = find_index(dictionary, key);
  if(index == -1) return false;
  else return true;
};

size_t dictionary_size(dictionary_t *dictionary) { return dictionary->size; };

void dictionary_destroy(dictionary_t *dictionary){
  for(int i = 0; i < dictionary->capacity; i++){
    if(dictionary->nodes[i].deleted == false && dictionary->nodes[i].key != NULL){
      if(dictionary->destroy != NULL) dictionary->destroy(dictionary->nodes[i].value);
      free(dictionary->nodes[i].key);
    }
  }
  free(dictionary->nodes);
  free(dictionary);
};
