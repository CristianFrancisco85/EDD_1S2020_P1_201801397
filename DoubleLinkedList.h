#ifndef PRACTICA1EDD_DOUBLELINKEDLIST_H
#define PRACTICA1EDD_DOUBLELINKEDLIST_H
#include "Nodo.h"
#include "Word.h"

template <class T>
class DoubleLinkedList {
public:
    DoubleLinkedList();
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
DoubleLinkedList<T>::DoubleLinkedList(){
    this->Head=NULL;
    this->Iterador=NULL;
    this->Size=0;
}

template <class T>
T DoubleLinkedList<T>::getFirst() {

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
T DoubleLinkedList<T>::getLast() {

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
        return NULL;
    }
}

template <class T>
T DoubleLinkedList<T>::getXNode(int x ){
    Nodo<T> NullNodo;
    try {
        if (this->Head == NULL) {
            throw -1;
        } else {
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
    this->Size++;
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
    this->Size++;
}

template <class T>
void DoubleLinkedList<T>::addX(T Value , int x ) {
    try {
        if (this->Head == NULL || x==0 || x>=(this->Size)-1 ) {
            throw -1;
        }
        else {
            Nodo<T> *NewNode = new Nodo<T>;
            NewNode->setNodoValue(Value);
            this->Iterador = this->Head;
            try {
                for (int i = 0; i < x; i++) {
                    if (this->Iterador->getNextNodo() == NULL) {
                        throw -1;
                    } else {
                        this->Iterador = this->Iterador->getNextNodo();
                    }
                }
                this->Iterador->getPrevNodo()->setNextNodo(NewNode);
                NewNode->setPrevNodo(this->Iterador->getPrevNodo());
                this->Iterador->setPrevNodo(NewNode);
                NewNode->setNextNodo(this->Iterador);
                this->Size++;
            }
            catch (int x1) {
                std::cout << "ERROR -- NO EXISTE NODO EN LA POSICION " << x <<" PARA PODER INSERTAR"<<std::endl;
            }
        }
    }
    catch (int x){
        std::cout<<"ERROR -- LA LISTA ESTA VACIA , NO ES POSIBLE REALIZAR addXNode()"<<std::endl;
        std::cout<<"ERROR -- PARA INSERTAR EN CABEZA Y COLA UTILIZE addBEgin() y addEnd()";
    }
}

template <class T>
void DoubleLinkedList<T>::deleteXNode(int x) {

    try {

        if (this->Head == NULL) {
            throw -1;
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
                if(this->Iterador->getPrevNodo() == NULL && this->Iterador->getNextNodo() == NULL){
                    this->Head=NULL;
                }
                else if(this->Iterador->getPrevNodo() == NULL){
                    this->Iterador->getNextNodo()->setPrevNodo(NULL);
                    this->Head=this->Iterador->getNextNodo();
                }
                else if(this->Iterador->getNextNodo() == NULL){
                    this->Iterador->getPrevNodo()->setNextNodo(NULL);
                }
                else {
                    this->Iterador->getPrevNodo()->setNextNodo(this->Iterador->getNextNodo());
                    this->Iterador->getNextNodo()->setPrevNodo(this->Iterador->getPrevNodo());
                }
                this -> Size--;
                delete this->Iterador;
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
int DoubleLinkedList<T>::getSize() {
    return this->Size;
}

#endif //PRACTICA1EDD_DOUBLELINKEDLIST_H
