#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


void biseccion (long double f(),long double a, long double b, long double precicion){
    long double mitad = a + (b-a)*0.5;
    int cant_ite = 1;
    long double resultado = b - mitad;
    printf("La mitad es: %.22LF\n",mitad);
    while (true){
        if (f(mitad) > 0){
            b = mitad;
        } else if (f(mitad) < 0){
            a = mitad;
        }
        mitad = a + (b-a)*0.5;
        cant_ite += 1;
        resultado = b - mitad;
        printf("Los intervalos son: [%.22LF,%.22LF] || La mitad es: %.22LF\n",a,b,mitad);
        if (fabs(resultado) < precicion){
            break;
        }
    }
    printf("\n");
    printf("La función da: %.22LF\n",f(mitad));
    printf("La cantidad de itereaciones es: %d\n",cant_ite);
    printf("La última mitad es: %.22Lf\n",mitad);
    printf("Los intervalos son: [%.22Lf,%.22Lf]\n",a,b);
    printf("El resultado de |b - mitad| es: %.22f\n",fabs(resultado));
    printf("Termino\n\n");
}

long double funcion_ej_1(long double x){
        return 3*x - exp(x);
    }

int main(void){
    long double a = 1;
    long double b = 2;
    long double precicion = 0.00001;
    biseccion(funcion_ej_1,1.0,2.0,0.00001);
    return EXIT_SUCCESS;
}