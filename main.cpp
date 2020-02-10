#include <iostream>
#include "DoubleLinkedList.h"
#include "Stack.h"
#include <curses.h>
#include <clocale>

using namespace std;

void showMenu(WINDOW * win);
void clearWin(WINDOW * win);

int main() {
    int height,width,startx,starty;
    setlocale(LC_CTYPE,"Spanish");

    height = 26,
    width= 81;
    startx = 2;
    starty = 2;

    // CONFIGURACIONES INICIALES
    initscr();
    cbreak();
    noecho();

    //IMPRIMIR ENCABEZADO
    attron(A_REVERSE);
    move(0,2);
    printw("             PRACTICA 1 - CRISTIAN FRANCISCO MEONO CANEL -  201801397             ");
    attroff(A_REVERSE);
    WINDOW * borderwin = newwin(height+2,width+2,1,1);
    WINDOW * win = newwin(height,width,starty,startx);
    refresh();
    box (borderwin,124,45);
    wrefresh(borderwin);

    showMenu(win);

    getch();
    wdelch(win);
    wrefresh(win);
    getch();
    wdelch(win);
    wrefresh(win);
    getch();
    clearWin(win);
    getch();
    return 0;
}

void clearWin(WINDOW * win){
    werase(win);
    wrefresh(win);
}


void showMenu(WINDOW * win){
    mvwprintw(win,2,5,"UNIVERSIDAD DE SAN CARLOS DE GUATEMALA");
    mvwprintw(win,3,5,"FACULTAD DE INGENIERIA");
    mvwprintw(win,4,5,"ESTRUCTURAS DE DATOS");

    mvwprintw(win,6,5,"MENU:");
    mvwprintw(win,8,6,"1.Crear Archivo");
    mvwprintw(win,9,6,"2.Abrir Archivo");
    mvwprintw(win,10,6,"3.Archivos Recientes");
    mvwprintw(win,11,6,"4.Salir");
    wrefresh(win);
}
