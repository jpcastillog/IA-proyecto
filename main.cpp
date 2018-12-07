#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include "instance.h"

bool CheckRows(int grilla[9][9], int fila){
    int see_num [] = {0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 9; ++i){
        see_num[grilla[fila][i] - 1] = 1;
    }

    for(int i = 0; i < 9; ++i){
        if(see_num[i] == 0){
            return false;
        }
    }

    return true;
}
bool CheckColumns(int grilla[9][9], int columna){
    int see_num [] = {0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 9; ++i){
        see_num[grilla[i][columna] - 1] = 1;
    }

    for(int i = 0; i < 9; ++i){
        if(see_num[i] == 0){
            return false;
        }
    }
    return true;
}
bool  CheckSubGrids(int grilla[9][9], int fila, int columna){
    int fila_inicio = fila - fila%3;
    int columna_inicio = columna - columna%3;
    int see_num [] = {0,0,0,0,0,0,0,0,0};

    for(int i = fila_inicio ; i < fila_inicio + 3; ++i){
        for(int j = columna_inicio; j < columna_inicio + 3; ++j){
            see_num[grilla[i][j] - 1] = 1;
        }
    }

    for(int i = 0; i < 9; ++i){
        if (see_num[i] == 0){
            return false;
        }
    }
    return true;

}

bool CheckSum(int grilla[9][9], int sectores[9][9],int seg, std::list <segmento> segmentos){
    int suma = 0;
    
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if (sectores[i][j] == seg){
                suma += grilla[i][j]; 
            }
        }
    }

    std:: list <segmento>::iterator iterador = segmentos.begin();
    while (iterador -> identificador != seg){
        iterador++;
    }
    if(suma == iterador -> suma_segmento)
        return true;
    return false;

}

bool ForwardChecking(int grilla[9][9], int sectores[9][9], std::list <segmento> segmentos){
    return true;


}


int main(int argc, char const *argv[])
{   
    int array[9][9][9] = {};
    std::cout << "arreglo vacio:" << array[0][0][0]<< "\n";
    char archivo [1000] = "instancias-ejem/moderate_filled.txt";
    instance instancia(archivo);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            std:: cout << instancia.sectores[i][j] << " ";
        }
        std:: cout << "\n";
    }

    std:: cout<< "Matriz\n";

    for (int i = 0; i < 9 ; i++){
        for (int j = 0; j < 9; j++){
            std:: cout<< instancia.cuadricula[i][j] << " ";
            //std:: cout<< "\n";
        }
        std:: cout << "\n";
    }

    std:: cout << "\n";

    std:: list <segmento>:: iterator iterador = instancia.segmentos.begin();
    while(iterador != instancia.segmentos.end()){
        std:: cout<< iterador->identificador << ":"<< iterador -> suma_segmento <<"\n";
        iterador ++;
    }

    if (CheckSum(instancia.cuadricula, instancia.sectores, 2, instancia.segmentos))
        std:: cout << "Cumple con la suma\n";
    else 
        std:: cout << "No cumple con la suma\n";
    return 0;
}


