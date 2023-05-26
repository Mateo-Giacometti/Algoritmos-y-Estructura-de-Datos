#include <stdbool.h>
#include <stddef.h>

#ifndef TP3_H
#define TP3_H


typedef void (*destroy_f)(void *);

typedef struct dic_node{
  char *key;
  void *value;
  bool deleted;
}dic_node_t;

typedef struct dictionary {
  destroy_f destroy;
  size_t size;
  size_t capacity;
  double charge_factor;
  dic_node_t *nodes;
}dictionary_t;

/*Aplica hashing a un string*/
unsigned long int hash_function(const char* data, size_t dic_capacity);

/*Aplica rehash a un diccionario*/
bool rehash(dictionary_t *dictionary);

/* Busca el indice de una clave en el diccionario. 
 * Pre-condiciones:
 * - El diccionario existe
 * - La clave tiene largo mayor a cero
 * Post-condiciones:
 * - Retoro el indice de la clave si se encuentra
 * - Retorna -1 si no se encuentra
 */
long unsigned int find_index(dictionary_t *dictionary, const char *key);

/* Crea un nuevo diccionario */
dictionary_t *dictionary_create(destroy_f destroy);

/* Inserta un par clave-valor en el diccionario. O(1).
 * Pre-condiciones:
 * - El diccionario existe
 * - La clave tiene largo mayor a cero
 * - El valor puede ser destruido con la función con la que se inicializó el diccionario.
 * Post-condiciones:
 * - Retorna true si se ha podido guardar con éxito el par clave/valor
 * - Retorna false de otro modo.
 * - Si la clave ya estaba presente, se elimina el valor previo
 */
bool dictionary_put(dictionary_t *dictionary, const char *key, void *value);

/* Obtiene un valor del diccionario desde su clave. O(1).
 * Pre-condiciones
 * - El diccionario existe
 * - La clave tiene largo mayor a cero
 * Post-condiciones:
 * - Si la clave está presente, retorna el valor asociado y err debe ser false
 * - De otro modo, debe retornar NULL y err debe ser true
 */
void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err);

/* Elimina una clave del diccionario. O(1).
 * Pre-condiciones
 * - El diccionario existe
 * - La clave tiene largo mayor a cero
 * Retorna true si la clave estaba presente y se pudo eliminar, o false
 * de otro modo.
 */
bool dictionary_delete(dictionary_t *dictionary, const char *key);

/* Elimina una clave y retorna su valor asociado. O(1).
 * Pre-condiciones:
 * - El diccionario existe
 * - La clave tiene largo mayor a cero
 * Post-condiciones:
 * - Si la calve está presente, retorna el valor asocaido y err debe ser false
 * - De otro modo, debe retornar NULL y err debe ser true
 */
void *dictionary_pop(dictionary_t* dictionary, const char *key, bool *err);

/* Indica si hay un valor asociado a la clave indicada. O(1).
 * Pre-condiciones:
 * - El diccionario existe
 * - La clave tiene largo mayor a cero
 * Post-condiciones:
 * - Retorna true si la clave está presente en el diccionario
 * - Retorna false de otro modo
 */
bool dictionary_contains(dictionary_t *dictionary, const char *key);

/* Indica la cantidad de elementos guardados en el diccionario. O(1).
 * Pre-condiciones:
 * - El diccionario existe
 */
size_t dictionary_size(dictionary_t *dictionary);

/* Destruye el diccionario y los valores asociados a todas las claves presentes.
 * Pre-condiciones:
 * - El diccionario existe
 */
void dictionary_destroy(dictionary_t *dictionary);

#endif
