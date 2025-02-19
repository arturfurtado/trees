#include <iostream>
#include <chrono> //tempo dos algoritmos em execucao
#include <random> //numeros aleatorios
#include <map> //chaves-valor
#include <string> 
#include <functional> //funcoes como objeto (armazenar ponteiros)
#include <thread> 

//Artur Ramiro Furtado
//Diogo Henrique Ribicki

using namespace std;
using namespace std::chrono;

int* gerarVetor(int tamanho, int opcao) {
    int* vetor = new int[tamanho];
    if (opcao == 1) { //melhor caso ordenado
        for (int i = 0; i < tamanho; ++i) {
            vetor[i] = i + 1;
        }
    }
    else if (opcao == 2) {  //pior caso (ordem inversa)
        for (int i = 0; i < tamanho; ++i) {
            vetor[i] = tamanho - i;
        }
    }
    else { //caso aleatorio
        random_device rd; // semente para numeros aleatorios.
        mt19937 gen(rd()); //mersenne twister, gera numeros pseudoaleatorios
        uniform_int_distribution<> dis(1, tamanho); //gera os numeros apartir de 1 e tamanho
        for (int i = 0; i < tamanho; ++i) {
            vetor[i] = dis(gen);
        }
    }
    return vetor;
}

void insercaoDireta(int* vetor, int tamanho) {
    for (int i = 1; i < tamanho; ++i) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > chave) { //move elementos maiores que chave
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave; //insera a chave na posicao 
    }
}

int medianOfThree(int* vetor, int low, int high) {
    int mid = low + (high - low) / 2;
    if (vetor[low] > vetor[mid]) swap(vetor[low], vetor[mid]);
    if (vetor[low] > vetor[high]) swap(vetor[low], vetor[high]);
    if (vetor[mid] > vetor[high]) swap(vetor[mid], vetor[high]);
    return mid;
}

void quickSort(int* vetor, int low, int high) {
    if (low < high) {
        int pivotIndex = medianOfThree(vetor, low, high);
        swap(vetor[pivotIndex], vetor[high]); // pivot
        int pivot = vetor[high];

        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (vetor[j] < pivot) swap(vetor[++i], vetor[j]);
        }
        swap(vetor[i + 1], vetor[high]);

        quickSort(vetor, low, i); // corta à esquerda.
        quickSort(vetor, i + 2, high); // corta à direita.
    }
}


void bubbleSort(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = 0; j < tamanho - i - 1; ++j) {
            if (vetor[j] > vetor[j + 1]) {
                swap(vetor[j], vetor[j + 1]); //troca elementos adjacentes
            }
        }
    }
}


void shellSort(int* vetor, int tamanho) {
    for (int gap = tamanho / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < tamanho; ++i) {
            int temp = vetor[i];
            int j;
            for (j = i; j >= gap && vetor[j - gap] > temp; j -= gap) {
                vetor[j] = vetor[j - gap];
            }
            vetor[j] = temp;
        }
    }
}

void selecaoDireta(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; ++i) {
        int min_idx = i; //encontra o menor elemento
        for (int j = i + 1; j < tamanho; ++j) {
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        swap(vetor[min_idx], vetor[i]); //coloca o menor elemetno na posicao correta.
    }
}

void heapify(int* vetor, int tamanho, int i) {
    int maior = i;
    int esq = 2 * i + 1; //variavel para armazenar o filho esquerdo
    int dir = 2 * i + 2; //variavel para armazenar o filho direito

    if (esq < tamanho && vetor[esq] > vetor[maior])
        maior = esq;

    if (dir < tamanho && vetor[dir] > vetor[maior])
        maior = dir;

    if (maior != i) {
        swap(vetor[i], vetor[maior]); //troca o no atual com o maior filho
        heapify(vetor, tamanho, maior); //chama recursivamente para garantir o heap
    }
}

void heapSort(int* vetor, int tamanho) {
    for (int i = tamanho / 2 - 1; i >= 0; --i) {
        heapify(vetor, tamanho, i);
    }

    for (int i = tamanho - 1; i > 0; --i) {
        swap(vetor[0], vetor[i]); //move o maior elemento para o final
        heapify(vetor, i, 0); //restaura o heap 
    }
}

void merge(int* vetor, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = vetor[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = vetor[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        }
        else {
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int* vetor, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(vetor, l, m);
        mergeSort(vetor, m + 1, r);
        merge(vetor, l, m, r);
    }
}

int main() {
    int tamanho, opcao, repeticoes, escolhaAlgoritmo;

    cout << "Bem-vindo ao Comparador de Algoritmos de Ordenacao!\n";
    cout << "Digite o tamanho do vetor: ";
    cin >> tamanho;

    cout << "Escolha a situacao inicial dos dados:\n";
    cout << "1 - Melhor caso (ordenado)\n";
    cout << "2 - Pior caso (ordem inversa)\n";
    cout << "3 - Caso aleatorio\n";
    cout << "Opcao: ";
    cin >> opcao;

    cout << "Digite o numero de repeticoes: ";
    cin >> repeticoes;

    cout << "Escolha:\n";
    cout << "1 - Executar todos os algoritmos\n";
    cout << "2 - Escolher um algoritmo especifico\n";
    cout << "Opcao: ";
    cin >> escolhaAlgoritmo;

    vector<pair<string, function<void(int*, int)>>> algoritmos = {
        {"Insercao Direta", insercaoDireta},
        {"Bubble Sort", bubbleSort},
        {"Shell Sort", shellSort},
        {"Selecao Direta", selecaoDireta},
        {"Heap Sort", heapSort},
        {"Quick Sort", [](int* v, int n) { quickSort(v, 0, n - 1); }},
        {"Merge Sort", [](int* v, int n) { mergeSort(v, 0, n - 1); }}
    };

    if (escolhaAlgoritmo == 1) {
        map<string, double> tempos;
        for (auto& alg : algoritmos) {
            double tempoTotal = 0.0;
            for (int i = 0; i < repeticoes; ++i) {
                int* vetor = gerarVetor(tamanho, opcao);
                auto inicio = high_resolution_clock::now();
                alg.second(vetor, tamanho);
                auto fim = high_resolution_clock::now();
                duration<double, milli> duracao = fim - inicio;
                tempoTotal += duracao.count();
                delete[] vetor;
            }
            tempos[alg.first] = tempoTotal / repeticoes;
        }

        cout << "\nResultados Medios (em milissegundos):\n";
        for (auto& t : tempos) {
            cout << t.first << ": " << t.second << " ms\n";
        }
    }
    else if (escolhaAlgoritmo == 2) {
        cout << "Escolha um algoritmo:\n";
        for (int i = 0; i < algoritmos.size(); ++i) {
            cout << i + 1 << " - " << algoritmos[i].first << endl;
        }
        int escolha;
        cin >> escolha;

        if (escolha > 0 && escolha <= algoritmos.size()) {
            string nomeAlgoritmo = algoritmos[escolha - 1].first;
            double tempoTotal = 0.0;
            for (int i = 0; i < repeticoes; ++i) {
                int* vetor = gerarVetor(tamanho, opcao);
                auto inicio = high_resolution_clock::now();
                algoritmos[escolha - 1].second(vetor, tamanho);
                auto fim = high_resolution_clock::now();
                duration<double, milli> duracao = fim - inicio;
                tempoTotal += duracao.count();
                delete[] vetor;
            }
            cout << "\nTempo medio de " << nomeAlgoritmo << ": " << tempoTotal / repeticoes << " ms\n";
        }
        else {
            cout << "Algoritmo invalido!\n";
        }
    }

    return 0;
}
