#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    int key;
    void *value;
    struct Node *right;
    struct Node *left;
}node_t;

typedef struct Arbol{
    int size;
    struct Node *root;
}abb_t;


void in_order(node_t *raiz){
    if (raiz == NULL){
        return;
    }
    in_order(raiz->left);
    printf("%d", raiz->key);
    in_order(raiz->right);
}

void pre_order(node_t *raiz){
    if (raiz == NULL){
        return;
    }
    printf("%d", raiz->key);
    pre_order(raiz->left);
    pre_order(raiz->right);
}

// void print_hojas(abb_t * abb){

//     if (abb -> root -> left == NULL && abb -> root -> right == NULL){
//         printf("%d", abb->root);;
//     }
//     print_hojas(raiz->left);
//     print_hojas(raiz->right);
// }

// int altura(node_t* root){
//     if (root == NULL){
//         return -1; // si cuento la raiz como altura 0, pongo -1 SI NO si cuento la altura desde el 1 pongo 0
//     } else {
//         int left_h = altura(root -> left);
//         int right_h = altura(root -> right);
//         return 1 + max(left_h, right_h); // (left_h > right_h ? left_h : right_h); Se devuelve el máximo entre la altura del subárbol izquierdo y derecho, sumado a 1 para tener en cuenta el nodo actual
//     }
// }

bool is_hoja(node_t* node){
    if (node -> right == NULL && node -> left == NULL){
        return true;
    }
    return false;
}

int sumTree(node_t *root){ //Devuelve la suma de todos los valores del arbol

    if (root == NULL){
        return 0;
    }
    int sum_left = sumTree(root->left);
    int sum_right = sumTree(root->right);
    return (root -> key) + sum_right + sum_left;

}

bool is_sumTree(node_t *root){

    if ((root == NULL) || is_hoja(root)){
        return true;
    }
    int sum_left = sumTree(root -> left);
    int sum_right = sumTree(root -> right);
    if (root -> key != sum_left + sum_right){
        return false;
    }
    return (is_sumTree(root->left) && is_sumTree(root->right));

}

// //ARBOL BINARIO DE BUSQUEDA

// bool is_ordenado(int*arr){
//     for (int i=0; i< sizeof(arr)/sizeof(arr[0]) -1 ; i++){
//         if (arr[i]> arr[i+1]){
//             return false;
//         }
//     }
//     return true;
// }

// // bool is_abb(node_t *root){
//     int* arr = in_order(root);
//     return is_ordenado(arr);
// }


bool insert(abb_t *arb, node_t * root, node_t *parent, int k){
    if (root == NULL && parent == NULL){ 
        root = (node_t *) malloc (sizeof(node_t));
        root -> key = k;
        root -> left = NULL;
        root -> right = NULL;
        arb -> root = root;
        return true;
    }
    if (root == NULL){
        root = (node_t *) malloc (sizeof(node_t));
        root -> key = k;
        root -> left = NULL;
        root -> right = NULL;
        if (k < parent -> key){
            parent -> left = root;
        } else {
            parent -> right = root;
        }
        return true;
    }
    if (k < root -> key){
        return insert(arb, root -> left, root, k);
    }
    if (k > root -> key){
        return insert(arb, root -> right, root, k);
    }
    return false;
}

int main(){

    // abb_t *arbol = (abb_t *) malloc (sizeof(abb_t));
    // node_t* n1 =(node_t*) malloc (sizeof(node_t));
    // node_t* n2 =(node_t*) malloc (sizeof(node_t));
    // node_t* n3 =(node_t*) malloc (sizeof(node_t));
    // node_t* n4 =(node_t*) malloc (sizeof(node_t));
    // node_t* n5 =(node_t*) malloc (sizeof(node_t));
    // n1 -> key = 10;
    // n2 -> key = 3;
    // n3 -> key = 11;
    // n1 -> left = n2;
    // n1 -> right = n3;
    // n3 -> left = NULL;
    // n3 -> right = NULL;
    // n5 -> left = NULL;
    // n5 -> right = NULL;
    // n4 -> left = NULL;
    // n4 -> right = NULL;
    // n4 -> key = 2;
    // n5 -> key = 4;
    // n2 -> left = n4;
    // n2 -> right = n5;

    // arbol -> root = n1;
    // insert(arbol -> root, NULL, 5);
    // pre_order(arbol -> root);

    abb_t *arbol = (abb_t *) malloc (sizeof(abb_t));
    arbol-> root = NULL;
    arbol -> size = 0; 
    insert(arbol, arbol -> root, NULL, 26);
    pre_order(arbol -> root);


    //printf("%d", sumTree(arbol -> root));
    // if (is_sumTree(arbol -> root) == true){
    //     printf("%d", 1);
    // }
    

    return 0;
}


