#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <climits>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define ITERACIONES 1000
#define alfa 0.7

using namespace std;

int hallarInd(double rcl, vector<int> objetos) {
    int cont = 0;
    for (int i = 0; i < objetos.size(); i++) {
        if (objetos[i] >= rcl) cont++;
    }
    return cont;
}

int main() {

    srand(time(NULL));
    vector<int> mejorSol;
    vector<int> objetosAux = {5,5,5,5,5,5,4,4,4,4,4};
    sort(objetosAux.rbegin(), objetosAux.rend());
    vector<int> objetos;
    int capacidadMaxima = 10;
    int mejorSolucion = INT_MAX;

    for (int i = 0; i < ITERACIONES; i++) {
        objetos = objetosAux;
        vector<int> solActual(objetos.size(),capacidadMaxima);

        //Constructor
        while (!objetos.empty()) {
            int beta = objetos[0];
            int tao = objetos[objetos.size()-1];
            double rcl = beta - alfa*(beta-tao);
            int indRcl = hallarInd(rcl, objetos);
            int posA = rand() % indRcl;
            int i = 0;
            while (solActual[i] < objetos[posA]) i++;
            solActual[i] -= objetos[posA];
            objetos.erase(objetos.begin()+posA);
        }

        //Elimino los que no se usaron
        while (solActual.back() == 10) solActual.pop_back();

        int usadosActual = solActual.size();
        if (usadosActual < mejorSolucion) {
            mejorSolucion = usadosActual;
            mejorSol = solActual;
        }
    }

    for (int i = 0; i < mejorSol.size(); i++) {
        cout << mejorSol[i] << " ";
    }
    cout << endl;
    cout << mejorSolucion;

    return 0;
}
