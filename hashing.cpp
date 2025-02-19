#include <iostream>
#include "lde.hpp"
using namespace std;

#define TAMANHO 10

struct Hash{
    LDE <string> lista[TAMANHO];
};

int hashing(string chave){
    int soma = 0, pos;

    for( int i=0; i<chave.length(); i++ ){
        soma += int(chave[i]);
    }
    pos = soma % TAMANHO;
    return pos;
}

void inicializarHash(Hash &tabela){
    for( int i=0; i<TAMANHO; i++ ){
        inicializarLDE(tabela.lista[i]);
    }
}

void liberarHash(Hash &tabela){
    for( int i=0; i<TAMANHO; i++ ){
        liberarLDE(tabela.lista[i]);
    }
}

bool inserirHash(Hash &tabela, string palavra){
    int pos = hashing(palavra);
    if( pesquisarLDE(tabela.lista[pos], palavra) == NULL )
        return inserirLDE(tabela.lista[pos], palavra);
    else
        return false;
}

bool removerHash(Hash &tabela, string palavra){
    int pos = hashing(palavra);
    return retirarLDE(tabela.lista[pos], palavra);
}

bool pesquisarHash(Hash tabela, string palavra){
    int pos = hashing(palavra);
    return (pesquisarLDE(tabela.lista[pos], palavra) == NULL) ? false : true;
}

void mostrarHash(Hash &tabela){
    for( int i=0; i<TAMANHO; i++ ){
        cout << i << " => ";
        mostrarLDE(tabela.lista[i], 'C');
        cout << endl;
    }
}

int main(){
    string palavra;
    int opcao;
    Hash tabela;

    inicializarHash(tabela);

    do{
        cout << endl << "Menu:";
        cout << endl << "\t1. Inserir";
        cout << endl << "\t2. Retirar";
        cout << endl << "\t3. Pesquisar";
        cout << endl << "\t4. Mostrar";
        cout << endl << "\t5. Fim";
        cout << endl << "Opcao: ";
        cin >> opcao;
        fflush(stdin);

        switch(opcao){
            case 1 :
                cout << "Digite a palavra para inserir: ";
                cin >> palavra;
                if( inserirHash(tabela, palavra) )
                    cout << "Palavra inserida";
                else
                    cout << "Erro na insercao";
                break;
            case 2 :
                cout << "Digite a palavra para remover: ";
                cin >> palavra;
                if( removerHash(tabela, palavra) )
                    cout << "Palavra removida";
                else
                    cout << "Erro na remocao";
                break;
            case 3 :
                cout << "Digite a palavra para pesquisar: ";
                cin >> palavra;
                if( pesquisarHash(tabela, palavra) )
                    cout << "Palavra esta na tabela";
                else
                    cout << "Palavra nao localizada";
                break;
            case 4 :
                cout << "Tabela:" << endl;
                mostrarHash(tabela);
                break;
            case 5 :
                break;
            default:
                cout << "Erro: Opcao invalida";
        }
    }while( opcao != 5 );

    liberarHash(tabela);
    cout << endl;
}
