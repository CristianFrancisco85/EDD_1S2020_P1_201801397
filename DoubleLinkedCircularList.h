//
// Created by Cristian on 13/02/20.
//

#ifndef PRACTICA1EDD_DOUBLELINKEDCIRCULARLIST_H
#define PRACTICA1EDD_DOUBLELINKEDCIRCULARLIST_H


#include "Nodo.h"
#include "Word.h"

template <class T>
class DoubleLinkedCircularList {
public:
    DoubleLinkedCircularList();
    void addBegin(T Value);
    void addEnd(T Value);
    void addX(T Value , int x);
    T getFirst();
    T getLast();
    int getSize();
    T getXNode(int x);
    void deleteXNode(int x);

private:
    Nodo<T> *Head;
    Nodo<T> *Iterador;
    int Size;
};

template <class T>
DoubleLinkedCircularList<T>::DoubleLinkedCircularList(){
    this->Head=NULL;
    this->Iterador=NULL;
    this->Size=0;
}

template <class T>
T DoubleLinkedCircularList<T>::getFirst() {

    try {
        if(this->Head == NULL){
            throw -1;
        }
        else{
            this->Iterador=this->Head;
            return this->Iterador->getNodoValue();
        }
    }
    catch (int x){
        std::cout<<"ERROR -- LA LISTA ESTA VACIA , NO ES POSIBLE REALIZAR getFirst()";
        return NULL;
    }

}

template <class T>
T DoubleLinkedCircularList<T>::getLast() {

    try {
        if (this->Head == NULL) {
            throw -1;
        } else {
            this->Iterador = this->Head;
            while (this->Iterador->getNextNodo() != this->Head) {
                this->Iterador = this->Iterador->getNextNodo();
            }
            return this->Iterador->getNodoValue();
        }
    }
    catch (int x){
        std::cout<<"ERROR -- LA LISTA ESTA VACIA , NO ES POSIBLE REALIZAR getLast()";
        return NULL;
    }
}

template <class T>
T DoubleLinkedCircularList<T>::getXNode(int x ){
    Nodo<T> NullNodo;
    try {
        if (this->Head == NULL) {
            throw -1;
        } else {
            this->Iterador = this->Head;
            try {
                for (int i = 0; i < x; i++) {
                    if (this->Iterador->getNextNodo() == this->Head) {
                        throw -1;
                    } else {
                        this->Iterador = this->Iterador->getNextNodo();
                    }
                }
                return this->Iterador->getNodoValue();
            }
            catch (int x1) {
                std::cout << "ERROR -- NO EXISTE NODO EN LA POSICION " <<x;
                return NullNodo.getNodoValue();
                //return NULL;
            }
        }
    }
    catch (int x){
        std::cout<<"ERROR -- LA LISTA ESTA VACIA , NO ES POSIBLE REALIZAR getXNode()";
        return NullNodo.getNodoValue();
        //return NULL;
    }
}


template <class T>
void DoubleLinkedCircularList<T>::addBegin(T Value) {
    Nodo<T> *NewNode = new Nodo<T>;
    NewNode->setNodoValue(Value);
    if(this->Head==NULL){
        this->Head=NewNode;
        NewNode->setNextNodo(this->Head);
    }
    else {
        NewNode->setNextNodo(this->Head);
        this->Head = NewNode;
    }
    this->Size++;
}

template <class T>
void DoubleLinkedCircularList<T>::addEnd(T Value) {

    Nodo<T> *NewNode = new Nodo<T>;
    NewNode->setNodoValue(Value);
    if(this->Head==NULL){
        this->Head=NewNode;
        NewNode->setNextNodo(this->Head);
    }
    else{
        this->Iterador=this->Head;
        while(this->Iterador->getNextNodo()!= this->Head){
            this->Iterador = this->Iterador->getNextNodo();
        }
        this->Iterador->setNextNodo(NewNode);
        NewNode->setNextNodo(this->Head);
    }
    this->Size++;
}

template <class T>
void DoubleLinkedCircularList<T>::addX(T Value , int x ) {
    if (this->Head == NULL) {
        addBegin(Value);
    }
    else if(x<=0 ){
        addBegin(Value);
    }
    else if(x>=(this->Size)-1){
        addEnd(Value);
    }
    else {
        Nodo<T> *NewNode = new Nodo<T>;
        NewNode->setNodoValue(Value);
        this->Iterador = this->Head;
        try {
            for (int i = 1; i < x; i++) {
                if (this->Iterador->getNextNodo() == this->Head) {
                    throw -1;
                } else {
                    this->Iterador = this->Iterador->getNextNodo();
                }
            }
            NewNode->setNextNodo(this->Iterador->getNextNodo());
            this->Iterador->setNextNodo(NewNode);
            this->Size++;
        }
        catch (int x1) {
            std::cout << "ERROR -- NO EXISTE NODO EN LA POSICION " << x <<" PARA PODER INSERTAR"<<std::endl;
        }
    }
}


template <class T>
void DoubleLinkedCircularList<T>::deleteXNode(int x) {

    try {

        if (this->Head == NULL) {
            throw -1;
        }
        else {
            this->Iterador = this->Head;
            try {
                for (int i = 1; i < x; i++) {
                    if (this->Iterador->getNextNodo() == this->Head) {
                        throw -1;
                    } else {
                        this->Iterador = this->Iterador->getNextNodo();
                    }
                }
                if(this->Iterador->getNextNodo() == this->Head){
                    //this->Head=NULL;
                    std::cout << "ERROR -- NO EXISTE NODO EN LA POSICION " << x;
                }
                else {
                    this->Iterador->setNextNodo(this->Iterador->getNextNodo()->getNextNodo());
                }
                this -> Size--;
                delete this->Iterador->getNextNodo();
                this->Iterador = NULL;
            }
            catch (int x1) {
                std::cout << "ERROR -- NO EXISTE NODO EN LA POSICION " << x;
            }
        }
    }
    catch (int x){
        std::cout<<"ERROR -- LA LISTA ESTA VACIA , NO ES POSIBLE REALIZAR deleteXNode()";
    }
}

template <class T>
int DoubleLinkedCircularList<T>::getSize() {
    return this->Size;
}


#endif //PRACTICA1EDD_DOUBLELINKEDCIRCULARLIST_H
