#ifndef _INSTANCE_H
#define _INSTANCE_H
#include <iostream>
#include <list>
#include <string.h>

typedef struct{
    int identificador;
    int suma_segmento;
}segmento;

typedef struct{
    int fila; 
    int columna;
} unassigned;

class instance
{
public:
    int cuadricula[9][9];
    int  sectores [9][9];
    std::list <segmento> segmentos;
    std::list <unassigned> casillas_vacias;
public:
    instance(char archivo[1000]);
    ~instance();
};
#endif