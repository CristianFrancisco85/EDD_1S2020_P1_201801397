//
// Created by Cristian on 5/02/20.
//

#ifndef PRACTICA1EDD_NODO_H
#define PRACTICA1EDD_NODO_H

template <class T>

class Nodo {

public:
    Nodo();
    T getNodoValue();
    void setNodoValue(T TempValor);
    void setNextNodo(Nodo<T>* TempNodo);
    void setPrevNodo(Nodo<T>* TempNodo);
    Nodo<T>* getNextNodo();
    Nodo<T>* getPrevNodo();

private:
    //Apuntadores
    Nodo<T> *NextNodo;
    Nodo<T> *PrevNodo;
    T Valor;
};

//Constructor
template <class T>
Nodo<T>::Nodo() {
    this->NextNodo=NULL;
    this->PrevNodo=NULL;
}

//Recibe un Apuntador Nodo
template <class T>
void Nodo<T>::setNextNodo(Nodo* TempNodo) {
    this->NextNodo = TempNodo;
}

//Recibe un Apuntador Nodo
template <class T>
void Nodo<T>::setPrevNodo(Nodo* TempNodo) {
    this->PrevNodo = TempNodo;
}

//Recibe un Objeto T
template <class T>
void Nodo<T>::setNodoValue(T TempValor) {
    this->Valor = TempValor;
}

//Retorna un Objeto T
template <class T>
T Nodo<T>::getNodoValue() {
    return this->Valor;
}


// Retorna un Apuntador Nodo
template <class T>
Nodo<T>* Nodo<T>::getNextNodo() {
    return this->NextNodo;
}

// Retorna un Apuntador Nodo
template <class T>
Nodo<T>* Nodo<T>::getPrevNodo() {
    return this->PrevNodo;
}

#endif //PRACTICA1EDD_NODO_H
