#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>   // Para a função rand()
#include <ctime>     // Para a função time()

using namespace std;
using namespace std::chrono;

void swap(int &a, int &b, int &movimentation) {
    movimentation += 1;
    int t = a;
    a = b;
    b = t;
}

int returnPivo(string type, vector<int> &vetor, int lo, int hi) {
    if (type == "inicio") {
        return vetor[lo];
    } else if (type == "central") {
        return vetor[(hi + lo) / 2];
    } else if (type == "media") {
        return (vetor[lo] + vetor[(hi + lo) / 2] + vetor[hi]) / 3;
    } else if (type == "random") {
        // Certifique-se de que o índice aleatório está dentro dos limites válidos
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
    } else if (type == "achaPivo") {
        // Procedimento Acha pivô
    }

    return -1; // Caso nenhum tipo correspondente seja encontrado, retorne um valor padrão.
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

void quickSort(vector<int> &vetor, int lo, int hi, int &comparation, int &movimentation, string typeOfPivot) {
    if (lo < hi) {
        int p = partition(vetor, lo, hi, movimentation, comparation, typeOfPivot);

        quickSort(vetor, lo, p, comparation, movimentation, typeOfPivot);
        quickSort(vetor, p + 1, hi, comparation, movimentation, typeOfPivot);
    }
}

vector<int> generateList(int size, double exchangePercentage) {
    // Crie uma lista de números aleatórios
    vector<int> list;

    // Preencha a lista com números aleatórios (este exemplo usa números sequenciais)
    for (int i = 1; i <= size; ++i) {
        list.push_back(i);
    }

    int numberOfExchange = size * exchangePercentage;

    for (int i = 0; i < numberOfExchange; ++i) {
        int index1 = rand() % size;
        int index2 = rand() % size;

        // Troque os valores nos índices aleatórios
        swap(list[index1], list[index2]);
    }

    return list;
}


int main() {
    // "inicio", "central", "media", "random", "mediana", "achaPivo"
    string typeOfPivot = "media";
    
    // 100, 1000, 10000...
    int size = 10000;

    // 0.05, 0.25, 0.45
    double randomPercentage = 0.45;
    
    
    vector<int> vetor = generateList(size, randomPercentage);
    int comparation = 0, movimentation = 0;
    srand(time(NULL));
    
    auto start = high_resolution_clock::now();
    quickSort(vetor, 0, size - 1, comparation, movimentation, typeOfPivot);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tempo de execução para QuickSort com pivot " << typeOfPivot << ": " << duration.count() << " microssegundos" << endl;

    return 0;
}