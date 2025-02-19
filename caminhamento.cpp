#include <iostream>
using namespace std;

struct No{
    char info;
    No *esq=NULL, *dir=NULL;
};

void prefixado(No *raiz){
    if( raiz == NULL ) return;
    cout << raiz->info << " ";
    prefixado(raiz->esq);
    prefixado(raiz->dir);
}

void infixado(No *raiz){
    if( raiz == NULL ) return;
    infixado(raiz->esq);
    cout << raiz->info << " ";
    infixado(raiz->dir);
}

void posfixado(No *raiz){
    if( raiz == NULL ) return;
    posfixado(raiz->esq);
    posfixado(raiz->dir);
    cout << raiz->info << " ";
}

int contarA(No *raiz){
    if( raiz == NULL ) return 0;
    return 1 + contarA(raiz->esq) + contarA(raiz->dir);
}

int contarB(No *raiz){
    return (raiz == NULL) ? 0 : 1 + contarA(raiz->esq) + contarA(raiz->dir);
}

void contarC(No *raiz, int &cont){
    if( raiz == NULL ) return;
    cont++;
    contarC(raiz->esq, cont);
    contarC(raiz->dir, cont);
}

int main(){
    No *raiz = new No;
    No *n1 = new No;
    No *n2 = new No;
    No *n3 = new No;
    No *n4 = new No;
    No *n5 = new No;
    No *n6 = new No;

    raiz->info = 'A'; raiz->esq = n1; raiz->dir = n2;
    n1->info = 'B';   n1->esq = n3;   n1->dir = n4;
    n2->info = 'C';   n2->esq = n5;   n2->dir = n6;
    n3->info = 'D';
    n4->info = 'E';
    n5->info = 'F';
    n6->info = 'G';

    cout << "Prefixado: ";
    prefixado(raiz);
    cout << endl << "Infixado: ";
    infixado(raiz);
    cout << endl << "Posfixado: ";
    posfixado(raiz);

    cout << endl << "Numero de nos: " << contarA(raiz);
    cout << endl << "Numero de nos: " << contarB(raiz);
    int num=0;
    contarC(raiz, num);
    cout << endl << "Numero de nos: " << num;

    cout << endl;
}
