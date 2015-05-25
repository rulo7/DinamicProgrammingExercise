#include <fstream>
#include "ebanisto.h"
#include <iostream>


using namespace std;

int main(int argc, char** argv) {

    ifstream fichero("troncos.txt");

    int l, n;
    int caso = 1;
    // el primer valor equivale a la longitud del tronco
    while (fichero >> l) {
        // 0 es el centinela, es decir, que si se encuentra enel fichero, se acaba
        if (l != 0) {
            std::cout << "Caso " << caso << ":" << std::endl;

            // el segundo valor equivale al numero de cortes
            fichero >> n;
            // el tamaño del array es el del numero de cortes mas los extremos
            int* cortes = new int[n + 2];

            // inicializamos los valores de los cortes en los extrmos
            cortes[0] = 0;
            cortes[n + 1] = l;

            // Almacenamos el resto de cortes
            for (int i = 0; i < n; i++) {
                fichero >> cortes[i + 1];
            }
            // llamamos a la funcion
            esfuerzoMinimoPosible(cortes, n + 2);
            // liberamos la memoria
            delete[] cortes;
            // pasamos al siguiente caso
            caso++;
        }
    }
    // cerramos el fichero de entrada
    fichero.close();
    return 0;
}


