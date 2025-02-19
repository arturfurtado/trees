#include <iostream>
using namespace std;

template <typename T>
struct No{
    T info;
    int alt;
    No <T> *esq=NULL, *dir=NULL;
};

template <typename T>
void prefixado(No <T> *raiz){
    if( raiz == NULL ) return;
    cout << raiz->info << " ";
    prefixado(raiz->esq);
    prefixado(raiz->dir);
}

template <typename T>
void infixado(No <T> *raiz){
    if( raiz == NULL ) return;
    infixado(raiz->esq);
    cout << raiz->info << " ";
    infixado(raiz->dir);
}

template <typename T>
void posfixado(No <T> *raiz){
    if( raiz == NULL ) return;
    posfixado(raiz->esq);
    posfixado(raiz->dir);
    cout << raiz->info << " ";
}

template <typename T>
int contar(No <T> *raiz){
    if( raiz == NULL ) return 0;
    return 1 + contar(raiz->esq) + contar(raiz->dir);
}

template <typename T>
int altura(No <T> *raiz){
    return (raiz==NULL) ? 0 : raiz->alt;
}

template <typename T>
int calcular_altura(No <T> *raiz ){
    int aE = altura(raiz->esq);
    int aD = altura(raiz->dir);
    return (aE>aD) ? aE+1 : aD+1;
}

template <typename T>
No <T> *rotacao_simples_direita(No <T> *k){
    No <T> *x = k->esq;
    No <T> *t2 = x->dir;

    x->dir = k;
    k->esq = t2;
    k->alt = calcular_altura(k);
    x->alt = calcular_altura(x);

    cout << "RSD no " << k->info << endl;

    return x;
}

template <typename T>
No <T> *rotacao_dupla_direita(No <T> *k){
    No <T> *x = k->esq;
    No <T> *w = x->dir;
    No <T> *t2 = w->esq;
    No <T> *t3 = w->dir;

    w->esq = x;
    w->dir = k;
    x->dir = t2;
    k->esq = t3;
    k->alt = calcular_altura(k);
    x->alt = calcular_altura(x);
    w->alt = calcular_altura(w);

    cout << "RDD no " << k->info << endl;

    return w;
}

template <typename T>
No <T> *rotacao_simples_esquerda(No <T> *k){
    No <T> *y = k->dir;
    No <T> *t2 = y->esq;

    y->esq = k;
    k->dir = t2;
    k->alt = calcular_altura(k);
    y->alt = calcular_altura(y);

    cout << "RSE no " << k->info << endl;
    return y;
}

template <typename T>
No <T> *rotacao_dupla_esquerda(No <T> *k){
    No <T> *y = k->dir;
    No <T> *z = y->esq;
    No <T> *t2 = z->esq;
    No <T> *t3 = z->dir;

    z->esq = k;
    z->dir = y;
    k->dir = t2;
    y->esq = t3;

    k->alt = calcular_altura(k);
    y->alt = calcular_altura(y);
    z->alt = calcular_altura(z);

    cout << "RDE no " << k->info << endl;
    return z;
}

template <typename T>
No <T> *rotacaoAVL(No <T> *k){
    if( altura(k->esq) > altura(k->dir) ){
        No <T> *x = k->esq;
        if( altura(x->esq) >= altura(x->dir) )
            k = rotacao_simples_direita(k);
        else
            k = rotacao_dupla_direita(k);
    }
    else{
        No <T> *y = k->dir;
        if( altura(y->dir) >= altura(y->esq) )
            k = rotacao_simples_esquerda(k);
        else
            k = rotacao_dupla_esquerda(k);
    }
    return k;
}

template <typename T>
No <T> * inserirAVL( No <T> *raiz, T info ){
    if( raiz == NULL ){
        raiz = new No<T>;
        if( raiz == NULL ) return NULL;  // Memoria cheia
        raiz->info = info;
        raiz->alt = 1;
        return raiz;
    }
    if( info == raiz->info ) return NULL; // Chave duplicada
    if( info < raiz->info )
        raiz->esq = inserirAVL(raiz->esq, info);
    else
        raiz->dir = inserirAVL(raiz->dir, info);
    int aE = altura(raiz->esq);
    int aD = altura(raiz->dir);
    if( aE-aD == 2 || aE-aD == -2 ) raiz = rotacaoAVL(raiz);
    raiz->alt = calcular_altura(raiz);
    return raiz;
}

template <typename T>
T buscar_maior_valor(No <T> *raiz){
    if( raiz->dir == NULL )
        return raiz->info;
    else
        return buscar_maior_valor(raiz->dir);
}

template <typename T>
No <T> * retirarAVL( No <T> *raiz, T info ){
    if( raiz == NULL ) return NULL;
    if( info == raiz->info ){
        No <T> *aux = raiz;
        if( raiz->esq == NULL && raiz->dir == NULL ){
            delete raiz;
            return NULL;
        }
        else if( raiz->esq == NULL && raiz->dir != NULL ){
            delete aux;
            return raiz->dir;
        }
        else if( raiz->esq != NULL && raiz->dir == NULL ){
            delete aux;
            return raiz->esq;
        }
        T aux2 = buscar_valor_troca(raiz->esq);
        raiz->info = aux2;
        return retirarAVL(raiz->esq, aux2);
    }
    if( info < raiz->info )
        raiz->esq = retirarAVL(raiz->esq, info);
    else
        raiz->dir = retirarAVL(raiz->dir, info);
    int aE = altura(raiz->esq);
    int aD = altura(raiz->dir);
    if( aE-aD == 2 || aE-aD == -2 ) raiz = rotacaoAVL(raiz);
    raiz->alt = calcular_altura(raiz);
    return raiz;
}

template <typename T>
bool pesquisarAVL(No <T> *raiz, T info){
    if( raiz == NULL ) return false;
    if( info == raiz->info ) return true;
    if( info < raiz->info )
        return pesquisarAVL(raiz->esq, info);
    else
        return pesquisarAVL(raiz->dir, info);
}

template <typename T>
void liberarAVL(No <T> *&raiz){
    if( raiz == NULL ) return;
    liberarAVL(raiz->esq);
    liberarAVL(raiz->dir);
    delete raiz;
}

template <typename T>
void mostrar_arvore(No  <T> *raiz, int tab=3 ){
    cout << endl;
    for( int i=0; i<tab; i++ ) cout << " ";
    if( raiz == NULL ){
        cout << "*";
        return;
    }
    cout << raiz->info << " (" << raiz->alt << ")" ;
    mostrar_arvore( raiz->esq, tab+3 );
    mostrar_arvore( raiz->dir, tab+3 );
}



