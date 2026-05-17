#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct subConjuntos {
    int num;
    vector<int> datos;
    int yaUsados;
    bool usado = false;
};

bool comparar(subConjuntos a, subConjuntos b) {
    if (a.yaUsados == b.yaUsados) return a.num < b.num;
    return a.yaUsados < b.yaUsados;
}

int main() {

    vector<int> U = {1,2,3,4,5,6,7};
    vector<bool> usados(U.size(), false);
    vector<vector<int>> sub = {
        {1,2,3},{2,4,5},{3,5,6},{6,7}
    };

    vector<subConjuntos> conjuntos;

    //Llenar datos
    for (int i = 0; i < sub.size(); i++) {
        subConjuntos s;
        s.num = i + 1;
        s.yaUsados = 0;
        s.datos = sub[i];
        conjuntos.push_back(s);
    }

    //Ordenar por cantidad de usados
    while (true) {
        sort(conjuntos.begin(), conjuntos.end(), comparar);
        conjuntos[0].yaUsados = conjuntos[0].datos.size();
        conjuntos[0].usado = true;
        for (int i = 0; i < conjuntos[0].datos.size(); i++) {
            usados[conjuntos[0].datos[i] - 1] = true;
            for (int j = 1; j < conjuntos.size(); j++) {
                for (int k = 0; k < conjuntos[j].datos.size(); k++) {
                    if (conjuntos[0].datos[i] == conjuntos[j].datos[k]) conjuntos[j].yaUsados++;
                }
            }
        }

        bool todos = true;
        for (int i = 0; i < usados.size(); i++) {
            if (!usados[i]) {
                todos = false;
                break;
            }
        }
        if (todos) break;
    }

    //Imprimir
    for (int i = 0; i < conjuntos.size(); i++) {
        if (conjuntos[i].usado) {
            cout << conjuntos[i].num << " ";
        }
    }



    return 0;
}
