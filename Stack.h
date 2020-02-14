#ifndef PRACTICA1EDD_STACK_H
#define PRACTICA1EDD_STACK_H

#include "Nodo.h"
#include <iostream>

template <class T>
class Stack {
public:
    Stack();
    void push(T Value);
    T pop();
    T pick();
    int getSize();
private:
    Nodo<T> *Head;
    int Size;

};


template <class T>
Stack<T>::Stack(){
    this->Head=NULL;
    this->Size=0;
}

template <class T>
void Stack<T>::push(T Value) {

    Nodo<T> *NewNode = new Nodo<T>;
    NewNode->setNodoValue(Value);
    if(this->Head==NULL){
        this->Head=NewNode;
    }
    else{
        this->Head->setNextNodo(NewNode);
        NewNode->setPrevNodo(this->Head);
        this->Head=NewNode;
    }
    this->Size++;
}

template <class T>
T Stack<T>::pop() {
    Nodo<T> NullNodo;
    try {
        if (this->Head == NULL) {
            throw -1;
        }
        else {
            T Value = this->Head->getNodoValue();
            if(this->Head->getPrevNodo() == NULL){
                delete this->Head;
                this->Head = NULL;
            }
            else{
                this->Head = this->Head->getPrevNodo();
                delete this->Head->getNextNodo();
            }
            this->Size--;
            return Value;
        }
    }
    catch (int x){
        std::cout<<"ERROR -- LA PILA ESTA VACIA , NO ES POSIBLE REALIZAR pop()";
        return NullNodo.getNodoValue();
    }
}

template <class T>
T Stack<T>::pick() {
    Nodo<T> NullNodo;
    try {
        if (this->Head == NULL) {
            throw -1;
        }
        else {
            T Value = this->Head->getNodoValue();
            return Value;
        }
    }
    catch (int x){
        std::cout<<"ERROR -- LA PILA ESTA VACIA , NO ES POSIBLE REALIZAR pick()";
        return NullNodo.getNodoValue();
    }
}

template <class T>
int Stack<T>::getSize() {
    return  this->Size;
}


#endif //PRACTICA1EDD_STACK_H