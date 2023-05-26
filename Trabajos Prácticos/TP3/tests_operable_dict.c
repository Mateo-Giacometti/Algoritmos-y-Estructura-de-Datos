#include "test_malloc.h"
#include "testing.h"
#include "operable_dict.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool test_normal_update() {
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  bool err = false;
  dictionary_t *dict1 = dictionary_create(NULL);
  dictionary_t *dict2 = dictionary_create(NULL);
  char *key0 = "key_0";
  char *key1 = "key_1";
  char *key2 = "key_2";
  char* key3 = "key_3";
  char* key4 = "key_4";
  char* key5 = "key_5";
  char* key_rep1 = "Key_rep";
  char* key_rep2 = "Key_rep";
  char *value0 = "value_0";
  char *value1 = "value_1";
  char *value2 = "value_2";
  char* value3 = "value_3";
  char* value4 = "value_4";
  char* value5 = "value_5";
  char* value_rep1 = "value_rep1";
  char* value_rep2 = "value_rep2";
  dictionary_put(dict1, key0, value0);
  dictionary_put(dict1, key1, value1);
  dictionary_put(dict1, key2, value2);
  dictionary_put(dict1, key_rep1, value_rep1);
  dictionary_put(dict2, key3, value3);
  dictionary_put(dict2, key4, value4);
  dictionary_put(dict2, key5, value5);
  dictionary_put(dict2, key_rep2, value_rep2);
  tests_result &= test_assert("El update fue realizado exitosamente", dictionary_update(dict1, dict2));
  tests_result &= test_assert("El size del diccionario actualizado es correcto", dictionary_size(dict1) == 7);
  tests_result &= test_assert("La clave key0 se encuentra en el diccionario", dictionary_contains(dict1, key0));
  tests_result &= test_assert("El valor de la key0 es correcto", strcmp(dictionary_get(dict1, key0, &err), value0) == 0);
  tests_result &= test_assert("La clave key1 se encuentra en el diccionario", dictionary_contains(dict1, key1));
  tests_result &= test_assert("El valor de la key1 es correcto", strcmp(dictionary_get(dict1, key1, &err), value1) == 0);
  tests_result &= test_assert("La clave key2 se encuentra en el diccionario", dictionary_contains(dict1, key2));
  tests_result &= test_assert("El valor de la key2 es correcto", strcmp(dictionary_get(dict1, key2, &err), value2) == 0);
  tests_result &= test_assert("La clave key3 se encuentra en el diccionario", dictionary_contains(dict1, key3));
  tests_result &= test_assert("El valor de la key3 es correcto", strcmp(dictionary_get(dict1, key3, &err), value3) == 0);
  tests_result &= test_assert("La clave key4 se encuentra en el diccionario", dictionary_contains(dict1, key4));
  tests_result &= test_assert("El valor de la key4 es correcto", strcmp(dictionary_get(dict1, key4, &err), value4) == 0);
  tests_result &= test_assert("La clave key5 se encuentra en el diccionario", dictionary_contains(dict1, key5));
  tests_result &= test_assert("El valor de la key5 es correcto", strcmp(dictionary_get(dict1, key5, &err), value5) == 0);
  tests_result &= test_assert("La clave key_rep (calve repetida en ambos diccionarios) se encuentra en el diccionario", dictionary_contains(dict1, key_rep2));
  tests_result &= test_assert("El valor de la key_rep es correcto (el valor que presenta en el dictionary2)", strcmp(dictionary_get(dict1, key_rep2, &err), value_rep2) == 0);
  dictionary_destroy(dict1);
  dictionary_destroy(dict2);
  return tests_result;
}


bool test_fail_update(){
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  bool err = false;
  dictionary_t *dict1 = dictionary_create(NULL);
  dictionary_t *dict2 = dictionary_create(NULL);
  char *key0 = "key_0";
  char *key1 = "key_1";
  char *key2 = "key_2";
  char* key3 = "key_3";
  char *value0 = "value_0";
  char *value1 = "value_1";
  char *value2 = "value_2";
  char* value3 = "value_3";
  dictionary_put(dict1, key0, value0);
  dictionary_put(dict1, key1, value1);
  dictionary_put(dict2, key2, value2);
  dictionary_put(dict2, key3, value3);
  set_malloc_status(false);
  tests_result &= test_assert("El update no fue realizado exitosamente", !dictionary_update(dict1, dict2));
  tests_result &= test_assert("El size del dictionary1 actualizado se mantine", dictionary_size(dict1) == 2);
  tests_result &= test_assert("La clave key0 se encuentra en el dictionary1", dictionary_contains(dict1, key0));
  tests_result &= test_assert("El valor de la key0 es correcto", strcmp(dictionary_get(dict1, key0, &err), value0) == 0);
  tests_result &= test_assert("La clave key1 se encuentra en el dictionary1", dictionary_contains(dict1, key1));
  tests_result &= test_assert("El valor de la key1 es correcto", strcmp(dictionary_get(dict1, key1, &err), value1) == 0);
  tests_result &= test_assert("La clave key2 no se encuentra en el dictionary1 (pertenece a dictionary2)", !dictionary_contains(dict1, key2));
  tests_result &= test_assert("La clave key3 no se encuentra en el dictionary1 (pertenece a dictionary2)", !dictionary_contains(dict1, key3));
  set_malloc_status(true);
  dictionary_destroy(dict1);
  dictionary_destroy(dict2);
  return tests_result;
}


bool test_normal_and(){
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  bool err = false;
  dictionary_t *dict1 = dictionary_create(NULL);
  dictionary_t *dict2 = dictionary_create(NULL);
  char *key0 = "key_0";
  char *key1 = "key_1";
  char *key2 = "key_2";
  char* key3 = "key_3";
  char* key_rep1 = "Key_rep";
  char* key_rep2 = "Key_rep";
  char* key_rep3 = "Key_rep1";
  char* key_rep4 = "Key_rep1";
  char *value0 = "value_0";
  char *value1 = "value_1";
  char *value2 = "value_2";
  char* value3 = "value_3";
  char* value_rep1 = "value_rep1";
  char* value_rep2 = "value_rep2";
  char* value_rep3 = "value_rep3";
  char* value_rep4 = "value_rep4";
  dictionary_put(dict1, key0, value0);
  dictionary_put(dict1, key1, value1);
  dictionary_put(dict1, key_rep1, value_rep1);
  dictionary_put(dict1, key_rep3, value_rep3);
  dictionary_put(dict2, key2, value2);
  dictionary_put(dict2, key3, value3);
  dictionary_put(dict2, key_rep2, value_rep2);
  dictionary_put(dict2, key_rep4, value_rep4);
  dictionary_t *dict3 = dictionary_and(dict1, dict2);
  tests_result &= test_assert("Se devuelve un nuevo diccionario", dict3 != NULL);
  tests_result &= test_assert("El size del diccionario nuevo es correcta", dictionary_size(dict3) == 2);
  tests_result &= test_assert("La clave key0 no se encuentra en el diccionario nuevo", !dictionary_contains(dict3, key0));
  tests_result &= test_assert("La clave key1 no se encuentra en el diccionario nuevo", !dictionary_contains(dict3, key1));
  tests_result &= test_assert("La clave key2 no se encuentra en el diccionario nuevo", !dictionary_contains(dict3, key2));
  tests_result &= test_assert("La clave key3 no se encuentra en el diccionario nuevo", !dictionary_contains(dict3, key3));
  tests_result &= test_assert("La clave key_rep se encuentra en el diccionario nuevo", dictionary_contains(dict3, key_rep1));
  tests_result &= test_assert("El valor de la key_rep es correcto (el que se encuentra en el dictionary1)", strcmp(dictionary_get(dict3, key_rep1, &err), value_rep1) == 0);
  tests_result &= test_assert("La clave key_rep2 se encuentra en el diccionario nuevo", dictionary_contains(dict3, key_rep3));
  tests_result &= test_assert("El valor de la key_rep2 es correcto (el que se encuentra en el dictionary2)", strcmp(dictionary_get(dict3, key_rep3, &err), value_rep3) == 0);
  dictionary_destroy(dict1);
  dictionary_destroy(dict2);
  dictionary_destroy(dict3);
  return tests_result;
}


bool test_fail_and(){
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  dictionary_t *dict1 = dictionary_create(NULL);
  dictionary_t *dict2 = dictionary_create(NULL);
  char *key0 = "key_0";
  char *key1 = "key_1";
  char *key2 = "key_2";
  char* key3 = "key_3";
  char *value0 = "value_0";
  char *value1 = "value_1";
  char *value2 = "value_2";
  char* value3 = "value_3";
  dictionary_put(dict1, key0, value0);
  dictionary_put(dict1, key1, value1);
  dictionary_put(dict2, key2, value2);
  dictionary_put(dict2, key3, value3);
  set_malloc_status(false);
  dictionary_t *dict3 = dictionary_and(dict1, dict2);
  tests_result &= test_assert("No se pudo crear el nuevo diccionario", dict3 == NULL);
  set_malloc_status(true);
  dictionary_destroy(dict1);
  dictionary_destroy(dict2);
  return tests_result;
}


bool test_normal_or(){
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  bool err = false;
  dictionary_t *dict1 = dictionary_create(NULL);
  dictionary_t *dict2 = dictionary_create(NULL);
  char *key0 = "key_0";
  char *key1 = "key_1";
  char *key2 = "key_2";
  char* key3 = "key_3";
  char* key_rep1 = "Key_rep";
  char* key_rep2 = "Key_rep";
  char* key_rep3 = "Key_rep1";
  char* key_rep4 = "Key_rep1";
  char *value0 = "value_0";
  char *value1 = "value_1";
  char *value2 = "value_2";
  char* value3 = "value_3";
  char* value_rep1 = "value_rep1";
  char* value_rep2 = "value_rep2";
  char* value_rep3 = "value_rep3";
  char* value_rep4 = "value_rep4";
  dictionary_put(dict1, key0, value0);
  dictionary_put(dict1, key1, value1);
  dictionary_put(dict1, key_rep1, value_rep1);
  dictionary_put(dict1, key_rep3, value_rep3);
  dictionary_put(dict2, key2, value2);
  dictionary_put(dict2, key3, value3);
  dictionary_put(dict2, key_rep2, value_rep2);
  dictionary_put(dict2, key_rep4, value_rep4);
  dictionary_t *dict3 = dictionary_or(dict1, dict2);
  tests_result &= test_assert("Se devuelve un nuevo diccionario", dict3 != NULL);
  tests_result &= test_assert("El size del diccionario nuevo es correcta", dictionary_size(dict3) == 6);	
  tests_result &= test_assert("La clave key0 se encuentra en el diccionario nuevo", dictionary_contains(dict3, key0));
  tests_result &= test_assert("El valor de la key0 es correcto", strcmp(dictionary_get(dict3, key0, &err), value0) == 0);
  tests_result &= test_assert("La clave key1 se encuentra en el diccionario nuevo", dictionary_contains(dict3, key1));
  tests_result &= test_assert("El valor de la key1 es correcto", strcmp(dictionary_get(dict3, key1, &err), value1) == 0);
  tests_result &= test_assert("La clave key2 se encuentra en el diccionario nuevo", dictionary_contains(dict3, key2));
  tests_result &= test_assert("El valor de la key2 es correcto", strcmp(dictionary_get(dict3, key2, &err), value2) == 0);
  tests_result &= test_assert("La clave key3 se encuentra en el diccionario nuevo", dictionary_contains(dict3, key3));
  tests_result &= test_assert("El valor de la key3 es correcto", strcmp(dictionary_get(dict3, key3, &err), value3) == 0);
  tests_result &= test_assert("La clave key_rep se encuentra en el diccionario nuevo", dictionary_contains(dict3, key_rep1));
  tests_result &= test_assert("El valor de la key_rep es correcto (el que se encuentra en el dictionary1)", strcmp(dictionary_get(dict3, key_rep1, &err), value_rep1) == 0);
  tests_result &= test_assert("La clave key_rep2 se encuentra en el diccionario nuevo", dictionary_contains(dict3, key_rep3));
  tests_result &= test_assert("El valor de la key_rep2 es correcto (el que se encuentra en el dictionary2)", strcmp(dictionary_get(dict3, key_rep3, &err), value_rep3) == 0);
  dictionary_destroy(dict1);
  dictionary_destroy(dict2);
  dictionary_destroy(dict3);
  return tests_result;
}

bool test_fail_or(){
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  dictionary_t *dict1 = dictionary_create(NULL);
  dictionary_t *dict2 = dictionary_create(NULL);
  char *key0 = "key_0";
  char *key1 = "key_1";
  char *key2 = "key_2";
  char* key3 = "key_3";
  char *value0 = "value_0";
  char *value1 = "value_1";
  char *value2 = "value_2";
  char* value3 = "value_3";
  dictionary_put(dict1, key0, value0);
  dictionary_put(dict1, key1, value1);
  dictionary_put(dict2, key2, value2);
  dictionary_put(dict2, key3, value3);
  set_malloc_status(false);
  dictionary_t *dict3 = dictionary_or(dict1, dict2);
  tests_result &= test_assert("No se pudo crear el nuevo diccionario", dict3 == NULL);
  set_malloc_status(true);
  dictionary_destroy(dict1);
  dictionary_destroy(dict2);
  return tests_result;
}

bool test_equals(){
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  dictionary_t *dict1 = dictionary_create(free);
  dictionary_t *dict2 = dictionary_create(free);
  dictionary_t *dict3 = dictionary_create(free);
  char *key0 = "key_0";
  char *key1 = "key_1";
  char *key2 = "key_2";
  char* key3 = "key_3";
  int *value0 = malloc(sizeof(int));
  *value0 = 0;
  int *value1 = malloc(sizeof(int));
  *value1 = 1;
  int *value2 = malloc(sizeof(int));
  *value2 = 2;
  int *value3 = malloc(sizeof(int));
  *value3 = 3;
  int *not_value = malloc(sizeof(int));
  *not_value = 3;
  dictionary_put(dict1, key0, value0);
  dictionary_put(dict1, key1, value1);
  dictionary_put(dict1, key2, value2);
  dictionary_put(dict2, key0, value0);
  dictionary_put(dict2, key1, value1);
  tests_result &= test_assert("Diccionarios de misma capacidad y diferente size no son iguales", !dictionary_equals(dict1, dict2));
  dictionary_put(dict2, key3, value3);
  tests_result &= test_assert("Diccionarios de igual size pero de distintos elementos no son iguales", !dictionary_equals(dict1, dict2));
  dictionary_put(dict1, key3, value3);
  dictionary_put(dict2, key2, value2);
  tests_result &= test_assert("Diccionarios de igual size y mismos elementos son iguales", dictionary_equals(dict1, dict2));
  dictionary_put(dict2, key3, not_value);
  tests_result &= test_assert("Diccionarios de igual size y mismos elementos pero algun puntero a value es distinto hace que no sean iguales", !dictionary_equals(dict1, dict2));
  dictionary_put(dict2, key3, value3);
  dict3->capacity = dict1->capacity/4;
  dictionary_put(dict3, key0, value0);
  dictionary_put(dict3, key1, value1);
  dictionary_put(dict3, key2, value2);
  dictionary_put(dict3, key3, value3);
  tests_result &= test_assert("Diccionarios con los mismos elementos pero diferente orden en memoria son iguales", dictionary_equals(dict1, dict3));
  for(int i = 0; i < dict1->capacity; i++){
    if(dict1->nodes[i].key != NULL){
      free(dict1->nodes[i].key);
    }
    if(dict2->nodes[i].key != NULL){
      free(dict2->nodes[i].key);
    }
    if(dict3->nodes[i].key != NULL){
      free(dict3->nodes[i].key);
    }
  }
  free(value0);
  free(value1);
  free(value2);
  free(dict1->nodes);
  free(dict2->nodes);
  free(dict3->nodes);
  free(dict1);
  free(dict2);
  free(dict3);
  return tests_result;
}

int main(void) {
  srand(117);
  int return_code = 0;
  return_code += !test_normal_update();
  return_code += !test_fail_update();
  return_code += !test_normal_and();
  return_code += !test_fail_and();
  return_code += !test_normal_or();
  return_code += !test_fail_or();
  return_code += !test_equals();
  exit(return_code);
}
