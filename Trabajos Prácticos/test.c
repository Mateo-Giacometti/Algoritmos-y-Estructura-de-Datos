#include <stdio.h>
#include <stdbool.h>

void swap(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
    return;
}

int main(){
    int x = 1;
    int y = 2;
    swap(&x, &y);
    printf("%d %d", x, y);
    return 0;
}