
#ifndef Nodo_H
#define Nodo_H
#define DERECHA 1
#define IZQUIERDA 0
#define TRUE 1
#define FALSE 0

class AVL {
private:
    enum {
        IZQUIERDO, DERECHO
    };    
    Nodo *raiz;
    Nodo *actual;
    int contador;
    int altura;

public:    
    AVL() : raiz(NULL), actual(NULL) {
    }
    ~AVL() {
        Eliminar(raiz);
    }
    // insertar en el arbol
    void Insertar(const int dat);
    // borrar algo del arbol
    void Borrar(const int dat);
    // para buscar nodos en caso pida Victor
    bool Buscar(const int dat);
    // ver si tiene algo el arbol
    bool Vacio(Nodo *r) {
        return r == NULL;
    }
    // ver si es hoja
    bool EsHoja(Nodo *r) {
        return !r->derecho && !r->izquierdo;
    }
    
    
    int Altura(const int dat);
    // regresar el valor del nodo para cuando dibujemos
    int &ValorActual() {
        return actual->dato;
    }
    // moverse a la raiz
    void Raiz() {
        actual = raiz;
    }

private:
    // las funciones para equilibrar el arbol
    void Equilibrar(Nodo *nodo, int, bool);
    void RSI(Nodo* nodo); // 
    void RSD(Nodo* nodo);
    void RDI(Nodo* nodo);
    void RDD(Nodo* nodo);
    void Eliminar(Nodo* &);
    void auxContador(Nodo*);
    void auxAltura(Nodo*, int);
};
void AVL::Eliminar(Nodo* &nodo) {    
    if (nodo) {
        Eliminar(nodo->izquierdo); // Eliminar izquierdo
        Eliminar(nodo->derecho); // Eliminar derecho
        delete nodo; // Eliminar nodo
        nodo = NULL;
    }
}
void AVL::Insertar(const int dat) {
    Nodo *padre = NULL;

    cout << "Insertar: " << dat << endl;
    actual = raiz;    
    while (!Vacio(actual) && dat != actual->dato) {
        padre = actual;
        if (dat > actual->dato) actual = actual->derecho;
        else if (dat < actual->dato) actual = actual->izquierdo;
    }    
    if (!Vacio(actual)) return;    
    if (Vacio(padre)) raiz = new Nodo(dat);        
    else if (dat < padre->dato) {
        padre->izquierdo = new Nodo(dat, padre);
        Equilibrar(padre, IZQUIERDO, true);
    }        
    else if (dat > padre->dato) {
        padre->derecho = new Nodo(dat, padre);
        Equilibrar(padre, DERECHO, true);
    }
}

void AVL::Equilibrar(Nodo *nodo, int rama, bool nuevo) {
    bool salir = false;    
    while (nodo && !salir) {
        if (nuevo)
            if (rama == IZQUIERDO) nodo->FE--; 
            else nodo->FE++;
        else
            if (rama == IZQUIERDO) nodo->FE++; 
        else nodo->FE--;
        if (nodo->FE == 0) salir = true; 
        else if (nodo->FE == -2) { 
            if (nodo->izquierdo->FE == 1) RDD(nodo); 
            else RSD(nodo); 
            salir = true;
        } else if (nodo->FE == 2) { 
            if (nodo->derecho->FE == -1) RDI(nodo); 
            else RSI(nodo); 
            salir = true;
        }
        if (nodo->padre)
            if (nodo->padre->derecho == nodo) rama = DERECHO;
            else rama = IZQUIERDO;
        nodo = nodo->padre;
    }
}

// rotar dos veces a la derecha
void AVL::RDD(Nodo* nodo) {
    cout << "rota dos veces a la derecha" << endl;
    Nodo *Padre = nodo->padre;
    Nodo *P = nodo;
    Nodo *Q = P->izquierdo;
    Nodo *R = Q->derecho;
    Nodo *B = R->izquierdo;
    Nodo *C = R->derecho;

    if (Padre)
        if (Padre->derecho == nodo) Padre->derecho = R;
        else Padre->izquierdo = R;
    else raiz = R;    
    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;    
    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;    
    switch (R->FE) {
        case -1: Q->FE = 0;
            P->FE = 1;
            break;
        case 0: Q->FE = 0;
            P->FE = 0;
            break;
        case 1: Q->FE = -1;
            P->FE = 0;
            break;
    }
    R->FE = 0;
}

// rotar dos veces a la izquierda

void AVL::RDI(Nodo* nodo) {
    cout << "rota dos veces a la izquierda" << endl;
    Nodo *Padre = nodo->padre;
    Nodo *P = nodo;
    Nodo *Q = P->derecho;
    Nodo *R = Q->izquierdo;
    Nodo *B = R->izquierdo;
    Nodo *C = R->derecho;
    if (Padre)
        if (Padre->derecho == nodo) Padre->derecho = R;
        else Padre->izquierdo = R;
    else raiz = R;    
    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;
    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;
    switch (R->FE) {
        case -1: P->FE = 0;
            Q->FE = 1;
            break;
        case 0: P->FE = 0;
            Q->FE = 0;
            break;
        case 1: P->FE = -1;
            Q->FE = 0;
            break;
    }
    R->FE = 0;
}

// rotar una vez a la derecha

void AVL::RSD(Nodo* nodo) {
    cout << "rota una vez a la derecha" << endl;
    Nodo *Padre = nodo->padre;
    Nodo *P = nodo;
    Nodo *Q = P->izquierdo;
    Nodo *B = Q->derecho;
    if (Padre)
        if (Padre->derecho == P) Padre->derecho = Q;
        else Padre->izquierdo = Q;
    else raiz = Q;  
    P->izquierdo = B;
    Q->derecho = P;
    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;
    P->FE = 0;
    Q->FE = 0;
}

// rotar una vez a la izquierda
void AVL::RSI(Nodo* nodo) {
    cout << "roto una vez a la izquierda" << endl;
    Nodo *Padre = nodo->padre;
    Nodo *P = nodo;
    Nodo *Q = P->derecho;
    Nodo *B = Q->izquierdo;
    if (Padre)
        if (Padre->derecho == P) Padre->derecho = Q;
        else Padre->izquierdo = Q;
    else raiz = Q;
    P->derecho = B;
    Q->izquierdo = P;
    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;
    P->FE = 0;
    Q->FE = 0;
}

// eliminar un elemento

void AVL::Borrar(const int dat) {
    Nodo *padre = NULL;
    Nodo *nodo;
    int aux;
    actual = raiz;    
    while (!Vacio(actual)) {
        if (dat == actual->dato) { 
            if (EsHoja(actual)) { 
                if (padre)                    
                    if (padre->derecho == actual) padre->derecho = NULL;
                    else if (padre->izquierdo == actual) padre->izquierdo = NULL;
                delete actual; 
                actual = NULL;                
                if ((padre->derecho == actual && padre->FE == 1) ||
                        (padre->izquierdo == actual && padre->FE == -1)) {
                    padre->FE = 0;
                    actual = padre;
                    padre = actual->padre;
                }
                if (padre)
                    if (padre->derecho == actual) Equilibrar(padre, DERECHO, false);
                    else Equilibrar(padre, IZQUIERDO, false);
                return;
            } else { 
                padre = actual;                
                if (actual->derecho) {
                    nodo = actual->derecho;
                    while (nodo->izquierdo) {
                        padre = nodo;
                        nodo = nodo->izquierdo;
                    }
                }                    
                else {
                    nodo = actual->izquierdo;
                    while (nodo->derecho) {
                        padre = nodo;
                        nodo = nodo->derecho;
                    }
                }               
                aux = actual->dato;
                actual->dato = nodo->dato;
                nodo->dato = aux;
                actual = nodo;
            }
        } else { 
            padre = actual;
            if (dat > actual->dato) actual = actual->derecho;
            else if (dat < actual->dato) actual = actual->izquierdo;
        }
    }
}



// buscar un dato en el arbol
bool AVL::Buscar(const int dat) {
    actual = raiz;
    while (!Vacio(actual)) {
        if (dat == actual->dato) return true; 
        else if (dat > actual->dato) actual = actual->derecho; 
        else if (dat < actual->dato) actual = actual->izquierdo;
    }
    return false; 
}

// la altura del nodo que esta el dato
int AVL::Altura(const int dat) {
    int altura = 0;
    actual = raiz;    
    while (!Vacio(actual)) {
        if (dat == actual->dato) return altura; 
        else {
            altura++; 
            if (dat > actual->dato) actual = actual->derecho;
            else if (dat < actual->dato) actual = actual->izquierdo;
        }
    }
    return -1; 
}
// Función de prueba para recorridos del árbol
void Mostrar(int &d, int FE) {
    cout << d << "(" << FE << "),";
}
#endif 
