//
// Created by Cristian on 5/02/20.
//

#ifndef PRACTICA1EDD_DOUBLELINKEDLIST_H
#define PRACTICA1EDD_DOUBLELINKEDLIST_H

#include "Nodo.h"

template <class T>

class DoubleLinkedList {
public:
    DoubleLinkedList();
    void addBegin(T Value);
    void addEnd(T Value);
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
DoubleLinkedList<T>::DoubleLinkedList(){
    this->Head=NULL;
    this->Iterador=NULL;
    this->Size=0;
}

template <class T>
T DoubleLinkedList<T>::getFirst() {
    if(this->Head == NULL){
        //CONTROLAR EXCEPCION PARA UNA LISTA VACIA
    }
    else{
        this->Iterador=this->Head;
        return this->Iterador->getNodoValue();
    }
}

template <class T>
T DoubleLinkedList<T>::getLast() {
    if(this->Head == NULL){
        //CONTROLAR EXCEPCION PARA UNA LISTA VACIA
    }
    else{
        this->Iterador=this->Head;
        while(this->Iterador->getNextNodo()!= NULL){
            this->Iterador = this->Iterador->getNextNodo();
        }
        return this->Iterador->getNodoValue();
    }
}

template <class T>
T DoubleLinkedList<T>::getXNode(int x ){
    if(this->Head == NULL){
        //CONTROLAR EXCEPCION PARA UNA LISTA VACIA
    }
    else{
        this->Iterador=this->Head;
        for(int i =0;i<x;i++){
            if(this->Iterador->getNextNodo()==NULL){
                //CONTROLAR EXCEPCION DE NODO INEXISTENTE
                return 0;
            }
            else {
                this->Iterador = this->Iterador->getNextNodo();
            }
        }
        return this->Iterador->getNodoValue();
    }
}

template <class T>
void DoubleLinkedList<T>::addBegin(T Value) {
    Nodo<T> *NewNode = new Nodo<T>;
    NewNode->setNodoValue(Value);
    if(this->Head==NULL){
        this->Head=NewNode;
    }
    else {
        this->Head->setPrevNodo(NewNode);
        NewNode->setNextNodo(this->Head);
        this->Head = NewNode;
    }
}

template <class T>
void DoubleLinkedList<T>::addEnd(T Value) {

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
        NewNode->setPrevNodo(this->Iterador);
    }
}

template <class T>
void DoubleLinkedList<T>::deleteXNode(int x) {
    if(this->Head == NULL){
        //CONTROLAR EXCEPCION PARA UNA LISTA VACIA
    }
    else{
        this->Iterador=this->Head;
        for(int i =0;i<x;i++){
            if(this->Iterador->getNextNodo()==NULL){
                //CONTROLAR EXCEPCION DE NODO INEXISTENTE
            }
            else {
                this->Iterador = this->Iterador->getNextNodo();
            }
        }
        this->Iterador->getPrevNodo()->setNextNodo(this->Iterador->getNextNodo());
        this->Iterador->getNextNodo()->setPrevNodo(this->Iterador->getPrevNodo());
        delete this->Iterador;
        this->Iterador=NULL;

    }
}




#endif //PRACTICA1EDD_DOUBLELINKEDLIST_H
