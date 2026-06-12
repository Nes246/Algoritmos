#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdlib>
#define alfa 0.3
#define ITERACIONES 3000

using namespace std;

void constructorMoneda(vector<int> denominaciones, int monto, vector<int> &solucion);

int main() {

    srand(time(NULL));
    int mejorCantidad = INT_MAX;
    vector <int> denominaciones = {100, 90, 1};
    vector <int> mejorSol;

    for (int i = 1; i <= ITERACIONES; i++) {
        denominaciones = {100, 90, 1};
        //sort(denominaciones.begin(), denominaciones.end());

        vector <int> solucionActual;
        int monto = 180;
        constructorMoneda(denominaciones, monto, solucionActual);

        //Conseguir mejor solucion
        if (solucionActual.size() < mejorCantidad) {
            mejorCantidad = solucionActual.size();
            mejorSol = solucionActual;
        }
    }

    for (int i = 0; i < mejorSol.size(); i++) {
        cout << mejorSol[i] << " ";
    }

    return 0;
}

int hallarIndice(int num, vector<int> denominaciones) {
    int cont = 0;
    for (int i = 0; i < denominaciones.size(); i++) {
        if (denominaciones[i] >= num) cont++;
    }
    return cont;
}

void constructorMoneda(vector<int> denominaciones, int monto, vector<int> &solucion) {
    while (!denominaciones.empty()) {
        int tau = denominaciones[denominaciones.size() - 1];
        int beta = denominaciones[0];
        double rcl = beta - (alfa*(beta-tau));
        int indRcl = hallarIndice(rcl, denominaciones);
        //int cantRcl = denominaciones.size() - indRcl;
        int pos = rand() %  indRcl;
        if (denominaciones[pos] <= monto) {
            int cant = monto/denominaciones[pos];
            solucion.insert(solucion.end(), cant, denominaciones[pos]);
            monto = monto - cant*denominaciones[pos];
        }
        denominaciones.erase(denominaciones.begin() + pos);
    }
}