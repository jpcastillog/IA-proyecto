#include <iostream>
#include <list>
#include <string.h>

typedef struct{
    int identificador;
    int suma_segmento;
}segmento;

class instance
{
public:
    int cuadricula[9][9];
    int  sectores [9][9];
    std::list <segmento> segmentos;
public:
    instance(char archivo[1000]);
    ~instance();
};