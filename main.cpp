#include <iostream>
#include "DoubleLinkedList.h"
using namespace std;


int main() {
    cout << "Hello, World!" <<endl;
    DoubleLinkedList<int> Prueba;
    int x =5;

    Prueba.addEnd(x);
    x =7;
    Prueba.addEnd(x);
    x =8;
    Prueba.addEnd(x);
    cout << Prueba.getXNode(0)<<endl;
    cout << Prueba.getXNode(1)<<endl;
    cout << Prueba.getXNode(2)<<endl;
    Prueba.deleteXNode(1);
    cout << Prueba.getXNode(0)<<endl;
    cout << Prueba.getXNode(1)<<endl;
    cout << Prueba.getXNode(2)<<endl;

    return 0;
}
