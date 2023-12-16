#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;
using namespace std::chrono;

// PIVOS NORMAIS

void swap(int &a, int &b, int &movimentation) {
    movimentation += 1;
    int t = a;
    a = b;
    b = t;
}

void exibirLista(const vector<int> &lista) {
    cout << "[";
    for (size_t i = 0; i < lista.size(); ++i) {
        cout << lista[i];
        if (i < lista.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]\n";
}

int returnPivo(string type, vector<int> &vetor, int lo, int hi) {
    if (type == "inicio") {
        return vetor[lo];
    } else if (type == "central") {
        return vetor[(hi + lo) / 2];
    } else if (type == "media") {
        return (vetor[lo] + vetor[(hi + lo) / 2] + vetor[hi]) / 3;
    } else if (type == "random") {
        int randIndex = rand() % (hi - lo + 1) + lo;
        return vetor[randIndex];
    } else if (type == "mediana") {
        int elementoDoMeio;
        if ((vetor[lo] <= vetor[(hi + lo) / 2] && vetor[(hi + lo) / 2] <= vetor[hi]) ||
            (vetor[hi] <= vetor[(hi + lo) / 2] && vetor[(hi + lo) / 2] <= vetor[lo])) {
            elementoDoMeio = vetor[(hi + lo) / 2];
        } else if ((vetor[(hi + lo) / 2] <= vetor[lo] && vetor[lo] <= vetor[hi]) ||
                   (vetor[hi] <= vetor[lo] && vetor[lo] <= vetor[(hi + lo) / 2])) {
            elementoDoMeio = vetor[lo];
        } else {
            elementoDoMeio = vetor[hi];
        }
        return elementoDoMeio;
    }
    
    return -1;
}

int partition(vector<int> &vetor, int lo, int hi, int &movimentation, int &comparation, string typeOfPivot) {
    int pivo = returnPivo(typeOfPivot, vetor, lo, hi);
    int i = lo - 1;
    int j = hi + 1;
    while (true) {
        for (i = i + 1; vetor[i] < pivo; i++) {
            comparation += 1;
        }
        for (j = j - 1; vetor[j] > pivo; j--) {
            comparation += 1;
        }
        if (i >= j)
            break;
        swap(vetor[i], vetor[j], movimentation);
    }
    return j;
}

void quickSortIterative(vector<int> &vetor, int lo, int hi, int &comparation, int &movimentation, string typeOfPivot) {
    stack<pair<int, int>> pilha;
    pilha.push({lo, hi});
    while (!pilha.empty()) {
        auto [lo, hi] = pilha.top();
        pilha.pop();
        int p = partition(vetor, lo, hi, movimentation, comparation, typeOfPivot);
        if (p - 1 > lo) {
            pilha.push({lo, p - 1});
        }
        if (p + 1 < hi) {
            pilha.push({p + 1, hi});
        }
    }
}

vector<int>* generateList(int size, double exchangePercentage) {
    vector<int>* list = new vector<int>;
    for (int i = 1; i <= size; ++i) {
        list->push_back(i);
    }
    int numberOfExchange = size * exchangePercentage;
    for (int i = 0; i < numberOfExchange; ++i) {
        int index1 = rand() % size;
        int index2 = rand() % size;
        swap((*list)[index1], (*list)[index2], i);
    }
    return list;
}

// ACHA PIVO

void achaPivo(int N1, int N2, int& PTO, vector<int>& Lista) {
    int ESQ, DIR, POS;
    ESQ = N1;
    DIR = N2;
    POS = ESQ + 1;
    PTO = 0;

    while (POS <= DIR) {
        if (POS > DIR) {
            break;
        } else if (Lista[POS] >= Lista[POS - 1]) {
            POS = POS + 1;
        } else {
            PTO = POS;
            break;
        }
    }
}

void partitionAchaPivo(int N1, int N2, float PIVO, int& P, vector<int>& L) {
    int ESQ, DIR;
    ESQ = N1;
    DIR = N2;

    do {
        swap(L[ESQ], L[DIR]);

        while (L[ESQ] <= PIVO) {
            ESQ = ESQ + 1;
        }

        while (L[DIR] > PIVO) {
            DIR = DIR - 1;
        }

    } while (ESQ <= DIR);

    P = DIR;
}

void quickSortAchaPivo(vector<int>& L, int N1, int N2) {
    stack<pair<int, int>> pilha;
    pilha.push({N1, N2});

    while (!pilha.empty()) {
        auto [ESQ, DIR] = pilha.top();
        pilha.pop();

        int PTO;
        achaPivo(ESQ, DIR, PTO, L);

        if (PTO != 0) {
            int P;
            partitionAchaPivo(ESQ, DIR, L[PTO], P, L);
            pilha.push({ESQ, P});
            pilha.push({P + 1, DIR});
        }
    }
}

// MAIN

int main() {
    string typeOfPivot = "achaPivo";
    int size = 100;
    double randomPercentage = 0.45;

    vector<int>* vetor = generateList(size, randomPercentage);
    int comparation = 0, movimentation = 0;
    srand(time(NULL));
    exibirLista(*vetor);

    auto start = high_resolution_clock::now();
    if(typeOfPivot == "achaPivo") quickSortAchaPivo(*vetor, 0, size - 1);
    else quickSortIterative(*vetor, 0, size - 1, comparation, movimentation, typeOfPivot);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tempo de execução para QuickSort com pivot " << typeOfPivot << ": " << duration.count() << " microssegundos" << endl;
    exibirLista(*vetor);
    delete vetor;

    return 0;
}
