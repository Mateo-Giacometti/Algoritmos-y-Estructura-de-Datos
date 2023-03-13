#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
¿Que valor se imprime por consola luego de cada llamado a printf?
*/

void main(){
    int x = 10;
    int* px = &x;

    printf("%d \n", px);
    printf("%d \n", (*px));

     (*px)++;

     printf("%d \n", px);
     printf("%d \n", (*px));
}

/*
Se imprime: I- Dirección de memoria de x
            II- Valor de x
            III- Nueva dirrección de memoria de X+1
            IV- Valor de X+1
*/
    