#include <iostream>
#include "DoubleLinkedList.h"
#include "LinkedCircularList.h"
#include "Stack.h"
#include "Word.h"
#include <curses.h>
#include <clocale>
#include <fstream>
#include <string>
#include "Change.h"
#include "Archive.h"
#include "LinkedList.h"
#include <math.h>


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
void deleteChar(WINDOW * win, int posy, int posx, DoubleLinkedList<char> *Lista);

//DEVUELVE EL TEXTO EN LA LISTA
string getText(DoubleLinkedList<char> *Lista);

//GUARDA EL ARCHIVO
void saveArchive(DoubleLinkedList<char> *Lista, string NombreArchivo, bool Nuevo);

//MENU DE REPORTES
void showReportsMenu(WINDOW * win, DoubleLinkedList<char> *Lista, Stack<Change> *PilaCa, Stack<Change> *PilaCaR, int posy, int posx);

// GRAFICA LA LISTA
void graphList (DoubleLinkedList<char> *Lista);

//DIVIDE LA LISTA DE CARACTERES EN UNA LISTA DE PALABRAS
void divideWords(DoubleLinkedList<char> *ListaCh , DoubleLinkedList<Word> *ListaWor);

// BUSCA Y REEMPLAZA EN BASE A PALABRAS ACTUALIZA LISTA DE CARACTERES
int searchAndReplace (DoubleLinkedList<char> *ListaCh , DoubleLinkedList<Word> *ListaWor, Stack<Change> *PilaCa , Stack<Change> *PilaCaR, string palabraBuscar , string palabraReemplazar, bool Tipo);

//PIDE PARAMETROS AL USUARIO Y LOS MUESTRA EN PANTALLA
void showSearchAndReplace(WINDOW * win, DoubleLinkedList<char> *ListaCh, DoubleLinkedList<Word> *ListaWor, Stack<Change> *PilaCa);

//MUESTRA MENU DE ARCHIVOS RECIENTES
void showRecentArchives(WINDOW * win, LinkedCircularList<Archive> *ListaArchivos);

//GRAFICA LA PILA DE CAMBIOS Y LA DE CAMBIOS REVERTIDOS
void graphStacks(Stack<Change> PilaCa, Stack<Change> PilaCaR);

//GRAFICA LISTA DE ARCHIVOS
void graphArchives(LinkedCircularList<Archive> *ListaArchivos);

//ORDENA Y GRAFICA DE PILA DE CAMBIOS EN ORDEN ALFABETICO
void binarySort (Stack<Change> PilaCa,Stack<Change> PilaCa2);

// VARIABLES GLOBALES

//CARACTERES
int reporte1=0;
// PILAS
int reporte2=0;
//ARCHIVOS
int reporte3=0;
//LISTA ORDENADA
int reporte4=0;

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
    LinkedCircularList<Archive> ArchivosRecientes;
    Archive TempArchivo;
    string Ruta="";
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
                while (option2Control) {
                    ch=getch();
                    if (ch >= 32 && ch <= 126) {
                        Ruta.push_back(ch);
                        wprintw(win,"%c", ch);
                        wrefresh(win);
                    }
                    if (ch == 10) {
                        string aux=Ruta;
                        //SE VERIFICA QUE EL FICHERO EXISTA
                        ifstream fichero;
                        fichero.open(Ruta);
                        if(!fichero.fail()) {

                            for (int i = 0; i < aux.length(); i++) {
                                aux = aux.substr(aux.find("/") + 1, aux.length() - 1);
                                i = aux.find("/") + 1;
                                if (aux.find("/") == string::npos) {
                                    break;
                                }
                            }
                            TempArchivo.setRuta(Ruta);
                            TempArchivo.setNombre(aux);
                            ArchivosRecientes.addEnd(TempArchivo);
                            fichero.close();
                            newArchive(win,Ruta);
                            option2Control = false;
                        }
                        else{
                            clearWin(win);
                            showMenu(win);
                            mvwprintw(win, 20, 6, "NO EXISTE ARCHIVO EN LA RUTA INDICADA");
                            mvwprintw(win, 18, 6, "Escriba Ruta de Archivo: ");
                            wrefresh(win);
                        }
                        Ruta="";
                    }
                }
            }
                break;
                //OPCION 3 -- Archivos Recientes
            case 51:
                showRecentArchives(win,&ArchivosRecientes);
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

    DoubleLinkedList<char> TempArchivo;
    Stack<Change> *ChangesList = new Stack<Change>;
    Stack<Change> *RevertList = new Stack<Change>;
    DoubleLinkedList<Word> *ListaWor = new DoubleLinkedList<Word>;

    //UBICACION DE CURSOR
    int posx = 0;
    int posy = 0;
    int pointerList=0;
    int ch;
    bool Control = true;
    Change TempChange;

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

        fichero.get(letra);
        while(!fichero.eof()){
            if(letra>=32 && letra<=126){
                TempArchivo.addEnd((char)letra);
                pointerList++;
                wprintw(win,"%c",letra);
                wrefresh(win);
                getyx(win,posy,posx);
            }
            fichero.get(letra);
        }
        fichero.close();

    }


    while(Control){
        ch = getch();

        switch (ch){
            //BUSCAR Y REEMPLAZAR ^W
            case 23:
                if(ChangesList->getSize()>0){
                    if(ChangesList->pick().getPalabraReemplazar()==""){
                        ChangesList->clearStack();
                    }
                }
                if(RevertList->getSize()>0){
                    if(RevertList->pick().getPalabraReemplazar()==""){
                        RevertList->clearStack();
                    }
                }
                showSearchAndReplace(win,&TempArchivo,ListaWor,ChangesList);
                pointerList=TempArchivo.getSize();
                getyx(win,posy,posx);
                break;
            // REPORTES ^C
            case 3: {
                showReportsMenu(win, &TempArchivo, ChangesList, RevertList, posy, posx);
            }
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
            // SALIR ^X
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
                if(ChangesList->getSize()>0){
                    if(ChangesList->pick().getPalabraReemplazar()!=""){
                        ChangesList->clearStack();
                        RevertList->clearStack();
                    }
                }

                if(pointerList>0){

                    pointerList--;
                    //TempChange.setChar(TempArchivo.getXNode(pointerList));
                    //TempChange.setPointerList(pointerList);
                    //TempChange.setTipo(false);
                    //ChangesList->push(TempChange);
                    ChangesList->clearStack();
                    RevertList->clearStack();

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
                if(RevertList->getSize()>0){
                    if(RevertList->pick().getPalabraReemplazar()!=""){
                        string arg1=RevertList->pick().getPalabraBuscar();
                        string arg2=RevertList->pick().getPalabraReemplazar();
                        searchAndReplace(&TempArchivo,ListaWor,ChangesList,RevertList,arg1,arg2,false);
                    }
                    else{
                        if(RevertList->pick().getTipo()){
                            TempArchivo.addX(RevertList->pick().getChar(),RevertList->pick().getPointerList());
                            pointerList++;
                        }
                        else{
                            TempArchivo.deleteXNode(RevertList->pick().getPointerList());
                            pointerList--;
                        }
                        ChangesList->push(RevertList->pop());
                    }
                }
                clearWin(win);
                mvwprintw(win,0,0,getText(&TempArchivo).c_str());
                wrefresh(win);
                break;
            // Ctrl+Z
            case 26:
                if(ChangesList->getSize()>0){
                    if(ChangesList->pick().getPalabraReemplazar()!=""){
                        string arg1=ChangesList->pick().getPalabraBuscar();
                        string arg2=ChangesList->pick().getPalabraReemplazar();
                        searchAndReplace(&TempArchivo,ListaWor,ChangesList,RevertList,arg2,arg1,true);
                    }
                    else{

                        if(ChangesList->pick().getTipo()){
                            TempArchivo.deleteXNode(ChangesList->pick().getPointerList());
                            pointerList--;
                        }
                        else{
                            TempArchivo.addX(ChangesList->pick().getChar(),ChangesList->pick().getPointerList());
                            pointerList++;
                        }
                        RevertList->push(ChangesList->pop());
                    }
                    clearWin(win);
                    mvwprintw(win,0,0,getText(&TempArchivo).c_str());
                    wrefresh(win);
                }
                break;
            //GUARDA UN CARACTER Y LO IMPRIME
            default:
                if(ch>=32 && ch<=126){

                    if(ChangesList->getSize()>0){
                        if(ChangesList->pick().getPalabraReemplazar()!=""){
                            ChangesList->clearStack();
                            RevertList->clearStack();
                        }
                    }
                    if(pointerList==TempArchivo.getSize()){
                        TempArchivo.addX((char)ch,pointerList);
                        TempChange.setChar((char)ch);
                        TempChange.setPointerList(pointerList);
                        TempChange.setTipo(true);
                        ChangesList->push(TempChange);
                        RevertList->clearStack();
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

void showRecentArchives(WINDOW * win, LinkedCircularList<Archive> *ListaArchivos){

    clearWin(win);
    mvwprintw(win,2,5,"ARCHIVOS RECIENTES");
    for(int i=0; i<ListaArchivos->getSize();i++){
        Archive TempArchivo = ListaArchivos->getXNode(i);
        mvwprintw(win,i+5,5,to_string(i).c_str());
        wprintw(win,". ");
        wprintw(win,TempArchivo.getNombre().c_str());
        wprintw(win,"        ");
        wprintw(win,TempArchivo.getRuta().c_str());
    }
    mvwprintw(win,20,5,"INTRODUCZA EL NUMERO DE ARCHIVO PARA ABRIR: ");
    wrefresh(win);

    int ch;
    bool Control=true;
    string numArchivo;

    while(Control){
        ch= getch();
        if (ch >= 48 && ch <= 57) {
            numArchivo.push_back(ch);
            wprintw(win,"%c", ch);
            wrefresh(win);
        }
        if (ch == 10) {
            if(stoi(numArchivo)<ListaArchivos->getSize()){
                newArchive(win,ListaArchivos->getXNode(stoi(numArchivo)).getRuta());
                Control=false;
            }
            else{

            }
        }
        if(ch==24){
            graphArchives(ListaArchivos);
        }
    }


}

//MANEJO DE INTERFAZ EN CONSOLA

void clearWin(WINDOW * win){
    werase(win);
    wrefresh(win);
}

string getText(DoubleLinkedList<char> *Lista){
    string TempText="";
    for(int i =0;i<Lista->getSize();i++){
        TempText = TempText + Lista->getXNode(i);
    }
    return TempText;
}

void showReportsMenu(WINDOW * win, DoubleLinkedList<char> *Lista, Stack<Change> *PilaCa, Stack<Change> *PilaCaR, int posy, int posx){
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
            case 50: {
                graphStacks(*PilaCa,*PilaCaR);
                Control = false;
            }
                break;
                //OPCION 3 -- Palabras Ordenadas
            case 51:
            {
                if(PilaCa->pick().getPalabraBuscar()!=""){
                    binarySort(*PilaCa,*PilaCa);
                }
                Control=false;
            }
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

    wmove(win,posy,posx);
}

void showSearchAndReplace(WINDOW * win, DoubleLinkedList<char> *ListaCh, DoubleLinkedList<Word> *ListaWor, Stack<Change> *PilaCa){
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

void divideWords(DoubleLinkedList<char> *ListaCh , DoubleLinkedList<Word> *ListaWor){

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

int searchAndReplace (DoubleLinkedList<char> *ListaCh , DoubleLinkedList<Word> *ListaWor, Stack<Change> *PilaCa, Stack<Change> *PilaCaR , string palabraBuscar , string palabraReemplazar, bool Tipo){
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
        ListaWor = new DoubleLinkedList<Word>;
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
                TempChange.setEstado(true);
                PilaCaR->push(TempChange);
            }
                //REHACER CAMBIO Ctrl+Y
            else {
                TempChange=PilaCaR->pop();
                TempChange.setEstado(false);
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

void graphList (DoubleLinkedList<char> *Lista){
    string command = "";
    ofstream file;
    file.open("./grafica" + to_string(reporte1) + ".dot", fstream::in | fstream::out | fstream::trunc);
    file << "digraph {";
    file << "node [shape=box];"<<endl;
    file << "rankdir=LR;"<<endl;
    file << "\"NULL\" [shape=plain];"<<endl;
    file << "\" " + to_string(0) +" : "+Lista->getXNode(0) +  " \" -> \"NULL\" [shape=plain] ;" <<endl;
    for(int i =0;i<Lista->getSize()-1;i++){
        file << "\" " + to_string(i) +" : "+Lista->getXNode(i) +  " \" -> " + "\" " + to_string(i+1) + " : " + Lista->getXNode(i+1) + " \" ;" <<endl;
        file << "\" " + to_string(i+1) +" : "+Lista->getXNode(i+1) +  " \" -> " + "\" " + to_string(i) + " : " + Lista->getXNode(i) + " \" ;" <<endl;
    }
    file << "\" " + to_string(Lista->getSize()-1) +" : "+Lista->getXNode(Lista->getSize()-1) +  " \" -> \"NULL.\" ;" <<endl;
    file << "}";
    file.close();
    command = "dot -Tpng ./grafica" + to_string(reporte1) + ".dot -o ImagenGrafica" + to_string(reporte1) + ".png >>/dev/null 2>>/dev/null";
    system(command.c_str());
    reporte1++;
}

void saveArchive(DoubleLinkedList<char> *Lista, string NombreArchivo, bool Nuevo){

    ofstream file;
    if(Nuevo){
        file.open("./"+NombreArchivo+".txt",  fstream::in | fstream::out | fstream::trunc);
    }
    else{
        file.open(NombreArchivo,  fstream::in | fstream::out | fstream::trunc);
    }
    reporte1++;
    file << getText(Lista);
    file.close();

}

void graphStacks(Stack<Change> PilaCa, Stack<Change> PilaCaR){
    string command = "";
    string aux = "";
    ofstream file;
    int PilaSize;
    Change TempCambio;

    // PARA LA PILA DE CAMBIOS
    PilaSize=PilaCa.getSize();
    if(PilaSize>0){
        file.open("./PilaCambios" + to_string(reporte2) + ".dot", fstream::in | fstream::out | fstream::trunc);
        file << "digraph {";
        file << "node [shape=box];"<<endl;
        file << "rankdir=RL;"<<endl;
        for(int i =0;i<PilaSize;i++){
            TempCambio = PilaCa.pick();
            file<< "\" Palabra Buscada : "+TempCambio.getPalabraBuscar()<<endl;
            file<< " Palabra Reemplazada : "+TempCambio.getPalabraReemplazar()<<endl;
            file<< " Estado : No Revertido  "<<endl;
            if(TempCambio.getPalabraBuscar()!=""){
                file<< " Caracter : null"<<endl;
                file<< " Posicion : null"<<endl;
            }
            else{
                aux= " Caracter : ";
                aux.push_back(TempCambio.getChar());
                file<< aux <<endl;
                file<< " Posicion : "+to_string(TempCambio.getPointerList())<<endl;
            }
            file<<"\""<<endl;
            file<<"->"<<endl;
            PilaCa.pop();
        }
        file<<"\"PILA DE CAMBIOS\";";
        file << "}";
        file.close();
        command = "dot -Tpng ./PilaCambios" + to_string(reporte2) + ".dot -o PilaCambios" + to_string(reporte2) + ".png >>/dev/null 2>>/dev/null";
        system(command.c_str());
    }

    // PARA LA PILA DE REVERTIDOS
    PilaSize=PilaCaR.getSize();
    if(PilaSize>0){
        file.open("./PilaRevertidos" + to_string(reporte2) + ".dot", fstream::in | fstream::out | fstream::trunc);
        file << "digraph {";
        file << "node [shape=box];"<<endl;
        file << "rankdir=RL;"<<endl;
        for(int i =0;i<PilaSize;i++){
            TempCambio = PilaCaR.pick();
            file<< "\" Palabra Buscada : "+TempCambio.getPalabraBuscar()<<endl;
            file<< " Palabra Reemplazada : "+TempCambio.getPalabraReemplazar()<<endl;
            file<< " Estado : No Revertido  "<<endl;
            if(TempCambio.getPalabraBuscar()!=""){
                file<< " Caracter : null"<<endl;
                file<< " Posicion : null"<<endl;
            }
            else{
                aux= " Caracter : ";
                aux.push_back(TempCambio.getChar());
                file<< aux <<endl;
                file<< " Posicion : "+to_string(TempCambio.getPointerList())<<endl;
            }
            file<<"\""<<endl;
            file<<"->"<<endl;
            PilaCaR.pop();
        }
        file<<"\"PILA DE CAMBIOS\";";
        file << "}";
        file.close();
        command = "dot -Tpng ./PilaRevertidos" + to_string(reporte2) + ".dot -o PilaRevertidos" + to_string(reporte2) + ".png >>/dev/null 2>>/dev/null";
        system(command.c_str());
    }

    reporte2++;
}

void graphArchives(LinkedCircularList<Archive> *ListaArchivos){
    string command = "";
    string aux = "";
    ofstream file;
    int ListaSize;
    Archive TempArchivo;

    // PARA LA PILA DE CAMBIOS
    ListaSize=ListaArchivos->getSize();
    if(ListaSize>0){
        file.open("./Archivos" + to_string(reporte3) + ".dot", fstream::in | fstream::out | fstream::trunc);
        file << "digraph {";
        file << "node [shape=box];"<<endl;
        file << "rankdir=RL;"<<endl;
        for(int i =0;i<ListaSize;i++){
            TempArchivo = ListaArchivos->getXNode(i);
            file<< "\" Nombre de Archivo : "+TempArchivo.getNombre()<<endl;
            file<< " Ruta : "+TempArchivo.getRuta()<<endl;
            file<<"\""<<endl;
            file<<"->"<<endl;
        }
        TempArchivo = ListaArchivos->getFirst();
        file<< "\" Nombre de Archivo : "+TempArchivo.getNombre()<<endl;
        file<< " Ruta : "+TempArchivo.getRuta()<<endl;
        file<<"\""<<endl;
        }

        file << "}";
        file.close();
        command = "dot -Tpng ./Archivos" + to_string(reporte3) + ".dot -o Archivos" + to_string(reporte3) + ".png >>/dev/null 2>>/dev/null";
        system(command.c_str());

        reporte3++;
}

void binarySort (Stack<Change> PilaCa,Stack<Change> PilaCa2){
    LinkedList<Change> *ListaCambios = new LinkedList<Change>;
    int pivote,primero,ultimo;
    int StackSize;
    Change TempChange;
    string TempString,PivoteString;

    ListaCambios->addBegin(PilaCa.pop());

    StackSize=PilaCa.getSize();
    for(int i = 0 ; i<StackSize ; i++){
        primero=0;
        ultimo=ListaCambios->getSize()-1;
        TempChange=PilaCa.pop();
        TempString=TempChange.getPalabraBuscar();
        while(primero<=ultimo){
            pivote = floor((primero+ultimo)/2);
            PivoteString = ListaCambios->getXNode(pivote).getPalabraBuscar();

            if(TempString.compare(PivoteString)<0){
                ultimo = pivote-1;
            }
            else{
                primero=pivote+1;
            }
        }

        ListaCambios->addX(TempChange,primero);
    }


    string command = "";
    ofstream file;
    file.open("./Buscadas" + to_string(reporte4) + ".dot", fstream::in | fstream::out | fstream::trunc);
    file << "digraph {";
    file << "node [shape=box];"<<endl;
    file << "rankdir=LR;"<<endl;
    for(int i =0;i<ListaCambios->getSize();i++){
        TempChange = ListaCambios->getXNode(i);
        file << "\" "<<endl;
        file << TempChange.getPalabraBuscar()<<endl;
        file << "Reemplazada por : ";
        file << TempChange.getPalabraReemplazar()<<endl;
        file << "\" "<<endl;
        file << "->"<<endl;
    }
    file << "\"FIN\""<<endl;
    file << "}";
    file.close();
    command = "dot -Tpng ./Buscadas" + to_string(reporte4) + ".dot -o BuscadasImagen" + to_string(reporte4) + ".png >>/dev/null 2>>/dev/null";
    system(command.c_str());


    //SEGUNDA GRAFICA
    delete ListaCambios;
    ListaCambios = new LinkedList<Change>;

    ListaCambios->addBegin(PilaCa2.pop());

    StackSize=PilaCa2.getSize();
    for(int i = 0 ; i<StackSize ; i++){
        primero=0;
        ultimo=ListaCambios->getSize()-1;
        TempChange=PilaCa2.pop();
        TempString=TempChange.getPalabraReemplazar();
        while(primero<=ultimo){
            pivote = floor((primero+ultimo)/2);
            PivoteString = ListaCambios->getXNode(pivote).getPalabraReemplazar();

            if(TempString.compare(PivoteString)<0){
                ultimo = pivote-1;
            }
            else{
                primero=pivote+1;
            }
        }

        ListaCambios->addX(TempChange,primero);
    }


    command = "";
    file.open("./Reemplazos" + to_string(reporte4) + ".dot", fstream::in | fstream::out | fstream::trunc);
    file << "digraph {";
    file << "node [shape=box];"<<endl;
    file << "rankdir=LR;"<<endl;
    for(int i =0;i<ListaCambios->getSize();i++){
        TempChange = ListaCambios->getXNode(i);
        file << "\" "<<endl;
        file << TempChange.getPalabraReemplazar()<<endl;
        file << "Reemplazo a : ";
        file << TempChange.getPalabraBuscar()<<endl;
        file << "\" "<<endl;
        file << "->"<<endl;
    }
    file << "\"FIN\""<<endl;
    file << "}";
    file.close();
    command = "dot -Tpng ./Reemplazos" + to_string(reporte4) + ".dot -o ReemplazosImagen" + to_string(reporte4) + ".png >>/dev/null 2>>/dev/null";
    system(command.c_str());
    reporte4++;




}

void deleteChar(WINDOW * win, int posy, int posx, DoubleLinkedList<char> *Lista){

    if((posx+(posy*80))<=Lista->getSize() && Lista->getSize()>0){
        if(posy>0){
            Lista->deleteXNode(posx+(posy*80)-1);
        }
        else{
            Lista->deleteXNode(posx-1);
        }
    }

}