#ifndef AVL_H
#define AVL_H
#include <iostream>
using namespace std;
class AVL;
class Nodo {
  public:   
   Nodo(const int dat, Nodo *pad=NULL, Nodo *izq=NULL, Nodo *der=NULL) :
     dato(dat), padre(pad), izquierdo(izq), derecho(der), FE(0) {}   
   int dato;
   int FE; //PARA GUARDAR EL FACTOR EQUILIBRO, DIFERENCIA ENTRE LA ALTURA de la rama derecha e izquierda
   Nodo *izquierdo;
   Nodo *derecho;
   Nodo *padre;
   friend class AVL;
};


#endif 

