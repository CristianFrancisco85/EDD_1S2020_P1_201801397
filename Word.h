//
// Created by Cristian on 11/02/20.
//

#ifndef PRACTICA1EDD_WORD_H
#define PRACTICA1EDD_WORD_H

#include <iostream>

using namespace std;

class Word {
public:
    Word();
    void setWord(string arg1);
    void setPosBegin(int arg1);
    void setPosEnd(int arg1);
    string getWord();
    int getPosBegin();
    int getPosEnd();

private:
    string Palabra;
    int posBegin;
    int posEnd;
};

Word::Word(){
    this->Palabra = "";
    this->posBegin =0;
    this->posEnd = 0;
}

void Word::setWord(string arg1) {
    this->Palabra = arg1;
}

void Word::setPosBegin(int arg1) {
    this->posBegin = arg1;
}

void Word::setPosEnd(int arg1) {
    this->posEnd = arg1;
}

string Word::getWord() {
    return this->Palabra;
}

int Word::getPosBegin() {
    return this->posBegin;
}

int Word::getPosEnd() {
    return this->posEnd;
}


#endif //PRACTICA1EDD_WORD_H
