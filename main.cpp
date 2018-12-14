#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include "instance.h"
#include "forwardchecking.h"
#include <ctime>

int main(int argc, char const *argv[]){   
    unsigned t0, t1;
    t0 = clock();
    char archivo [1000] = "Instancias Finales/60blank.txt";
    instance instancia(archivo);

    std:: cout << "Casillas vacias: "<<instancia.casillas_vacias.size() <<"\n";
    ForwardCheckingAleatorio(instancia.cuadricula, instancia.sectores, instancia.segmentos, instancia.casillas_vacias);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    std:: cout << 0 << "\n";
    std:: cout << time << "\n";
    for (int i = 0; i < 9 ; i++){
        for (int j = 0; j < 9; j++){
            std:: cout<< instancia.cuadricula[i][j] << "C" <<instancia.sectores[i][j] <<" ";
            if(instancia.sectores[i][j] < 10){
                std:: cout << " ";
            }
        }
        std:: cout << "\n";
    }
    return 0;
}