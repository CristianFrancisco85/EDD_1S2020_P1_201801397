//
// Created by Cristian on 13/02/20.
//

#ifndef PRACTICA1EDD_ARCHIVE_H
#define PRACTICA1EDD_ARCHIVE_H

#include <iostream>

using namespace std;

class Archive {

public:
    Archive();
    void setNombre(string arg1);
    void setRuta(string arg1);
    string getNombre();
    string getRuta();
private:
    string Nombre;
    string Ruta;
};

Archive::Archive(){

}

void Archive::setNombre(string arg1) {
    this->Nombre=arg1;
}

void Archive::setRuta(string arg1) {
    this->Ruta=arg1;
}

string Archive::getNombre() {
    return  this->Nombre;
}

string Archive::getRuta() {
    return  this->Ruta;
}



#endif //PRACTICA1EDD_ARCHIVE_H
