#include "test_malloc.h"
#include "testing.h"
#include "internal_iterator.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Ejemplo de distintas funciones de iteracion

/*
Itera cada par clave-valor del diccionario y le suma 1 al valor. Cada nuevo resultado se guarda en un array de int.
*/
bool add_value(const char *key, void *value, void *extra){
  int *array = (int *)extra;
  int *val = (int *)value;
  *val = *val + 1;
  int i = 0;
  while (array[i] != 0) {
    i++;
  }
  array[i] = *val;
  return true;
};

bool test_NULL_iterate_function() {
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  dictionary_t *dict = dictionary_create(free);
  char *key = "key_0";
  int *value = malloc(sizeof(int));
  *value = 0;
  dictionary_put(dict, key, value);
  iterate(dict, NULL, NULL);
  tests_result &= test_assert("La funcion del iterador NULL no afecta al diccionario", dictionary_contains(dict, key));
  dictionary_destroy(dict);
  return tests_result;
};

bool test_function(){
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  dictionary_t *dict = dictionary_create(free);
  char *key = "key_1";
  int *value = malloc(sizeof(int));
  *value = 1;
  dictionary_put(dict, key, value);
  char *key2 = "key_2";
  int *value2 = malloc(sizeof(int));
  *value2 = 2;
  dictionary_put(dict, key2, value2);
  char *key3 = "key_3";
  int *value3 = malloc(sizeof(int));
  *value3 = 3;
  dictionary_put(dict, key3, value3);
  int *extra = calloc(3, sizeof(int));
  iterate(dict, add_value, extra);
  tests_result &= test_assert("El nuevo valor 1 es correcto", *value == 2);
  tests_result &= test_assert("El nuevo valor 2 es correcto", *value2 == 3);
  tests_result &= test_assert("El nuevo valor 3 es correcto", *value3 == 4);
  tests_result &= test_assert("El nuevo valor 1 fue almacenado correctamente", extra[0] == 2);
  tests_result &= test_assert("El nuevo valor 2 fue almacenado correctamente", extra[2] == 3);
  tests_result &= test_assert("El nuevo valor 3 fue almacenado correctamente", extra[1] == 4);
  free(extra);
  dictionary_destroy(dict);
  return tests_result;
};


int main(void) {
  srand(117);
  int return_code = 0;
  return_code += !test_NULL_iterate_function();
  return_code += !test_function();
  exit(return_code);
};
