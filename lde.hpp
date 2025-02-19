#include <iostream>
using namespace std;

template<typename T>
struct No{
    T info;
    No <T> *eloA, *eloP;
};

template<typename T>
struct LDE{
    No <T> *comeco;
    No <T> *fim;
};

template<typename T>
void inicializarLDE(LDE <T> &lista){
    lista.comeco = NULL;
    lista.fim = NULL;
}

template<typename T>
bool inserirFinalLDE( LDE <T> &lista, T valor ){
    No <T> *novo = new No <T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->eloA = NULL;
    novo->eloP = NULL;

    if( lista.comeco == NULL ){ // Lista Vazia
        lista.comeco = novo;
        lista.fim = novo;
    } else {
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
    }
    return true;
}

template<typename T>
bool inserirLDE( LDE <T> &lista, T valor ){
    No <T> *novo = new No <T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->eloA = NULL;
    novo->eloP = NULL;

    if( lista.comeco == NULL ){ // Caso a
        lista.comeco = novo;
        lista.fim = novo;
    }
    else if( valor < lista.comeco->info ){ // Caso b
        novo->eloP = lista.comeco;
        lista.comeco->eloA = novo;
        lista.comeco = novo;
    }
    else if( valor > lista.fim->info ){ // Caso c
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
    }
    else{ // Caso d
        No <T> *ant = lista.comeco;
        while( ant != NULL ){
            if( ant->info < valor && valor < ant->eloP->info ){
                novo->eloP = ant->eloP;
                novo->eloA = ant;
                ant->eloP->eloA = novo;
                ant->eloP = novo;
                break;
            }
            ant = ant->eloP;
        }
    }
    return true;
}



template<typename T>
void mostrarLDE( LDE <T> lista, char ordem ){
    No <T> *aux = (ordem=='C') ? lista.comeco : lista.fim;
    while( aux != NULL ){
        cout << aux->info << "  ";
        aux = (ordem=='C') ? aux->eloP : aux->eloA;
        /* if( ordem == 'C' )
               aux = aux->eloP;
           else
               aux = aux->eloA;
        */
    }
}

template<typename T>
void liberarLDE(LDE <T> &lista){
    No <T> *aux = lista.comeco;
    No <T> *aux2;
    while( aux != NULL ){
        aux2 = aux;
        aux = aux->eloP;
        delete aux2;
    }
}

template<typename T>
No <T> * pesquisarLDE(LDE <T> &lista, T valor){
    No <T> *aux = lista.comeco;
    while( aux != NULL ){
        if( valor == aux->info ) return aux;
        aux = aux->eloP;
    }
    return NULL;
}

template <typename T>
bool retirarLDE( LDE <T> &lista, T valor ){
    No <T> *aux = pesquisarLDE(lista, valor);
    if( aux == NULL ) return false; // Não localizou valor

    if( aux == lista.comeco ){
        if( aux == lista.fim ){ // Caso a
            lista.comeco = NULL;
            lista.fim = NULL;
        } else {  // Caso b
            lista.comeco = aux->eloP;
            lista.comeco->eloA = NULL;
        }
    }
    else if( aux == lista.fim ){ // Caso c
        lista.fim = aux->eloA;
        lista.fim->eloP = NULL;
    }
    else{ // Caso d
        No <T> *ant = aux->eloA;
        No <T> *prox = aux->eloP;
        ant->eloP = prox;
        prox->eloA = ant;
    }
    delete aux;
    return true;
}

