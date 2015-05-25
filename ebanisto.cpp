#include<climits>
#include <iostream>
#include"ebanisto.h"
/*
 El problema consiste en que tenemos un tronco con varias marcas para realizar cortes.
 Las marcas 0 y 1 coinciden con los extremos del tronco.
 La solución consiste en encontrar un algoritmo de programación dinámica que nos devuelva el esfuerzo minimo posible de realizar los cortes por las marcas.
 Además, la solución deberá añadir el orden en el que cortamos las marcas, pues el esfuerzo de ebanisto varía según este factor:
 - El esfuerzo invertido en cortar una marca del tronco es de 2 veces la longitud del trozo de tronco que contiene la marca. 
 */

/*
 * Dadas las marcas de corte sobre el tronco, devuelve el valor del esfuerzo minimo posible 
 * realizado para hacer los cortes sobre esas marcas y el orden en el que deberían hacerse 
 * esos cortes para que el esfuerzo sea mínimo.
 */
void esfuerzoMinimoPosible(int marcas[], int n) {

    // instanciamos la matriz que almacena la k seleccionada para cada corte
    int** kas = new int* [n];
    // instanciamos la matriz de resultados
    int** esfuerzoMinimoPosible = new int* [n];

    // terminamos de instanciar las matrices
    for (int i = 0; i < n; i++) {
        esfuerzoMinimoPosible[i] = new int[n];
        kas[i] = new int[n];
    }

    // inicializamos los casos base    
    for (int i = 0; i < n; i++) {
        // En el caso de que no exista marca de corte en el segmento (i,i+1), no supone ningún esfuerzo
        esfuerzoMinimoPosible[i][i + 1] = 0;
    }

    // de forma iterativa por diagonales rellenamos la tabla, desde el origen hasta la llamada recursiva inicial:
    // Llam. rec inicial = esfuerzoMinimoPosible(0,n-1);
    int min, j;
    // recorre la diagonal
    for (int d = 2; d < n; d++) {
        // recorre los elementos de la diagonal
        for (int i = 0; i < n - d; i++) {
            j = i + d;
            min = INT_MAX;

            for (int k = i + 1; k < j; k++) {
                // selecciono el corte que genera un esfuerzo minimo
                if ((esfuerzoMinimoPosible[i][k] + esfuerzoMinimoPosible[k][j]) < min) {
                    min = esfuerzoMinimoPosible[i][k] + esfuerzoMinimoPosible[k][j];
                    kas[i][j] = k;
                }

            }

            // esfuerzo(i,j) = 2*(c[j] - c[i]) + min(i<k<j){esfuerzo(i,k) + esfuerzo(k,j)}
            esfuerzoMinimoPosible[i][j] = 2 * (marcas[j] - marcas[i]) + min;

        }
    }

    // recuperamos la solucion
    std::cout << "El coste minimo es: " << esfuerzoMinimoPosible[0][n - 1] << std::endl;
    std::cout << "Cortes: " << std::endl;
    recuperarSolucion(0, n - 1, kas, marcas, 0);

    // Liberamos la memoria de cada fila de las matrices
    for (int i = 0; i < n; i++) {
        delete[] esfuerzoMinimoPosible[i];
        delete[] kas[i];
    }

    // Liberamos la memoria de cada matriz
    delete[] esfuerzoMinimoPosible;
    delete[] kas;
}

void recuperarSolucion(int i, int j, int** kas, int* marcas, int cont) {

    if (i + 1 < j) {
        // generamos la indentacion
        for (int i = 0; i < cont; i++) {
            std::cout << "\t";
        }
        // mostramos el corte realizado
        std::cout << marcas[kas[i][j]] << std::endl;
        // mostramos los cortes del tronco resultante a la izquierda
        recuperarSolucion(i, kas[i][j], kas, marcas, cont + 1);
        // mostramos los cortes del tronco resultante a la derecha
        recuperarSolucion(kas[i][j], j, kas, marcas, cont + 1);
    }
}