#include <iostream>
#include <list>
#include "instance.h"
#include "forwardchecking.h"
#include <cstdlib>

/**
 * bool noAsignadas
 
******
Resumen Función:
*	La función encuentra la primera casilla vacia de arriba a abajo y de derecha a izquierda de la grilla.
******
Input:
* 	int& fila: referencia de la fila a asignar
*   int& columna: referencia de la columna a asignar
*   int grilla[9][9]: grilla del killer sudoku 
*   list <unassigned> casillas_vacias: lista con las casillas vacias de la grilla
******
Returns:
*	bool, retorna true si hay casillas vacias y false cuando ya no hay casillas por asignarl en la grilla	
**/

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
/**
 * bool CheckRows
 
******
Resumen Función:
*	La función revisa que en la fila no se encuentre el numero num
******
Input:
*   int grilla[9][9]: grilla del killer sudoku 
* 	int fila: fila a checkear
*   int num: numero a buscar en la fila
******
Returns:
*	bool, retorna false si el numero se encuentra en la fila y true si no esta	
**/
bool CheckRows(int grilla[9][9], int fila, int num){
    for(int i = 0; i < 9; ++i){
        if(grilla[fila][i] == num){
            return false;
        } 
    }
    return true;
}
/**
 * bool CheckColumns
 
******
Resumen Función:
*	La función revisa que en la columna no se encuentre el numero num
******
Input:
*   int grilla[9][9]: grilla del killer sudoku 
* 	int columna: columna a checkear
*   int num: numero a buscar en la columna
******
Returns:
*	bool, retorna false si el numero se encuentra en la columna y true si no esta	
**/
bool CheckColumns(int grilla[9][9], int columna, int num){
    for(int i = 0; i < 9; ++i){
        
        if (grilla[i][columna]==num) {
            return false;
        }
    }
    return true;
}
/**
 * bool CheckSubGrids
 
******
Resumen Función:
*	La función revisa que en la Sub Grilla no se encuentre el numero num
******
Input:
*   int grilla[9][9]: grilla del killer sudoku 
* 	int fila: fila en donde se podria posicionar num
*   int columna: columna en donde se podria posicionar num
*   int num: numero a buscar en la sub grilla
******
Returns:
*	bool, retorna false si el numero se encuentra en la sub grilla y true si no esta	
**/
bool  CheckSubGrids(int grilla[9][9], int fila, int columna, int num){
    int fila_inicio = fila - fila%3;
    int columna_inicio = columna - columna%3;
    for(int i = fila_inicio ; i < fila_inicio + 3; ++i){
        for(int j = columna_inicio; j < columna_inicio + 3; ++j){
            
            if (grilla[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}
/**
 * bool CheckSum
 
******
Resumen Función:
*	La función revisa que la suma de los segmentos se cumpla en la grilla si se insertara num en la pos fila, columna
******
Input:
*   int grilla[9][9]: grilla del killer sudoku 
*   int sectores [9][9]: grilla con los sectores 
*   list <segmento> segmentos
* 	int fila: posible fila en que se posicionaria num
*   int columna: posible columna en que se posicionaria num 
*   int num: numero que se posicionaria en fila, columna para checkear la suma de los sectores
******
Returns:
*	bool, retorna true si se posicionara el numero en fila, columna y cumple la restriccion de la suma de los sectores
    false en otro caso 
**/
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
/**
 * bool asignacionValida
 
******
Resumen Función:
*	La funcion ve si la grilla cumple con las restricciones 
******
Input:
*   int grilla[9][9]: grilla del killer sudoku 
*   int sectores [9][9]: grilla con los sectores 
*   list <segmento> segmentos
* 	int fila: posible fila en que se posicionaria num
*   int columna: posible columna en que se posicionaria num 
*   int num: numero que se posicionaria en fila, columna
******
Returns:
*	bool, retorna true si la  grilla cumple con las restricciones del killer sudoku y false si no las cumple
**/
bool asignacionValida(int grilla[9][9], int sectores[9][9], std:: list<segmento> segmentos, std::list <unassigned> casillas_vacias, int fila, int columna, int num){
    bool checkFilas = CheckRows(grilla, fila, num);
    bool checkColumnas = CheckColumns(grilla, columna, num);
    bool checkSubGrilla = CheckSubGrids(grilla, fila, columna, num);
    bool checkSuma = CheckSum(grilla, sectores, segmentos, fila, columna, num);
    return checkFilas && checkColumnas && checkSubGrilla && checkSuma;
} 
/**
 * bool numerosAsignados
 
******
Resumen Función:
*	La función revisa si quedan valores por instanciar del dominio
******
Input:
*   int numeros[9]: arreglo que contiene 1 is el numero ha sido asignado
******
Returns:
*	bool, retorna true si quedan numeos del dominio por instanciar y false si no quedan
**/
bool numerosAsignados(int numeros[9]){
    
    for(int i = 0; i < 9; i++)
    {
        if(numeros[i] == 0)
            return true;
    }
    return false;
}

/**
 * bool noAsignadas
 
******
Resumen Función:
*	La función encuentra una casilla vacia en la grilla de forma aleatoria
Input:
* 	int& fila: referencia de la fila a asignar
*   int& columna: referencia de la columna a asignar
*   int grilla[9][9]: grilla del killer sudoku 
*   list <unassigned> casillas_vacias: lista con las casillas vacias de la grilla
******
Returns:
*	bool, retorna true si hay casillas vacias y false cuando ya no hay casillas por asignar en la grilla	
**/

bool noAsignadasAleatoria(int& fila, int& columna, int grilla[9][9], std::list <unassigned> casillas_vacias){
    int variables_no_asignadas = casillas_vacias.size();
    int rand_num = rand()%variables_no_asignadas;
    std::list <unassigned>:: iterator itr = casillas_vacias.begin();
    std:: advance(itr,rand_num);
    fila = itr -> fila;
    columna = itr -> columna;
    int cont = 0;
    while(grilla[fila][columna] && cont < variables_no_asignadas + 1 ){
        int rand_num = rand()%variables_no_asignadas;
        std:: advance(itr,rand_num);
        fila = itr -> fila;
        columna = itr -> columna;
    }

    if (noAsignadas(fila, columna, grilla, casillas_vacias)){
        return true;
    }

    return false;
}

/**
 * bool ForwardCheckingAleatorio
 
******
Resumen Función:
*	Función que determina una solución al killer sudoku o que notiene solucion con instanciacion aleatoria
******
Input:
*   int grilla[9][9]: grilla del killer sudoku 
*   int sectores [9][9]: grilla con los sectores 
*   list <segmento> segmentos: lista de los segmentos de la grilla
*   list <unassigned> casillas_vacias: lista con las casillas vacias de la grilla 
******
Returns:
*	bool, retorna true si la instancia tiene solución y false si no la tiene
**/
bool ForwardCheckingAleatorio(int grilla[9][9], int sectores[9][9], std::list <segmento> segmentos, std::list <unassigned> casillas_vacias){
    int row, col;
    if (!noAsignadasAleatoria(row, col, grilla, casillas_vacias)){
        return true;
    }
    int numeros[9] = {0,0,0,0,0,0,0,0,0};

    while(numerosAsignados(numeros)){
        int num = 1 + rand()%9;
        while(numeros[num-1]){
            num = 1+rand()%9;
        }
        numeros[num - 1] = 1;
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
/**
 * bool ForwardChecking
 
******
Resumen Función:
*	Función que determina una solución al killer sudoku o que notiene solucion 
******
Input:
*   int grilla[9][9]: grilla del killer sudoku 
*   int sectores [9][9]: grilla con los sectores 
*   list <segmento> segmentos: lista de los segmentos de la grilla
*   list <unassigned> casillas_vacias: lista con las casillas vacias de la grilla 
******
Returns:
*	bool, retorna true si la instancia tiene solución y false si no la tiene
**/
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