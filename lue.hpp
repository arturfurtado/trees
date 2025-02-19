#include <iostream>
#include <string.h>
using namespace std;

template<typename T>
struct No{
    T info;
    No <T> *elo;
};

template<typename T>
struct LUE{
    No <T> *comeco;
    No <T> *fim;
};

template<typename T>
void inicializarLUE(LUE <T> &lista){
    lista.comeco = NULL;
    lista.fim = NULL;
}

template<typename T>
bool inserirFinalLUE( LUE <T> &lista, T valor ){
    No <T> *novo = new No <T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->elo = NULL;

    if( lista.comeco == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
    } else {
        lista.fim->elo = novo;
        lista.fim = novo;
    }
    return true;
}

template<typename T>
bool inserirLUE( LUE <T> &lista, T valor ){
    No <T> *novo = new No <T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->elo = NULL;

    if( lista.comeco == NULL ){ // Caso 1
        lista.comeco = novo;
        lista.fim = novo;
    }
    else if( lista.comeco->info > valor ){ // Caso 2
        novo->elo = lista.comeco;
        lista.comeco = novo;
    }
    else if( lista.fim->info < valor ){ // Caso 3
        lista.fim->elo = novo;
        lista.fim = novo;
    }
    else{// Caso 4
        No <T> *ant = lista.comeco;
        while( ant != NULL ){
            if( ant->info < valor && valor < ant->elo->info ){
                novo->elo = ant->elo;
                ant->elo = novo;
                break;
            }
            ant = ant->elo;
        }
    }
    return true;
}

template<typename T>
void mostrarLUE( LUE <T> lista ){
    No <T> *aux = lista.comeco;
    while( aux != NULL ){
        cout << aux->info << "  ";
        aux = aux->elo;
    }
}

template<typename T>
void liberarLUE(LUE <T> &lista){
    No <T> *aux = lista.comeco;
    No <T> *aux2;
    while( aux != NULL ){
        aux2 = aux;
        aux = aux->elo;
        delete aux2;
    }
}

template<typename T>
bool pesquisarLUE1(LUE <T> lista, T valor){
    No <T> *aux = lista.comeco;
    while( aux != NULL ){
        if( valor == aux->info ) return true;
        aux = aux->elo;
    }
    return false;
}

template<typename T>
No <T> * pesquisarLUE2(LUE <T> lista, T valor){
    No <T> *aux = lista.comeco;
    while( aux != NULL ){
        if( valor == aux->info ) return aux;
        aux = aux->elo;
    }
    return NULL;
}

template<typename T>
bool retirarLUE(LUE <T> &lista, T valor ){
    if( lista.comeco == NULL ) return false;
    No <T> *aux;

    if( lista.comeco->info == valor ){

        aux = lista.comeco;
        lista.comeco = aux->elo; // Caso 1 e 2
        if( lista.fim == aux ) lista.fim = NULL; // Caso 1

    } else { // Caso 3 ou 4
        No <T> *ant;
        aux = lista.comeco;
        while( aux != NULL ){
            if( aux->info == valor ) break;
            ant = aux;
            aux = aux->elo;
        }
        if( aux == NULL ) return false; // Valor não localizado
        ant->elo = aux->elo;  // Caso 3 e 4
        if( aux == lista.fim ) lista.fim = ant; // Caso 3
    }
    delete aux;
    return true;
}

