#include <iostream>
#include "abb.hpp"
using namespace std;

template <typename T>
void infixado_vetor(No <T> *raiz, T vetor[], int &pos ){
    if( raiz == NULL ) return;
    infixado_vetor(raiz->esq, vetor, pos);
    vetor[pos++] = raiz->info;
    infixado_vetor(raiz->dir, vetor, pos);
}

template <typename T>
bool testar_vetor(T vetorA[], T vetorB[], int tam){
    for( int i=0; i<tam-1; i++ ){
        if( vetorA[i] != vetorB[i] ) return false;
    }
    return true;
}

template <typename T>
bool iguais(No <T> *raizA, No <T> *raizB ){
    int tamA = contar(raizA);
    int tamB = contar(raizB);
    if( tamA != tamB ) return false;

    T *vA = new T[tamA];
    T *vB = new T[tamB];
    int pos = 0;
    infixado_vetor(raizA, vA, pos);
    pos = 0;
    infixado_vetor(raizB, vB, pos);

    return testar_vetor(vA, vB, tamA);
}

template <typename T>
bool estritamente_iguais(No <T> *raizA, No <T> *raizB ){
    if( (raizA == NULL && raizB != NULL) || (raizA != NULL && raizB == NULL) )
        return false;
    if( raizA == NULL && raizB == NULL ) return true;

    if( raizA->info != raizB->info ) return false;

    return estritamente_iguais(raizA->esq, raizB->esq ) &&
           estritamente_iguais(raizA->dir, raizB->dir );
}

int main(){
    No <int> *raizA=NULL, *raizB = NULL;
    int opcao, valor;

    do{
        cout << endl << endl << "Exercicio 05:";
        cout << endl << "\t1 - Inserir em A";
        cout << endl << "\t2 - Inserir em B";
        cout << endl << "\t3 - Testar iguais";
        cout << endl << "\t4 - Testar estritamente iguais";
        cout << endl << "\t0 - Fim";
        cout << endl << "Opcao: ";
        cin >> opcao;

        switch(opcao){
            case 0: // Sair
                break;
            case 1: // Inserir em A
                cout << endl << "Valor a inserir: ";
                cin >> valor;
                if( inserirABB(raizA, valor) )
                    cout << "Valor inserido com sucesso!";
                else
                    cout << "Erro na insercao";
                break;
            case 2: // Inserir em A
                cout << endl << "Valor a inserir: ";
                cin >> valor;
                if( inserirABB(raizB, valor) )
                    cout << "Valor inserido com sucesso!";
                else
                    cout << "Erro na insercao";
                break;
            case 3:
                if( iguais( raizA, raizB ) )
                    cout << "As duas arvores tem o mesmo conteudo" << endl;
                else
                    cout << "As duas arvores NAO tem o mesmo conteudo" << endl;
                break;
            case 4:
                if( estritamente_iguais( raizA, raizB ) )
                    cout << "As duas arvores tem o mesmo conteudo na mesma posicao" << endl;
                else
                    cout << "As duas arvores sao diferentes" << endl;
                break;
            default:
                cout << endl << "Erro, opcao invalida!";
        }
    }while( opcao != 0 );

    liberarABB(raizA);
    liberarABB(raizB);
    cout << endl;
}
