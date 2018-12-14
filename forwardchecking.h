#ifndef _FORWARDCHECKING_H
#define _FORWARDCHECKING_H
#include <list>
#include "instance.h"

bool noAsignadas(int &fila, int &columna, int grilla[9][9], std:: list <unassigned> casillas_vacias);
bool CheckRows(int grilla[9][9], int fila, int num);
bool CheckColumns(int grilla[9][9], int columna, int num);
bool  CheckSubGrids(int grilla[9][9], int fila, int columna, int num);
bool CheckSum(int grilla[9][9], int sectores[9][9], std::list <segmento> segmentos, int fila, int columna, int num);
bool asignacionValida(int grilla[9][9], int sectores[9][9], std:: list<segmento> segmentos, std::list <unassigned> casillas_vacias, int fila, int columna, int num);
bool ForwardChecking(int grilla[9][9], int sectores[9][9], std::list <segmento> segmentos, std::list <unassigned> casillas_vacias);
bool numerosAsignados(int numeros[9]);
bool ForwardCheckingAleatorio(int grilla[9][9], int sectores[9][9], std::list <segmento> segmentos, std::list <unassigned> casillas_vacias);

#endif