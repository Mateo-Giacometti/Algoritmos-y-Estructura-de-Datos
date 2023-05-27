#include "tp3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Funciones Adicionales

unsigned long int hash_function(const char* data, size_t dic_capacity){
  unsigned long int hash = 0xcbf29ce484222325; 
  while (*data != '\0') {
    hash ^= (unsigned long int)*data++; 
    hash *= 0x100000001b3; 
  }
  return hash % dic_capacity; 
};


bool rehash(dictionary_t *dictionary){
  dic_node_t *new_nodes = calloc((dictionary->capacity * 2), sizeof(dic_node_t));
  if(!new_nodes) return false;
  int inserted_nodes = 0;
  long unsigned int hash;
  long unsigned int index;
  for(int i = 0; i < dictionary->capacity; i++){
    if(dictionary->nodes[i].key != NULL){
      hash = hash_function(dictionary->nodes[i].key, dictionary->capacity * 2);
      for(int j = 0; j < dictionary->capacity * 2; j++){
        index = (hash + j) % (dictionary->capacity * 2);
        if(!new_nodes[index].key){
          new_nodes[index].key = dictionary->nodes[i].key;
          new_nodes[index].value = dictionary->nodes[i].value;
          inserted_nodes++;
          break;
        }
      }
    }
    if(inserted_nodes == dictionary->size) break; 
  }
  free(dictionary->nodes);
  dictionary->nodes = new_nodes;
  dictionary->capacity = dictionary->capacity * 2;
  return true;
};


long unsigned int find_index(dictionary_t *dictionary, const char *key){ 
  long unsigned int hash = hash_function(key, dictionary->capacity);
  long unsigned int index;
  for(long unsigned int i = 0; i < dictionary->capacity; i++){
    index = (hash + i) % dictionary->capacity;
    if(dictionary->nodes[index].key != NULL && strcmp(dictionary->nodes[index].key, key) == 0) return index;
    else if(dictionary->nodes[index].key == NULL && dictionary->nodes[index].deleted == false) return -1;
  }
  return -1; 
};


dictionary_t *dictionary_create(destroy_f destroy){ 	
  dictionary_t *dict = malloc(sizeof(dictionary_t));
  if(!dict) return NULL;
  dict->nodes = calloc(18, sizeof(dic_node_t));
  if(!dict->nodes) {
    free(dict);
    return NULL;
  }
  if(destroy != NULL) dict->destroy = destroy;
  else dict->destroy = NULL;
  dict->size = 0;
  dict->capacity = 18;
  dict->charge_factor = 0.70; 
  return dict;
};


bool dictionary_put(dictionary_t *dictionary, const char *key, void *value){
  if(((double)dictionary->size / (double)dictionary->capacity) >= (dictionary->charge_factor)){
    if(!rehash(dictionary)) return false;
  }
  bool deleted_place = false;
  long unsigned int index;
  long unsigned int hash = hash_function(key, dictionary->capacity);
  if(dictionary->nodes[hash].deleted == true) deleted_place = true;
  for(int i = 0; i < dictionary->capacity; i++){
    index = (hash + i) % dictionary->capacity;
    if(!dictionary->nodes[index].key && dictionary->nodes[index].deleted == false){
      if(deleted_place) index = hash;
      dictionary->nodes[index].key = malloc(sizeof(char) * (strlen(key) + 1));
      if(!dictionary->nodes[index].key) return false;
      strcpy(dictionary->nodes[index].key, key);
      dictionary->nodes[index].value = value;
      if(dictionary->nodes[index].deleted) dictionary->nodes[index].deleted = false;
      dictionary->size++;
      return true;
    }
    else if(dictionary->nodes[index].key && strcmp(dictionary->nodes[index].key, key) == 0){
      if(dictionary->nodes[index].value != NULL){
        if(dictionary->destroy != NULL) dictionary->destroy(dictionary->nodes[index].value);
      }
      dictionary->nodes[index].value = value;
      return true;
    }
  }
  return false; 
};


void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err){
  long unsigned int index = find_index(dictionary, key);
  if(index == -1){
    *err = true;
    return NULL;
  }
  *err = false;
  return dictionary->nodes[index].value;
};

  
bool dictionary_delete(dictionary_t *dictionary, const char *key){
  long unsigned int index = find_index(dictionary, key);
  if(index == -1) return false;
  free(dictionary->nodes[index].key);
  dictionary->nodes[index].key = NULL;
  if(dictionary->nodes[index].value != NULL){
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
  int used_node_del = 0;  
  for(int i = 0; i < dictionary->capacity; i++){
    if(dictionary->nodes[i].key != NULL){
      if(dictionary->destroy != NULL) dictionary->destroy(dictionary->nodes[i].value);
      free(dictionary->nodes[i].key);
      used_node_del++;
    }
    if(used_node_del == dictionary->size) break;
  }
  free(dictionary->nodes);
  free(dictionary);
};
