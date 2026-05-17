#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

//Codigo: 20230924
//Nombre: Vanessa Liliana Chavez Flores

void ordenar(vector<int> &numeros);
bool backTracking(vector<int> &numeros, int suma, vector<vector<int>> &subConjuntos, int i, vector<int>& orden, int sumaActual, int j);

vector<bool> estado(6,false);

int main() {

    vector<int> numeros = {3,1,1,4,2,5};
    vector<vector<int>> subConjuntos;
    vector<int> orden;
    int suma = 0;
    ordenar(numeros);

    for (int i = 0; i < numeros.size(); i++) {
        suma += numeros[i];
    }

    if (suma%2 == 0) {
        if (backTracking(numeros, suma, subConjuntos, 0, orden, 0, 0) == true) {
            for (int i = 0; i < subConjuntos.size(); i++) {
                cout << "Subconjunto " << i + 1 << ": {";
                for (int j = 0; j < subConjuntos[i].size(); j++) {
                    cout << subConjuntos[i][j] << " ";
                }
                cout << "}" << endl;
            }
        };
    }
    else {
        cout << "La suma es impar";
    }

    return 0;
}

bool backTracking(vector<int> &numeros, int suma, vector<vector<int>> &subConjuntos, int i, vector<int>& orden, int sumaActual, int j) {
    if (sumaActual == suma/2) {
        subConjuntos.push_back(orden);
        vector<int> segundo;
        for (int k = 0; k < numeros.size(); k++) {
            if (!estado[k]) {
                segundo.push_back(numeros[k]);
            }
        }
        subConjuntos.push_back(segundo);
        return true;
    }

    if (sumaActual > suma/2) return false;

    for (int l = i; l < numeros.size(); l++) {
        if (!estado[l]) {
            estado[l] = true;
            orden.push_back(numeros[l]);
            if (backTracking(numeros, suma, subConjuntos, l + 1, orden, sumaActual + numeros[l], j) == true) return true;
            estado[l] = false;
            orden.pop_back();
        }
    }
    return false;

}

void ordenar(vector<int> &numeros) {
    for (int i = 0; i < numeros.size(); i++) {
        for (int j = i + 1; j < numeros.size(); j++) {
            if (numeros[i] < numeros[j]) {
                int aux = numeros[i];
                numeros[i] = numeros[j];
                numeros[j] = aux;
            }
        }
    }
}