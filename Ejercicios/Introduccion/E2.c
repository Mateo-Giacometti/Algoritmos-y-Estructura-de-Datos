#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
Escribir la función que dado n P N devuelve la suma de todos los números
impares menores que n.
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

int prime_sum(int n){
    int sum = 0;
    for(int i = 1; i <= n; i++){
        if(is_prime(i)){
            sum += i;
        }
    }
    return sum;
}

int main(void){
    int n;
    printf("Ingrese un número: ");
    scanf("%d", &n);
    printf("La suma de los números primos menores que %d es %d.\n", n, prime_sum(n));
    return EXIT_SUCCESS;
}