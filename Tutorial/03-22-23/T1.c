#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node_t;

typedef struct list list_t;

struct node {
  int value;
  node_t *next;
};

struct list {
  node_t *head;
  size_t size;
};

list_t *create_list() {
  list_t *list = (list_t *)malloc(sizeof(list_t));
  list->head = NULL;
  list->size = 0;
  return list;
}

node_t *append_to_list(list_t *list, int value) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;
  if (list->size == 0) {
    list->head = new_node;
  } else {
    node_t *curr = list->head;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = new_node;
  }
  list->size += 1;
  return new_node;
}

int at_position(list_t *list, size_t idx, int *err) {
  if (list->size == 0) {
    *err = 1;
    return 0;
  }
  node_t *current = list->head;
  for (size_t i = 0; i < idx; i++, current = current->next)
    ;
  *err = 0;
  return current->value;
}

//Lo que teniamos que hacer 
void remove_node(list_t *list, node_t *node) {
    node_t * first = list ->head;
    node_t * ;
    while(first->next){
        
    }
    
    return;
}

//Es O(n)

void destroy_list(list_t *list) {
  node_t *next = list->head;
  while (next != NULL) {
    node_t *curr = next;
    next = curr->next;
    free(curr);
  }
  free(list);
}

node_t **add_nodes(list_t *list) {
  char *buffer;
  size_t buffersize = 256;
  size_t chars;

  int n_nodes = 0;
  node_t **nodes = NULL;
  buffer = (char *)malloc(buffersize * sizeof(char));
  chars = getline(&buffer, &buffersize, stdin);
  char *p = strtok(buffer, " ");
  while (p != NULL) {
    int d = atoi(p);

    n_nodes += 1;
    nodes = (node_t **)realloc(nodes, sizeof(node_t *) * n_nodes);
    // printf("Adding node with value %d\n", d);
    nodes[n_nodes - 1] = append_to_list(list, d);

    p = strtok(NULL, " ");
  }
  free(buffer);
  return nodes;
}

void remove_nodes(list_t *list, node_t **nodes) {
  char *buffer;
  size_t buffersize = 256;
  size_t chars;

  buffer = (char *)malloc(buffersize * sizeof(char));
  chars = getline(&buffer, &buffersize, stdin);
  char *p = strtok(buffer, " ");
  while (p != NULL) {
    size_t d;
    if (1 == sscanf(p, "%zu", &d)) {
      // printf("Removing node at index %lu\n", d);
      remove_node(list, nodes[d]);
    }
    p = strtok(NULL, " ");
  }
  free(buffer);
}

void assert_nodes(list_t *list) {
  char *buffer;
  size_t buffersize = 256;
  size_t chars;

  buffer = (char *)malloc(buffersize * sizeof(char));
  chars = getline(&buffer, &buffersize, stdin);

  if (chars == 1) {
    // printf("buffer is %s\n", buffer);
    // printf("list size is %lu\n", list->size);
    assert(list->size == 0);
    free(buffer);
    return;
  }

  char *p = strtok(buffer, " ");
  size_t idx = 0;
  int err;
  while (p != NULL) {
    int d = atoi(p);
    int val = at_position(list, idx, &err);
    // printf("Comparing element at position %lu (%d) with %d\n", idx, val, d);
    assert(err == 0 && val == d);

    p = strtok(NULL, " ");
    idx += 1;
  }

  free(buffer);
}

void test_stdin() {
  list_t *list = create_list();
  node_t **nodes = add_nodes(list);
  // printf("list size: %zu\n", list->size);
  remove_nodes(list, nodes);
  assert_nodes(list);
  free(nodes);
  destroy_list(list);
}

int main() {
  test_stdin();
  printf("Ok");

  list_t *list = create_list();
  node_t *node0 = append_to_list(list, 0);
  node_t *node1 = append_to_list(list, 1);
  node_t *node2 = append_to_list(list, 2);
  node_t *node3 = append_to_list(list, 3);
  node_t *node4 = append_to_list(list, 4);
  int err;
  for (size_t i = 0; i < 5; ++i) {
    int at_idx = at_position(list, i, &err);
    assert(err == 0 && at_idx == i);
  }

  remove_node(list, node2);
  int values[] = {0, 1, 3, 4};
  for (size_t i = 0; i < 4; ++i) {
    int at_idx = at_position(list, i, &err);
    assert(err == 0 && at_idx == values[i]);
  }

  remove_node(list, node1);
  int values2[] = {0, 3, 4};
  for (size_t i = 0; i < 3; ++i) {
    int at_idx = at_position(list, i, &err);
    assert(err == 0 && at_idx == values2[i]);
  }

  remove_node(list, node0);
  int values3[] = {3, 4};
  for (size_t i = 0; i < 2; ++i) {
    int at_idx = at_position(list, i, &err);
    assert(err == 0 && at_idx == values3[i]);
  }

  destroy_list(list);
  return 0;
}
