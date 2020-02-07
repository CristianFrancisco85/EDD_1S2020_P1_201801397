#include <iostream>
#include "DoubleLinkedList.h"
#include "Stack.h"
#include <curses.h>
using namespace std;


int main() {
    initscr();
    cbreak();
    refresh();
    noecho();
    int c= getch();
    cout<<c;

    
    return 0;
}
