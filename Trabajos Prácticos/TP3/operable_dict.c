#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "operable_dict.h"

//Funciones adicionales para operable dict

dic_node_t* make_backup(dictionary_t *dictionary){
  dic_node_t *backup = calloc(dictionary->capacity, sizeof(dic_node_t)); 
  if(!backup) return NULL;
  for(int i = 0; i < dictionary->capacity; i++){
    if(dictionary->nodes[i].key != NULL){
      backup[i].key = malloc(sizeof(char) * (strlen(dictionary->nodes[i].key) + 1));
      if(!backup[i].key){
        for(int j = 0; j < i; j++){
          if(backup[j].key != NULL){ 
            free(backup[j].key);
          }
        }
        free(backup);
        return NULL;
      }
      strcpy(backup[i].key, dictionary->nodes[i].key);
      backup[i].value = dictionary->nodes[i].value;
    }
    else if(dictionary->nodes[i].deleted == true){
      backup[i].deleted = true;
    }
  }
  return backup;
};


void delete_backup(dic_node_t *backup, size_t backup_capacity ,size_t backup_size){
  int deleted_nodes = 0;
  for(int k = 0; k < backup_capacity; k++){
    if(backup[k].key != NULL){
      free(backup[k].key);
      deleted_nodes++;
    }
    if(deleted_nodes == backup_size) break;
  }
  free(backup);
};


dictionary_t* and_insert(dictionary_t *new_dictionary, dictionary_t *min_dict, dictionary_t *max_dict, bool dict1_is_min){
  int num_of_inserts = 0;
  for(int i = 0; i < min_dict->capacity; i++){
    if(min_dict->nodes[i].key != NULL && dictionary_contains(max_dict, min_dict->nodes[i].key)){ 
      if(dict1_is_min){
        if(!dictionary_put(new_dictionary, min_dict->nodes[i].key, min_dict->nodes[i].value)){
          new_dictionary->destroy = NULL;
          dictionary_destroy(new_dictionary);
          return NULL;
        }
      }
      else{
        if(!dictionary_put(new_dictionary, max_dict->nodes[i].key, max_dict->nodes[i].value)){
          new_dictionary->destroy = NULL;
          dictionary_destroy(new_dictionary);
          return NULL;
        }
      }
      num_of_inserts++;
    }
    if(num_of_inserts == min_dict->size) break;
  }
  return new_dictionary;
};


bool or_insert(dictionary_t *new_dictionary, dictionary_t *dict_insert){
  int num_of_inserts = 0;
  for(int i = 0; i < dict_insert->capacity; i++){
    if(dict_insert->nodes[i].key != NULL){
      if(!dictionary_put(new_dictionary, dict_insert->nodes[i].key, dict_insert->nodes[i].value)){
        new_dictionary->destroy = NULL;
        dictionary_destroy(new_dictionary);
        return false;
      }
      num_of_inserts++;
    }
    if(num_of_inserts == dict_insert->size) break;
  }
  return true;
};


bool are_equal(dictionary_t *dict1, dictionary_t *dict2){
  bool err = false;
  int num_of_comp = 0;
  for(int i = 0; i < dict1->capacity; i++){
    if(dict1->nodes[i].key != NULL){
      if(dict1->nodes[i].value != dictionary_get(dict2, dict1->nodes[i].key, &err) || err == true) return false;
      num_of_comp++;
    }
    if(num_of_comp == dict1->size) break;
  }
  return true;
};


//Funciones dadas por la actividad

bool dictionary_update(dictionary_t *dictionary1, dictionary_t *dictionary2){
  dic_node_t *backup_nodes = make_backup(dictionary1);
  if(!backup_nodes) return false;
  size_t aux_size = dictionary1->size;
  size_t aux_capacity = dictionary1->capacity;
  int new_nodes_inserted = 0;
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
      new_nodes_inserted++;
    }
    if(new_nodes_inserted == dictionary2->size) break;
  }
  delete_backup(backup_nodes, aux_capacity, aux_size);
  return true;
};


dictionary_t* dictionary_and(dictionary_t *dictionary1, dictionary_t *dictionary2){
  dictionary_t *new_dictionary = dictionary_create(dictionary1->destroy);
  if(!new_dictionary) return NULL;
  if(dictionary1->size <= dictionary2->size) return and_insert(new_dictionary, dictionary1, dictionary2, true); 
  else return and_insert(new_dictionary, dictionary2, dictionary1, false);
}; 


dictionary_t* dictionary_or(dictionary_t *dictionary1, dictionary_t *dictionary2){ 
  dictionary_t *new_dictionary = dictionary_create(dictionary1->destroy);
  if(!new_dictionary) return NULL;
  if(!or_insert(new_dictionary, dictionary2) || !or_insert(new_dictionary, dictionary1)){ 
    return NULL;
  }
  return new_dictionary;
}; 


bool dictionary_equals(dictionary_t *dictionary1, dictionary_t *dictionary2){ 
  if(dictionary1->size != dictionary2->size) return false;
  if(dictionary1->capacity <= dictionary2->capacity) return are_equal(dictionary1, dictionary2);
  else return are_equal(dictionary2, dictionary1);
}; 

