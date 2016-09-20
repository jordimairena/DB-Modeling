/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jordi
 *
 * Created on 18 de septiembre de 2016, 12:05 PM
 */
#include "Nodo.h"
#include "AVL.h"
#include <cstdlib>
#include <iostream>
using namespace std;
/*
 * 
 */
int main(int argc, char** argv) {
    // el arbol de int
   AVL ArbolInt;

   // Insertar nodos en árbol:
   ArbolInt.Insertar(1);
   ArbolInt.Insertar(1);
   ArbolInt.Insertar(20);
   ArbolInt.Insertar(40);
   ArbolInt.Insertar(2);
   ArbolInt.Insertar(9);
   ArbolInt.Insertar(7);
   ArbolInt.Insertar(3);
   ArbolInt.Insertar(8);
   ArbolInt.Insertar(80);
   ArbolInt.Insertar(36);
   ArbolInt.Insertar(69);
   ArbolInt.Insertar(12);
   ArbolInt.Insertar(58);
   ArbolInt.Insertar(50);
   ArbolInt.Insertar(20);
   cout << "Borrar 8" <<endl;
   ArbolInt.Borrar(8);   
   return 0;
}

 

