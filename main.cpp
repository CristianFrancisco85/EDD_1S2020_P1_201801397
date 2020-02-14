#include <iostream>
#include "DoubleLinkedList.h"
#include "Stack.h"
#include "Word.h"
#include <curses.h>
#include <clocale>
#include <fstream>
#include <string>
#include "Change.h"


using namespace std;

//MUESTRA MENU
void showMenu(WINDOW * win);

// LIMPIA VENTANA DE TEXTO
void clearWin(WINDOW * win);

// CREA UN NUEVO ARCHIVO
void newArchive(WINDOW * win,string Archivo);

//MUEVE HACIA ATRAS EL CURSOR
void moveBack(WINDOW * win,int posy,int posx);

//MUEVE HACIA ADELANTE EL CURSOR
void moveFront(WINDOW * win,int posy,int posx);

//ELIMINA UN CARCTER HACIA ATRAS EN PANTALLA Y LISTA
void deleteChar(WINDOW * win, int posy, int posx, DoubleLinkedCircularList<char> *Lista);

//DEVUELVE EL TEXTO EN LA LISTA
string getText(DoubleLinkedCircularList<char> *Lista);

//GUARDA EL ARCHIVO
void saveArchive(DoubleLinkedCircularList<char> *Lista, string NombreArchivo, bool Nuevo);

//MENU DE REPORTES
void showReportsMenu(WINDOW * win, DoubleLinkedCircularList<char> *Lista, int posy, int posx);

// GRAFICA LA LISTA
void graphList (DoubleLinkedCircularList<char> *Lista);

//DIVIDE LA LISTA DE CARACTERES EN UNA LISTA DE PALABRAS
void divideWords(DoubleLinkedCircularList<char> *ListaCh , DoubleLinkedCircularList<Word> *ListaWor);

// BUSCA Y REEMPLAZA EN BASE A PALABRAS ACTUALIZA LISTA DE CARACTERES
int searchAndReplace (DoubleLinkedCircularList<char> *ListaCh , DoubleLinkedCircularList<Word> *ListaWor, Stack<Change> *PilaCa , Stack<Change> *PilaCaR, string palabraBuscar , string palabraReemplazar, bool Tipo);

//PIDE PARAMETROS AL USUARIO Y LOS MUESTRA EN PANTALLA
void showSearchAndReplace(WINDOW * win, DoubleLinkedCircularList<char> *ListaCh, DoubleLinkedCircularList<Word> *ListaWor, Stack<Change> *PilaCa);

// VARIABLES GLOBALES

int archivo=0;

// FUNCIONES PRINCIPALES

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
    raw();
    keypad(stdscr, TRUE);

    //IMPRIMIR ENCABEZADO y VENTANA
    attron(A_REVERSE);
    move(0,2);
    printw("             PRACTICA 1 - CRISTIAN FRANCISCO MEONO CANEL -  201801397             ");
    attroff(A_REVERSE);
    WINDOW * borderwin = newwin(height+2,width+2,1,1);
    WINDOW * win = newwin(height,width,starty,startx);
    refresh();
    box (borderwin,124,45);
    wrefresh(borderwin);

    // MOSTRAR MENU
    showMenu(win);

    bool Control = true;

    while(Control){
        int ch = getch();

        switch(ch){
                //OPCION 1 -- Crear Archivo
            case 49:
                newArchive(win,"");
                break;
                //OPCION 2  -- Abrir Archvo
            case 50: {
                mvwprintw(win, 18, 6, "Escriba Ruta de Archivo: ");
                wrefresh(win);
                bool option2Control = true;
                string Ruta="";
                while (option2Control) {
                    ch=getch();
                    if (ch > 32 && ch <= 126) {
                        Ruta.push_back(ch);
                        wprintw(win,"%c", ch);
                        wrefresh(win);
                    }
                    if (ch == 10) {
                        option2Control = false;
                        newArchive(win,Ruta);
                    }
                }
            }
                break;
                //OPCION 3 -- Archivos Recientes
            case 51:
                wprintw(win,"Ctrl+L");
                wrefresh(win);
                break;
                //OPCION 4 -- Salir
            case 52:
                clearWin(win);
                mvwprintw(win,0,0,"Hasta la proxima -- Presione una tecla para continuar...");
                wrefresh(win);
                getch();
                clearWin(win);
                endwin();
                Control = false;
                break;
        }
    }

    return 0;
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

void newArchive(WINDOW * win, string Archivo){

    //ESTRUCTURAS DE DATOS

    DoubleLinkedCircularList<char> TempArchivo;
    Stack<Change> ChangesList;
    Stack<Change> RevertList;
    DoubleLinkedCircularList<Word> *ListaWor = new DoubleLinkedCircularList<Word>;

    //UBICACION DE CURSOR
    int posx = 0;
    int posy = 0;
    int pointerList=0;
    int ch;
    bool Control = true;

    //ENCABEZADO
    attron(A_REVERSE);
    move(0,2);
    printw("             ^W(Buscar y Reemplazar)  ^C(Reportes)  ^S(GUARDAR)             ");
    attroff(A_REVERSE);

    clearWin(win);
    wmove(win,0,0);

    if(Archivo!=""){
        char letra;
        ifstream fichero;
        fichero.open(Archivo);
        if(!fichero.fail()){
            fichero.get(letra);
            while(!fichero.eof()){
                if(letra>=32 && letra<=126){
                    TempArchivo.addEnd((char)letra);
                    wprintw(win,"%c",letra);
                    wrefresh(win);
                    getyx(win,posy,posx);
                }
                fichero.get(letra);
            }
            fichero.close();
        }
        else{
            wprintw(win,"NO SIRVE");
        }
    }


    while(Control){
        ch = getch();

        switch (ch){
            //BUSCAR Y REEMPLAZAR ^W
            case 23:
                showSearchAndReplace(win,&TempArchivo,ListaWor,&ChangesList);
                pointerList=TempArchivo.getSize();
                getyx(win,posy,posx);
                break;
            // REPORTES ^C
            case 3:
                showReportsMenu(win, &TempArchivo, posy, posx);
                break;
            // GUARDAR ^S
            case 19: {
                attron(A_REVERSE);
                if(Archivo == ""){
                    move(0, 2);
                    printw("                                                                             ");
                    move(0, 2);
                    printw("         Nombre de Archivo (sin extension) : ");
                    bool boolArchivo = true;
                    while (boolArchivo) {
                        ch = getch();
                        if (ch > 32 && ch <= 126) {
                            Archivo.push_back(ch);
                            printw("%c", ch);
                            wrefresh(win);
                        }
                        if (ch == 10) {
                            boolArchivo = false;
                            saveArchive(&TempArchivo, Archivo,true);
                        }
                    }
                }
                else{
                    saveArchive(&TempArchivo, Archivo,false);
                }
                move(0,2);
                printw("             ^W(Buscar y Reemplazar)  ^C(Reportes)  ^S(GUARDAR)             ");
                attroff(A_REVERSE);
                wmove(win,posy,posx);
            }
                break;
            // GUARDAR ^X
            case 24:
                clearWin(win);
                mvwprintw(win,0,0,"Hasta la proxima -- Presione una tecla para continuar...");
                wrefresh(win);
                getch();
                clearWin(win);
                showMenu(win);
                Control=false;
                break;
            //MOVER CURSOR ATRAS
            case KEY_LEFT:
                if(pointerList>0){
                    pointerList--;
                    moveBack(win,posy,posx);
                    getyx(win,posy,posx);
                    wrefresh(win);
                }
                break;
            //MOVER CURSOR ADELANTE
            case KEY_RIGHT:
                if(pointerList<TempArchivo.getSize()){
                    pointerList++;
                    moveFront(win,posy,posx);
                    getyx(win,posy,posx);
                    wrefresh(win);
                }
                break;
            //ELIMINAR CARACTER
            case 127:
                if(pointerList>0){
                    pointerList--;
                    moveBack(win,posy,posx);
                    TempArchivo.deleteXNode(pointerList);
                    //deleteChar(win,posy,posx,&TempArchivo);
                    wdelch(win);
                    wrefresh(win);
                    getyx(win,posy,posx);
                }
                break;
            // Ctrl+Y
            case 25:
                if(RevertList.getSize()>0){
                    if(RevertList.pick().getPalabraReemplazar()!=""){
                        string arg1=RevertList.pick().getPalabraBuscar();
                        string arg2=RevertList.pick().getPalabraReemplazar();
                        searchAndReplace(&TempArchivo,ListaWor,&ChangesList,&RevertList,arg1,arg2,false);
                    }
                    else{

                    }
                }
                clearWin(win);
                mvwprintw(win,0,0,getText(&TempArchivo).c_str());
                wrefresh(win);
                break;
            // Ctrl+Z
            case 26:

                if(ChangesList.getSize()>0){
                    if(ChangesList.pick().getPalabraReemplazar()!=""){
                        string arg1=ChangesList.pick().getPalabraBuscar();
                        string arg2=ChangesList.pick().getPalabraReemplazar();
                        searchAndReplace(&TempArchivo,ListaWor,&ChangesList,&RevertList,arg2,arg1,true);
                    }
                    else{

                    }
                    clearWin(win);
                    mvwprintw(win,0,0,getText(&TempArchivo).c_str());
                    wrefresh(win);
                }
                break;
            //GUARDA UN CARACTER Y LO IMPRIME
            default:
                if(ch>=32 && ch<=126){
                    if(pointerList==TempArchivo.getSize()){
                        TempArchivo.addX((char)ch,pointerList);
                        //TempArchivo.addEnd((char)ch);
                    }
                    else{
                        TempArchivo.deleteXNode(pointerList);
                        TempArchivo.addX((char)ch,pointerList);
                    }
                    pointerList++;
                    wprintw(win,"%c",ch);
                    wrefresh(win);
                    getyx(win,posy,posx);
                }

                break;
        }

    }

}

//MANEJO DE INTERFAZ EN CONSOLA

void clearWin(WINDOW * win){
    werase(win);
    wrefresh(win);
}

string getText(DoubleLinkedCircularList<char> *Lista){
    string TempText="";
    for(int i =0;i<Lista->getSize();i++){
        TempText = TempText + Lista->getXNode(i);
    }
    return TempText;
}

void saveArchive(DoubleLinkedCircularList<char> *Lista, string NombreArchivo, bool Nuevo){

    ofstream file;
    if(Nuevo){
        file.open("./"+NombreArchivo+".txt",  fstream::in | fstream::out | fstream::trunc);
    }
    else{
        file.open(NombreArchivo,  fstream::in | fstream::out | fstream::trunc);
    }
    archivo++;
    file << getText(Lista);
    file.close();

}

void graphList (DoubleLinkedCircularList<char> *Lista){
    string command = "";
    ofstream file;
    file.open("./grafica"+to_string(archivo)+".dot",  fstream::in | fstream::out | fstream::trunc);
    file << "digraph {";
    file << "node [shape=box];"<<endl;
    file << "\"NULL\" [shape=plain];"<<endl;
    file << "\" " + to_string(0) +" : "+Lista->getXNode(0) +  " \" -> \"NULL\" [shape=plain] ;" <<endl;
    for(int i =0;i<Lista->getSize()-1;i++){
        file << "\" " + to_string(i) +" : "+Lista->getXNode(i) +  " \" -> " + "\" " + to_string(i+1) + " : " + Lista->getXNode(i+1) + " \" ;" <<endl;
        file << "\" " + to_string(i+1) +" : "+Lista->getXNode(i+1) +  " \" -> " + "\" " + to_string(i) + " : " + Lista->getXNode(i) + " \" ;" <<endl;
    }
    file << "\" " + to_string(Lista->getSize()-1) +" : "+Lista->getXNode(Lista->getSize()-1) +  " \" -> \"NULL.\" ;" <<endl;
    file << "}";
    file.close();
    command = "dot -Tpng ./grafica"+to_string(archivo)+".dot -o ImagenGrafica"+to_string(archivo)+".png >>/dev/null 2>>/dev/null";
    system(command.c_str());
    archivo++;
}

void showReportsMenu(WINDOW * win, DoubleLinkedCircularList<char> *Lista, int posy, int posx){
    //ENCABEZADO
    attron(A_REVERSE);
    move(0,2);
    printw("         Reportes:   1.Lista    2.Palabras Buscadas    3.Palabras Ordenadas      ");
    attroff(A_REVERSE);
    wrefresh(win);
    bool Control = true;

    while(Control){
        int ch = getch();

        switch(ch){
                //OPCION 1 -- Lista
            case 49:
                graphList(Lista);
                Control = false;
                break;
                //OPCION 2  -- Palabras Buscadas
            case 50:
                break;
                //OPCION 3 -- Palabras Ordenadas
            case 51:
                break;
                //OPCION 4 -- Salir Ctrl+X
            case 24:
                Control = false;
                break;
        }
    }

    attron(A_REVERSE);
    move(0,2);
    printw("             ^W(Buscar y Reemplazar)  ^C(Reportes)  ^S(GUARDAR)             ");
    attroff(A_REVERSE);

    wmove(win,posy,posx+1);
}

void showSearchAndReplace(WINDOW * win, DoubleLinkedCircularList<char> *ListaCh, DoubleLinkedCircularList<Word> *ListaWor, Stack<Change> *PilaCa){
    divideWords(ListaCh,ListaWor);
    //ENCABEZADO
    attron(A_REVERSE);
    move(0,2);
    printw("         Sintaxis<PalabraBuscar;PalabrasReemplazar:                               ");
    move(0,2);
    printw("         Sintaxis<PalabraBuscar;PalabrasReemplazar: ");

    wrefresh(win);
    bool Control = true;
    string params="";
    int changes=0;

    while(Control){
        int ch = getch();
        switch (ch){

            case 10: {
                attroff(A_REVERSE);
                string arg1 = params.substr(0, params.find(";"));
                string arg2 = params.substr(params.find(";") + 1, params.length() - 1);
                changes=searchAndReplace(ListaCh, ListaWor,PilaCa,NULL,arg1,arg2,true);
                Control = false;
                break;
            }
            case 24:
                clearWin(win);
                mvwprintw(win,0,0,"Hasta la proxima -- Presione una tecla para continuar...");
                wrefresh(win);
                getch();
                clearWin(win);
                showMenu(win);
                Control=false;
                break;
            default:
            //GUARDA EL CARACTER Y LO IMPRIME
                if(ch>32 && ch<=126) {
                    params.push_back(ch);
                    printw("%c", ch);
                    wrefresh(win);
                }
                break;
        }
    }

    attron(A_REVERSE);
    move(0,2);
    printw("             ^W(Buscar y Reemplazar)  ^C(Reportes)  ^S(GUARDAR)             ");
    attroff(A_REVERSE);
    clearWin(win);
    mvwprintw(win,0,0,"Se han realizado ");
    wprintw(win,to_string(changes).c_str());
    wprintw(win," cambios");
    mvwprintw(win,1,0,"Presione cualquier tecla para continuar");
    wrefresh(win);
    getch();
    clearWin(win);
    mvwprintw(win,0,0,getText(ListaCh).c_str());
    wrefresh(win);
}


//MANEJO DE DATOS

void divideWords(DoubleLinkedCircularList<char> *ListaCh , DoubleLinkedCircularList<Word> *ListaWor){

    Word *TempWord = new Word();
    string TempText="";
    int posB,posE;
    int ListLarge = ListaCh->getSize();

    for(int i =0;i<ListLarge;i++){

        if(ListaCh->getXNode(i) != 32){

            posB=i;
            for(int j = i ;j<ListLarge;j++){

                if(j==ListLarge-1 && ListaCh->getXNode(j) != 32){
                    posE = j;
                    i = j;
                    TempText.push_back(ListaCh->getXNode(j));
                    TempWord->setPosBegin(posB);
                    TempWord->setPosEnd(posE);
                    TempWord->setWord(TempText);
                    ListaWor->addEnd(*TempWord);
                    TempText="";
                    break;
                }
                else if(ListaCh->getXNode(j) == 32 ){
                    posE = j-1;
                    i = j-1;
                    TempWord->setPosBegin(posB);
                    TempWord->setPosEnd(posE);
                    TempWord->setWord(TempText);
                    ListaWor->addEnd(*TempWord);
                    TempText="";
                    break;
                }
                else{
                    TempText.push_back(ListaCh->getXNode(j));
                }
            }
        }
    }

    delete TempWord;

}

int searchAndReplace (DoubleLinkedCircularList<char> *ListaCh , DoubleLinkedCircularList<Word> *ListaWor, Stack<Change> *PilaCa, Stack<Change> *PilaCaR , string palabraBuscar , string palabraReemplazar, bool Tipo){
    divideWords(ListaCh,ListaWor);
    int ListaWordSize = ListaWor->getSize();
    int Changes=0;
    Change TempChange;

    for(int i =0;i<ListaWordSize;i++){

        if(ListaWor->getXNode(i).getWord() == palabraBuscar){

            int BeginWord=ListaWor->getXNode(i).getPosBegin();
            int EndWord=ListaWor->getXNode(i).getPosEnd();
            for(int j = BeginWord ; j<=EndWord ; j++){
                ListaCh->deleteXNode(BeginWord);
            }
            for(int j = 0 ; j<palabraReemplazar.length(); j++){
                ListaCh->addX(palabraReemplazar.at(j),BeginWord++);
            }
            Changes++;
        }
        //SE ACTUALIZA LISTA DE PALABRAS
        //delete ListaWor;
        ListaWor = new DoubleLinkedCircularList<Word>;
        divideWords(ListaCh,ListaWor);
        ListaWordSize = ListaWor->getSize();
    }

    if(Changes>0){
        if(PilaCaR==NULL){
            TempChange.setPalabraBuscar(palabraBuscar);
            TempChange.setpalabraReemplazar(palabraReemplazar);
            PilaCa->push(TempChange);
        }
        else {
            //REVERTIR CAMBIO Ctrl+Z
            if (Tipo) {
                TempChange=PilaCa->pop();
                PilaCaR->push(TempChange);
            }
                //REHACER CAMBIO Ctrl+Y
            else {
                TempChange=PilaCaR->pop();
                PilaCa->push(TempChange);
            }
        }
    }


    return Changes;

}


//FUNCIONES DE CURSOR

void moveBack(WINDOW * win,int posy,int posx){

    if(posx == 0 && posy != 0){
        wmove(win,posy-1,80);
    }
    else if(posx > 0 ){
        wmove(win,posy,posx-1);
    }

}

void moveFront(WINDOW * win,int posy,int posx){

    if(posx == 80 && posy != 25){
        wmove(win,posy+1,0);
    }
    else{
        wmove(win,posy,posx+1);
    }

}

void deleteChar(WINDOW * win, int posy, int posx, DoubleLinkedCircularList<char> *Lista){

    if((posx+(posy*80))<=Lista->getSize() && Lista->getSize()>0){
        if(posy>0){
            Lista->deleteXNode(posx+(posy*80)-1);
        }
        else{
            Lista->deleteXNode(posx-1);
        }
    }

}