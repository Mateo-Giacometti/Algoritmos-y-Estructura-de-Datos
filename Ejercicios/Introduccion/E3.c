#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
¿Cuál es el valor de a y b luego de ejecutar el programa?
*/

void myFunc(int* a, int b){
    (*a)++;
    b++;
}

int main(void){
    int a = 10;
    int b = 10;
    myFunc(&a, b);
    printf("%d, %d \n",a,b);
    return EXIT_SUCCESS;
}

/*
RTA: a = 11 y b = 10.
*/
