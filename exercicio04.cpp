#include <iostream>
#include "abb.hpp"
using namespace std;

template <typename T>
int altura(No <T> *raiz){
    if( raiz == NULL ) return 0;
    int aE = altura(raiz->esq);
    int aD = altura(raiz->dir);
    return (aE > aD) ? aE+1 : aD+1;
}

int main(){
    No <int> *raiz=NULL;
    int opcao, valor, a, b;

    do{
        cout << endl << endl << "Exercicio 04:";
        cout << endl << "\t1 - Inserir";
        cout << endl << "\t2 - Altura";
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
                cout << endl << "Altura: " << altura(raiz);
                cout << endl;
                break;
            default:
                cout << endl << "Erro, opcao invalida!";
        }
    }while( opcao != 0 );

    liberarABB(raiz);
    cout << endl;
}
