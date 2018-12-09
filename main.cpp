#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include "instance.h"

bool noAsignadas(int& fila, int& columna, int grilla[9][9], std::list <unassigned> casillas_vacias){
    std:: list <unassigned>:: iterator iterador = casillas_vacias.begin();
    while(iterador != casillas_vacias.end()){
        int row = iterador -> fila;
        int col = iterador -> columna;
        if (grilla[row][col] == 0){
            fila = row;
            columna = col;
            return true;
        }
        ++iterador;
    }
    return false;
}

bool CheckRows(int grilla[9][9], int fila, int num){
    //int see_num [] = {0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 9; ++i){
        if(grilla[fila][i] == num){
            return false;
        } 
    }
    return true;
}
bool CheckColumns(int grilla[9][9], int columna, int num){
    //int see_num [] = {0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 9; ++i){
        
        if (grilla[i][columna]==num) {
            return false;
        }
    }
    return true;
}
bool  CheckSubGrids(int grilla[9][9], int fila, int columna, int num){
    int fila_inicio = fila - fila%3;
    int columna_inicio = columna - columna%3;
    //int see_num [] = {0,0,0,0,0,0,0,0,0};

    for(int i = fila_inicio ; i < fila_inicio + 3; ++i){
        for(int j = columna_inicio; j < columna_inicio + 3; ++j){
            
            if (grilla[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool CheckSum(int grilla[9][9], int sectores[9][9], std::list <segmento> segmentos, int fila, int columna, int num){
    int suma = 0;
    int casVacias = 0;
    int seg = sectores[fila][columna];
    
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if (sectores[i][j] == seg){
                if(grilla[i][j] == 0)
                    ++casVacias; 
                if(i == fila && columna == j)
                    suma += num;
                suma += grilla[i][j]; 
            }
        }
    }

    std:: list <segmento>::iterator iterador = segmentos.begin();
    while (iterador -> identificador != seg){
        iterador++;
    }

    int suma_segmento = iterador -> suma_segmento;

    if(suma == suma_segmento && casVacias ==0)
        return true;

    if( suma <= suma_segmento  && casVacias > 0)
        return true;
    
    return false;

}

bool asignacionValida(int grilla[9][9], int sectores[9][9], std:: list<segmento> segmentos, std::list <unassigned> casillas_vacias, int fila, int columna, int num){
    bool checkFilas = CheckRows(grilla, fila, num);
    bool checkColumnas = CheckColumns(grilla, columna, num);
    bool checkSubGrilla = CheckSubGrids(grilla, fila, columna, num);
    bool checkSuma = CheckSum(grilla, sectores, segmentos, fila, columna, num);
    return checkFilas && checkColumnas && checkSubGrilla && checkSuma;
} 

bool ForwardChecking(int grilla[9][9], int sectores[9][9], std::list <segmento> segmentos, std::list <unassigned> casillas_vacias){
    int row, col;
    if (!noAsignadas(row, col, grilla, casillas_vacias)){
        return true;
    }
    for(int num = 9; num > 0; --num){
        if(asignacionValida(grilla, sectores, segmentos, casillas_vacias, row, col, num)){
           grilla[row][col] = num; 
            if(ForwardChecking(grilla, sectores,segmentos, casillas_vacias)){
                return true;
            }
            grilla[row][col] = 0;
        }      
    }
    return false;
}


int main(int argc, char const *argv[])
{   
    char archivo [1000] = "instancias-ejem/easy.txt";
    instance instancia(archivo);
    /*
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            std:: cout << instancia.sectores[i][j] << " ";
        }
        std:: cout << "\n";
    }
    */
    /*std:: cout<< "Matriz\n";

    for (int i = 0; i < 9 ; i++){
        for (int j = 0; j < 9; j++){
            std:: cout<< instancia.cuadricula[i][j] << " ";
        }
        std:: cout << "\n";
    }

    std:: cout << "\n";

    std:: list <segmento>:: iterator iterador = instancia.segmentos.begin();
    while(iterador != instancia.segmentos.end()){
        std:: cout<< iterador->identificador << ":"<< iterador -> suma_segmento <<"\n";
        iterador ++;
    }*/

    /*std:: list <unassigned>:: iterator iterador2 = instancia.casillas_vacias.begin();
    while(iterador2 != instancia.casillas_vacias.end()){
        std:: cout << "fila: " << iterador2 -> fila << "\n";
        std:: cout << "columna: " << iterador2 -> columna << "\n";
        iterador2 ++;

    } */

    /*
    if (CheckSum(instancia.cuadricula, instancia.sectores, 2, instancia.segmentos))
        std:: cout << "Cumple con la suma\n";
    else 
        std:: cout << "No cumple con la suma\n";

    */
    std:: cout << "tamaño de la lista: "<<instancia.casillas_vacias.size() <<"\n";
    ForwardChecking(instancia.cuadricula, instancia.sectores, instancia.segmentos, instancia.casillas_vacias);
    for (int i = 0; i < 9 ; i++){
        for (int j = 0; j < 9; j++){
            std:: cout<< instancia.cuadricula[i][j] << " ";
        }
        std:: cout << "\n";
    }
    return 0;
}