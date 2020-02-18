//
// Created by Cristian on 17/02/20.
//

#ifndef PRACTICA1EDD_LINKEDLIST_H
#define PRACTICA1EDD_LINKEDLIST_H

#include "Nodo.h"

template <class T>
class LinkedList {
public:
    LinkedList();
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
LinkedList<T>::LinkedList(){
    this->Head=NULL;
    this->Iterador=NULL;
    this->Size=0;
}

template <class T>
T LinkedList<T>::getFirst() {

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
        Nodo<T> NullNodo;
        return NullNodo.getNodoValue();
    }

}

template <class T>
T LinkedList<T>::getLast() {

    try {
        if (this->Head == NULL) {
            throw -1;
        } else {
            this->Iterador = this->Head;
            while (this->Iterador->getNextNodo() != NULL) {
                this->Iterador = this->Iterador->getNextNodo();
            }
            return this->Iterador->getNodoValue();
        }
    }
    catch (int x){
        std::cout<<"ERROR -- LA LISTA ESTA VACIA , NO ES POSIBLE REALIZAR getLast()";
        Nodo<T> NullNodo;
        return NullNodo.getNodoValue();
        //return NULL;
    }
}

template <class T>
T LinkedList<T>::getXNode(int x ){
    Nodo<T> NullNodo;
    try {
        if (this->Head == NULL) {
            throw -1;
        }
        else if(x<=0 ){
            return  this->getFirst();
        }
        else if(x>=(this->Size)-1){
            return this->getLast();
        }
        else {
            this->Iterador = this->Head;
            try {
                for (int i = 0; i < x; i++) {
                    if (this->Iterador->getNextNodo() == NULL) {
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
void LinkedList<T>::addBegin(T Value) {
    Nodo<T> *NewNode = new Nodo<T>;
    NewNode->setNodoValue(Value);
    if(this->Head==NULL){
        this->Head=NewNode;
    }
    else {
        NewNode->setNextNodo(this->Head);
        this->Head = NewNode;
    }
    this->Size++;
}

template <class T>
void LinkedList<T>::addEnd(T Value) {

    Nodo<T> *NewNode = new Nodo<T>;
    NewNode->setNodoValue(Value);
    if(this->Head==NULL){
        this->Head=NewNode;
    }
    else{
        this->Iterador=this->Head;
        while(this->Iterador->getNextNodo()!= NULL){
            this->Iterador = this->Iterador->getNextNodo();
        }
        this->Iterador->setNextNodo(NewNode);
    }
    this->Size++;
}

template <class T>
void LinkedList<T>::addX(T Value , int x ) {
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
                if (this->Iterador->getNextNodo() == NULL) {
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
void LinkedList<T>::deleteXNode(int x) {

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
                if(this->Iterador->getNextNodo() == NULL){
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
int LinkedList<T>::getSize() {
    return this->Size;
}


#endif //PRACTICA1EDD_LINKEDLIST_H
