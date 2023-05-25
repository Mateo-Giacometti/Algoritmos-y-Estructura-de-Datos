#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "operable_dict.h"

/*
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
  double charge_factor;
  dic_node_t *nodes;
};

//Funciones auxiliares 

unsigned long int hash_function(const char* data, size_t dic_capacity){
    unsigned long int hash = 0xcbf29ce484222325; 

    while (*data != '\0') {
        hash ^= (unsigned long int)*data++; 
        hash *= 0x100000001b3; 
    }

    return hash % dic_capacity; 
};


long unsigned int find_index(dictionary_t *dictionary, const char *key){ //Revisar 
  long unsigned int hash = hash_function(key, dictionary->capacity);
  bool pos_rep = false;
  if(dictionary->nodes[hash].key == NULL && dictionary->nodes[hash].deleted == true) pos_rep = true;
  for(long unsigned int i = 0; i < dictionary->capacity; i++){
    long unsigned int index = (hash + i) % dictionary->capacity;
    if(dictionary->nodes[index].key != NULL && strcmp(dictionary->nodes[index].key, key) == 0) return index;
    else if(dictionary->nodes[index].key == NULL && dictionary->nodes[index].deleted == false && pos_rep == true) return -1;
  }
  return -1; //Lo rompe ?
};


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
};


dictionary_t* and_insert(dictionary_t *new_dictionary, dictionary_t *min_dict, dictionary_t *max_dict, bool dict1_is_min){
  int count = 0;
  for(int i = 0; i < min_dict->capacity; i++){
    if(min_dict->nodes[i].key != NULL && dictionary_contains(max_dict, min_dict->nodes[i].key)){ //Preguntar si no se rompe
      if(dict1_is_min){
        if(!dictionary_put(new_dictionary, min_dict->nodes[i].key, min_dict->nodes[i].value)){
          dictionary_destroy(new_dictionary);
          return NULL;
        }
      }
      else{
        if(!dictionary_put(new_dictionary, max_dict->nodes[i].key, max_dict->nodes[i].value)){
          dictionary_destroy(new_dictionary);
          return NULL;
        }
      }
      count++;
      if(count == min_dict->size) break;
    }
  }
  return new_dictionary;
};


//Funciones dadas por la actividad

bool dictionary_update(dictionary_t *dictionary1, dictionary_t *dictionary2){
  dic_node_t *backup_nodes = calloc(dictionary1->capacity, sizeof(dic_node_t)); 
  if(!backup_nodes) return false;
  size_t aux_size = dictionary1->size;
  size_t aux_capacity = dictionary1->capacity;
  int count = 0;
  for(int i = 0; i < dictionary1->capacity; i++){
    if(dictionary1->nodes[i].key != NULL){
      backup_nodes[i].key = malloc(sizeof(char) * (strlen(dictionary1->nodes[i].key) + 1));
      if(!backup_nodes[i].key){
        for(int j = 0; j < i; j++){
          if(backup_nodes[j].key != NULL){ 
            free(backup_nodes[j].key);
          }
        }
        free(backup_nodes);
        return false;
      }
      strcpy(backup_nodes[i].key, dictionary1->nodes[i].key);
      backup_nodes[i].value = dictionary1->nodes[i].value;
    }
    else if(dictionary1->nodes[i].deleted == true){
      backup_nodes[i].deleted = true;
    }
  }
  for(int j = 0; j < dictionary2->capacity; j++){
    if(dictionary2->nodes[j].key != NULL){
      if(!dictionary_put(dictionary1, dictionary2->nodes[j].key, dictionary2->nodes[j].value)){
        for(int k = 0; k < dictionary1->capacity; k++){
          if(dictionary1->nodes[k].key != NULL){
            free(dictionary1->nodes[k].key); 
          }
        }
        free(dictionary1->nodes); 
        dictionary1->nodes = backup_nodes;
        dictionary1->size = aux_size;
        dictionary1->capacity = aux_capacity;
        return false;
      }
      count++;
      if(count == dictionary2->size) break;
    }
  }
  count = 0;
  for(int k = 0; k < aux_capacity; k++){
    if(backup_nodes[k].key != NULL){
      free(backup_nodes[k].key);
      count++;
      if(count == aux_size) break;
    }
  }
  free(backup_nodes);
  return true;
};//Creo que esta relativamente bien, a pesar de ser muy muy fea


dictionary_t* dictionary_and(dictionary_t *dictionary1, dictionary_t *dictionary2){ // Necesario revisar que diccionary1 y 2 no sean NULL?
  dictionary_t *new_dictionary = dictionary_create(dictionary1->capacity);
  if(!new_dictionary) return NULL;
  if(dictionary1->size <= dictionary2->size) return and_insert(new_dictionary, dictionary1, dictionary2, true); //Me fijo por capacity o por size ?
  else return and_insert(new_dictionary, dictionary2, dictionary1, false);
}; //Por las dudas le daria otros vistaso


dictionary_t* dictionary_or(dictionary_t *dictionary1, dictionary_t *dictionary2){ // Necesario revisar que diccionary1 y 2 no sean NULL? Ver size o capacity ?
  dictionary_t *new_dictionary = dictionary_create(dictionary1->capacity);
  if(!new_dictionary) return NULL;
  int count = 0;
  for(int i = 0; i < dictionary2->capacity; i++){
    if(dictionary2->nodes[i].key != NULL){
      if(!dictionary_put(new_dictionary, dictionary2->nodes[i].key, dictionary2->nodes[i].value)){
        dictionary_destroy(new_dictionary);
        return NULL;
      }
      count++;
      if(count == dictionary2->size) break;
    }
  }
  count = 0;
  for(int j = 0; j < dictionary1->capacity; j++){
    if(dictionary1->nodes[j].key != NULL){
      if(!dictionary_put(new_dictionary, dictionary1->nodes[j].key, dictionary1->nodes[j].value)){
        dictionary_destroy(new_dictionary);
        return NULL;
      }
      count++;
      if(count == dictionary1->size) break;
    }
  }
  return new_dictionary;
}; //Revisado. Capaz se puede reutilizar código 


bool dictionary_equals(dictionary_t *dictionary1, dictionary_t *dictionary2){ //Podrias agregar una forma de cortar el for si es que ya se analizaron todos los nodos llenos 
  if(dictionary1->size != dictionary2->size) return false;
  bool err = false;
  if(dictionary1->capacity <= dictionary2->capacity){
    for(int i = 0; i < dictionary1->capacity; i++){
      if(dictionary1->nodes[i].key != NULL){
        if(dictionary1->nodes[i].value != dictionary_get(dictionary2, dictionary1->nodes[i].key, &err) || err == true){ 
          return false;
        }
      }
    }
  }
  else{
    for(int j = 0; j < dictionary2->capacity; j++){
      if(dictionary2->nodes[j].key != NULL){
        if(dictionary2->nodes[j].value != dictionary_get(dictionary1, dictionary2->nodes[j].key, &err) || err == true){ 
          return false;
        }
      }
    }
  }
  return true;
}; //Revisada relativamente

*/