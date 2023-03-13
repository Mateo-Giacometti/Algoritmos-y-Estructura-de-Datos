#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
Escribir la función que dado n P N devuelve si es primo. Recuerden que un
número es primo si los únicos divisores que tiene son 1 y el mismo.
*/

bool is_prime(int x){
    if (x <= 1){
        return false;
    }
    for(int i = 2; i < x; i++){
        if (x % i == 0){
            return false;
        }
    }
}

int main(void){
    int n;
    printf("Ingrese un número: ");
    scanf("%d", &n);
    if (is_prime(n)){
        printf("El número %d es primo.\n", n);
    } else {
        printf("El número %d no es primo.\n", n);
    }
    return EXIT_SUCCESS;
}