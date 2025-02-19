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
bool testar_vetor(T vetor[], int tam){
    for( int i=0; i<tam-1; i++ ){
        if( vetor[i] > vetor[i+1] ) return false;
    }
    return true;
}

template <typename T>
bool testar_abb( No <T> *raiz ){
    int cont = contar(raiz);
    T *vetor = new T[cont];
    int pos=0;
    infixado_vetor(raiz, vetor, pos );
    return testar_vetor(vetor, cont);
}

int main(){

    No <int> *raiz1, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8;

    /*
    raiz1 = new No<int>; raiz1->info = 50;
    n1 = new No <int>; n1->info = 30;
    n2 = new No <int>; n2->info = 20;
    n3 = new No <int>; n3->info = 60;
    n4 = new No <int>; n4->info = 70;
    n5 = new No <int>; n5->info = 40;
    n6 = new No <int>; n6->info = 80;
    raiz1->esq = n1;
    raiz1->dir = n4;
    n1->esq = n2;
    n1->dir = n3;
    n4->esq = n5;
    n4->dir = n6;
*/
    raiz1 = new No <int>; raiz1->info = 2;
    n1 = new No <int>; n1->info = 7;
    n2 = new No <int>; n2->info = 5;
    n3 = new No <int>; n3->info = 3;
    n4 = new No <int>; n4->info = 6;
    n5 = new No <int>; n5->info = 9;
    n6 = new No <int>; n6->info = 5;
    n7 = new No <int>; n7->info = 11;
    n8 = new No <int>; n8->info = 4;
    raiz1->esq = n1;
    raiz1->dir = n2;
    n1->esq = n3;
    n1->dir = n4;
    n2->dir = n5;
    n4->esq = n6;
    n4->dir = n7;
    n5->esq = n8;


    No <int> *raiz2 = NULL;

    inserirABB(raiz2, 20);
    inserirABB(raiz2, 10);
    inserirABB(raiz2, 40);
    inserirABB(raiz2, 30);
    inserirABB(raiz2, 50);

    if( testar_abb(raiz1) )
        cout << endl << "A arvore 1 eh ABB" << endl;
    else
        cout << endl << "A arvore 1 nao eh ABB" << endl;
    if( testar_abb(raiz2) )
        cout << endl << "A arvore 2 eh ABB" << endl;
    else
        cout << endl << "A arvore 2 nao eh ABB" << endl;

    liberarABB(raiz1);
    liberarABB(raiz2);
}
