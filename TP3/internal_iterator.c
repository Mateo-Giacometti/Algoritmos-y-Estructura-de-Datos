#include "internal_iterator.h"

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


unsigned long int hash_function(const char* data, size_t dic_capacity){
    unsigned long int hash = 0xcbf29ce484222325; // Valor inicial del hash FNV-1a

    while (*data != '\0') {
        hash ^= (unsigned long int)*data++; // XOR el byte de datos con el hash
        hash *= 0x100000001b3; // Multiplicación por el número primo FNV
    }

    return hash % dic_capacity; // Limitar el valor del hash al rango de 0 a 100
}


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

*/

/*
 * Punto extra de internal iterator, suma 1 punto como máximo.
 */


/*
 * Itera cada par clave-valor del diccionario pasandoselo a la función de iteración.
 * Recibe un parámetro extra que puede contener cualquier cosa para permitirle a la función guardar resultados.
 */

/*
void iterate(dictionary_t* dict, iterate_f f, void* extra){ 
    if(!dict || !f) return; //Preguntar si esta bien
    size_t count = 0;
    for(int i = 0; i < dict->capacity; i++){
        if(dict->nodes[i].key != NULL){
            f(dict->nodes[i].key, dict->nodes[i].value, extra);
            count++;
        }
        if(count == dict->size) break;
    }
    return;
}
*/