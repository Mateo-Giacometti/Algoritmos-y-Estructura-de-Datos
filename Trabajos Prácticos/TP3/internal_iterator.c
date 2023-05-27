#include "internal_iterator.h"
#include <stdbool.h>
#include <stdio.h>


/*
 * Punto extra de internal iterator, suma 1 punto como máximo.
 */


/*
 * Itera cada par clave-valor del diccionario pasandoselo a la función de iteración.
 * Recibe un parámetro extra que puede contener cualquier cosa para permitirle a la función guardar resultados.
 */


void iterate(dictionary_t* dict, iterate_f f, void* extra){
    if(!f || !extra) return; 
    size_t nodes_iterated = 0;
    for(int i = 0; i < dict->capacity; i++){
        if(dict->nodes[i].key != NULL){
            f(dict->nodes[i].key, dict->nodes[i].value, extra);
            nodes_iterated++;
        }
        if(nodes_iterated == dict->size) break;
    }
};
