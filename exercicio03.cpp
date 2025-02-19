#include <iostream>
#include "abb.hpp"
using namespace std;

template <typename T>
void listar(No <T> *raiz, int a, int b){
    if( raiz == NULL ) return;
    listar(raiz->esq, a, b);
    if( a <= raiz->info && raiz->info <= b ) cout << raiz->info << " ";
    listar(raiz->dir, a, b);
}

int main(){
    No <int> *raiz=NULL;
    int opcao, valor, a, b;

    do{
        cout << endl << endl << "Exercicio 03:";
        cout << endl << "\t1 - Inserir";
        cout << endl << "\t2 - Listar entre dois valores";
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
                cout << endl << "Valor inicial do intervalo: ";
                cin >> a;
                cout << "Valor final do intervalo: ";
                cin >> b;
                cout << endl << "Arvore [" << a << ";" << b << "] => ";
                listar(raiz, a, b);
                cout << endl;
                break;
            default:
                cout << endl << "Erro, opcao invalida!";
        }
    }while( opcao != 0 );

    liberarABB(raiz);
    cout << endl;
}
