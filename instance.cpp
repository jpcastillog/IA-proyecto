#include <iostream>
#include <list>
#include <string.h>
#include <stdio.h>
#include "instance.h"
/** 
* 	 instance
******
Resumen Función:
*	constructor de la instancia, recibe como parametro un string con la ruta del archivo a leer
******
Input:
* 	char archivo[1000]: Ruta del archivo con la instancia a resolver
******
Returns:
*		
**/
instance::instance(char archivo [1000])
{
    memset(cuadricula, 0, sizeof(cuadricula));
    FILE* pFile;
    pFile = fopen(archivo, "r");
    int sector1, sector2, sector3, sector4, sector5, sector6, sector7, sector8, sector9 ;
    char c;
    char num1, num2, num3, num4, num5, num6, num7, num8, num9;
    int n1, n2, n3, n4, n5, n6, n7, n8, n9;
     
    if (pFile != NULL) {
        int cont = 0;
        while(!feof(pFile) && cont < 9){

            fscanf(pFile, "%c%c%i %c%c%i %c%c%i %c%c%i %c%c%i %c%c%i %c%c%i %c%c%i %c%c%i\n",&num1, &c,&sector1, &num2, &c, &sector2, &num3, &c,&sector3,&num4, &c, &sector4, &num5, &c, &sector5,&num6, &c ,&sector6, &num7, &c,&sector7, &num8, &c,&sector8, &num9, &c, &sector9);
            
            n1 = (int)num1 - (int)48; // -> se convierten los numeros a entero debido  a que las casillas vacias son "."
            n2 = (int)num2 - (int)48;
            n3 = (int)num3 - (int)48;
            n4 = (int)num4 - (int)48;
            n5 = (int)num5 - (int)48;
            n6 = (int)num6 - (int)48;
            n7 = (int)num7 - (int)48;
            n8 = (int)num8 - (int)48;
            n9 = (int)num9 - (int)48;

           
            int fila[9] = {n1, n2, n3, n4, n5, n6, n7, n8, n9};
            int sectors[9] = {sector1, sector2, sector3, sector4, sector5, sector6, sector7, sector8, sector9};
            // Se cargan los valores al arreglo que representa la grilla y que representa los sectores
            for(int i = 0; i < 9; i++)
            {
                if (fila[i] > 0){
                    this -> cuadricula [cont][i] = fila[i];
                }
                
                else{
                    unassigned casilla_vacia;
                    casilla_vacia.fila = cont;
                    casilla_vacia.columna = i;
                    // Se agregan las casillas vacias a la lista
                    this ->casillas_vacias.push_back(casilla_vacia);
                }
                this -> sectores[cont][i] = sectors[i];

            }

            cont ++;
        }
        // Se leen los sectores y sus respectivas sumas 
        while(!feof(pFile)){
            segmento seg;
            int sector;
            int suma;
            fscanf(pFile, "%c%i:%i\n", &c, &sector, &suma);
            seg.identificador = sector; 
            seg.suma_segmento = suma;
            // Se agregan los segmentos con su suma al la lista segmentos
            this -> segmentos.push_back(seg);
        }


    }
    
    else
    {
        std::cout << "No se encontro el archivo" << std::endl;
    }
    
    fclose(pFile);
}

instance::~instance()
{
}
