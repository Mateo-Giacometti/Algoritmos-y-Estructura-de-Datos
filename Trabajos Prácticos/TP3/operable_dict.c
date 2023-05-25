#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "operable_dict.h"

//Funciones adicionales para operable dict

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


bool or_insert(dictionary_t *new_dictionary, dictionary_t *dict_insert){
  int num_of_inserts = 0;
  for(int i = 0; i < dict_insert->capacity; i++){
    if(dict_insert->nodes[i].key != NULL){
      if(!dictionary_put(new_dictionary, dict_insert->nodes[i].key, dict_insert->nodes[i].value)){
        dictionary_destroy(new_dictionary);
        return false;
      }
      num_of_inserts++;
      if(num_of_inserts == dict_insert->size) break;
    }
  }
  return true;
};

bool are_equal(dictionary_t *dict1, dictionary_t *dict2){
  bool err = false;
  for(int i = 0; i < dict1->capacity; i++){
    if(dict1->nodes[i].key != NULL){
      if(dict1->nodes[i].value != dictionary_get(dict2, dict1->nodes[i].key, &err) || err == true) return false;
    }
  }
  return true;
};


//Funciones dadas por la actividad

bool dictionary_update(dictionary_t *dictionary1, dictionary_t *dictionary2){
  if(!dictionary1 || !dictionary2) return false;
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
  dictionary_t *new_dictionary = dictionary_create(dictionary1->destroy);
  if(!new_dictionary) return NULL;
  if(dictionary1->size <= dictionary2->size) return and_insert(new_dictionary, dictionary1, dictionary2, true); //Me fijo por capacity o por size ?
  else return and_insert(new_dictionary, dictionary2, dictionary1, false);
}; //Por las dudas le daria otros vistaso


dictionary_t* dictionary_or(dictionary_t *dictionary1, dictionary_t *dictionary2){ 
  dictionary_t *new_dictionary = dictionary_create(dictionary1->destroy);
  if(!new_dictionary) return NULL;
  if(!or_insert(new_dictionary, dictionary2) || !or_insert(new_dictionary, dictionary1)){ //Esta bien el orden ?
    dictionary_destroy(new_dictionary);
    return NULL;
  }
  return new_dictionary;
}; //Revisado. Capaz se puede reutilizar código 


bool dictionary_equals(dictionary_t *dictionary1, dictionary_t *dictionary2){ //Podrias agregar una forma de cortar el for si es que ya se analizaron todos los nodos llenos 
  if(dictionary1->size != dictionary2->size) return false;
  if(dictionary1->capacity <= dictionary2->capacity) return are_equal(dictionary1, dictionary2);
  else return are_equal(dictionary2, dictionary1);
}; //Revisada relativamente

