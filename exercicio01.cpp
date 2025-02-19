#include <iostream>
#include "abb.hpp"
using namespace std;

template <typename T>
void contar_nos_folha(No <T> *raiz, int &cont){
    if( raiz == NULL ) return;
    if( raiz->esq == NULL && raiz->dir == NULL )
        cont++;
    else{
        contar_nos_folha(raiz->esq, cont);
        contar_nos_folha(raiz->dir, cont);
    }
}

template <typename T>
int contar_nos_folha(No <T> *raiz){
    if( raiz == NULL ) return 0;
    if( raiz->esq == NULL && raiz->dir == NULL ) return 1;
    else
        return contar_nos_folha(raiz->esq) + contar_nos_folha(raiz->dir);
}

int main(){
    No <int> *raiz=NULL;
    int opcao, valor, cont;

    do{
        cout << endl << endl << "Exercicio 01:";
        cout << endl << "\t1 - Inserir";
        cout << endl << "\t2 - Numero de nos folha (parametro)";
        cout << endl << "\t3 - Numero de nos folha";
        cout << endl << "\t0 - Fim";
        cout << endl << "Opcao: ";
        cin >> opcao;

        switch(opcao){
            case 0: // Sair
                break;
            case 1: // Inserir
                cout << endl << "Valor a inserir: ";
                cin >> valor;
                if( inserirABB(raiz, valor) )
                    cout << "Valor inserido com sucesso!";
                else
                    cout << "Erro na insercao";
                break;
            case 2: // contar com parametro
                cout << endl << "Numero de nos folha: ";
                cont = 0;
                contar_nos_folha(raiz, cont);
                cout << cont << endl;
                break;
            case 3: // contar com return
                cout << endl << "Numero de nos folha: ";
                cout << contar_nos_folha(raiz) << endl;
                break;
            default:
                cout << endl << "Erro, opcao invalida!";
        }
    }while( opcao != 0 );

    liberarABB(raiz);
    cout << endl;
}
