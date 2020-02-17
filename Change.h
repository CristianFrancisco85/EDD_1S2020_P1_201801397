//
// Created by Cristian on 13/02/20.
//

#ifndef PRACTICA1EDD_CHANGE_H
#define PRACTICA1EDD_CHANGE_H

#include <iostream>

using namespace std;

class Change {

public:

    Change();

    void setPalabraBuscar(string arg1);
    void setpalabraReemplazar(string arg1);
    void setEstado(bool arg1);
    void setChar(char arg1);
    void setPointerList(int arg1);
    void setTipo(bool arg1);

    string getPalabraBuscar();
    string getPalabraReemplazar();
    bool getEstado();
    char getChar();
    int getPointerList();
    bool getTipo();
private:
    string palabraBuscar;
    string palabrasReemplazar;
    bool Estado;
    char Caracter;
    int PointerList;
    //Falso si se borro caracter y verdadero si se escribio
    bool Tipo;
};


Change::Change(){
    this->palabraBuscar="";
    this->palabrasReemplazar="";
    this->Estado=false;
    this->Caracter = 0;
    this->PointerList=0;
    this->Tipo = false;
}

void Change::setPalabraBuscar(string arg1) {
    this->palabraBuscar = arg1;
}

void Change::setpalabraReemplazar(string arg1) {
    this->palabrasReemplazar =  arg1;
}

void Change::setEstado(bool arg1) {
    this->Estado = arg1;
}

void Change::setChar(char arg1) {
    this->Caracter = arg1;
}

void Change::setPointerList(int arg1) {
    this->PointerList = arg1;
}

void Change::setTipo(bool arg1) {
    this->Tipo = arg1;
}

string Change::getPalabraBuscar() {
    return this->palabraBuscar;
}

string Change::getPalabraReemplazar() {
    return this->palabrasReemplazar;
}

bool Change::getEstado() {
    return this->Estado;
}

char Change::getChar() {
    return this->Caracter;
}

int Change::getPointerList() {
    return this->PointerList;
}

bool Change::getTipo() {
    return this->Tipo;
}



#endif //PRACTICA1EDD_CHANGE_H
