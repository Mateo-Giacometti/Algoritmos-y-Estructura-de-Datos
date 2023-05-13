#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
Dado un vector de ints queremos dejar todos los ceros al principio del vector. Diseñe un
algoritmo lo más eficiente posible para resolver este problema y analice el Orden del mismo.
*/

void orden(int vec[], int len_vec){
    int index = 0;
    for(int i = 0; i < len_vec; i++){
        if(vec[i] == 0){
            int aux = vec[index];
            vec[index] = vec[i];
            vec[i] = aux;
            index++;
        }
    }
}

int main (void){
    int vec[10] = {5,6,0,2,78,92,0,0,53,2};
    orden(vec, 10);
    for(int i = 0; i < 10; i++){
        printf("%d ", vec[i]);
    }
    return 0;
}
