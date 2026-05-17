#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void imprimirMatriz(vector<vector<double>> matriz) {
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            cout << setw(4) << fixed <<  setprecision(2) << matriz[i][j] << " ";
        }
        cout << endl;
    }
}


void backTracking(const vector<vector<double>> &coordenadas, const vector<vector<double>> &matriz, vector<bool> visitado, double &mejorRuta, int &cantRutas, int posicion, double suma, int cantRecorrido);

int main() {

    vector<vector<double>> coordenadas = {
        {2,3},{1,1},{1,5.5},{6,3},{2.5,1},{3.5,6}
    };

    //Llenar matriz de distancias
    vector<vector<double>> matriz(coordenadas.size(), vector<double>(coordenadas.size(), 0));
    vector<bool> visitado (6, false);

    for (int i = 0; i < coordenadas.size(); i++) {
        for (int j = 0; j < coordenadas.size(); j++) {
            if (i == j) matriz[i][j] = 0;
            else {
                matriz[i][j] = (sqrt((pow(coordenadas[j][0] - coordenadas[i][0],2) + pow(coordenadas[j][1] - coordenadas[i][1] ,2))));
            }
        }
    }

    int cantRutas = 0;
    double mejorRuta = INT_MAX;

    backTracking(coordenadas, matriz, visitado, mejorRuta, cantRutas, 0, 0, 0);

    cout << cantRutas << endl;
    cout << mejorRuta << endl;

    imprimirMatriz(matriz);



    return 0;
}

void backTracking(const vector<vector<double>> &coordenadas, const vector<vector<double>> &matriz, vector<bool> visitado, double &mejorRuta, int &cantRutas, int posicion, double suma, int cantRecorrido) {
    if (cantRecorrido == coordenadas.size() - 1) {
        cantRutas++;
        suma += matriz[posicion][0];
        if (suma != 0 and suma < mejorRuta) mejorRuta = suma;
        return;
    }

    for (int i = 1; i < coordenadas.size(); i++) {
        if (!visitado[i]) {
            visitado[i] = true;
            backTracking(coordenadas, matriz, visitado, mejorRuta, cantRutas, i, suma + matriz[posicion][i], cantRecorrido + 1);
            visitado[i] = false;
        }
    }
}