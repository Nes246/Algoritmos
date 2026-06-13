#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <climits>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define ITERACIONES 10000
#define alfa 0.4

using namespace std;

struct Punto {
    int num;
    char letra;
    vector <int> destinos;
    int pago;
};

void llenarPuntos(vector <Punto>& puntos);

void ordenarPorPago(vector<int>& destinos, const vector<Punto>& puntosAux) {
    for (int i = 0; i < destinos.size() - 1; i++) {
        for (int j = i + 1; j < destinos.size(); j++) {
            if (puntosAux[destinos[i]-1].pago < puntosAux[destinos[j]-1].pago) {
                int aux = destinos[j];
                destinos[j] = destinos[i];
                destinos[i] = aux;
            }
        }
    }
}

int hallarIndRcl(double rcl, vector<int> destinos, const vector<Punto>& puntosAux) {
    int cont = 0;
    for (int i = 0; i < destinos.size(); i++) {
        int pos = destinos[i]-1;
        if (puntosAux[pos].pago >= rcl) cont++;
    }
    return cont;
}

int main() {

    vector <Punto> puntosAux;
    llenarPuntos(puntosAux);
    vector <Punto> puntos;
    int mejorPago = INT_MIN;
    vector <Punto> mejorSol;

    for (int i=0; i < ITERACIONES; i++) {
        //vector <Punto> puntos = puntosAux;
        int pagoActual = 0;
        vector <Punto> solActual;

        //Constructor
        int puntoElegido = 0;
        while (puntosAux[puntoElegido].destinos.size() != 0) {
            ordenarPorPago(puntosAux[puntoElegido].destinos, puntosAux);
            vector<int> destinos = puntosAux[puntoElegido].destinos;
            int beta = puntosAux[destinos[0]-1].pago;
            int tao = puntosAux[destinos[destinos.size() - 1]-1].pago;
            double rcl = beta - alfa*(beta - tao);
            int indRcl = hallarIndRcl(rcl, destinos, puntosAux);
            int posA = rand() % indRcl;

            puntoElegido = destinos[posA] - 1;
            solActual.push_back(puntosAux[puntoElegido]);
            pagoActual += puntosAux[puntoElegido].pago;
        }

        //Hallar si es mejor
        if (pagoActual > mejorPago) {
            mejorPago = pagoActual;
            mejorSol = solActual;
        }

    }

    cout << "Puntos seleccionados: ";
    for (int i=0; i < mejorSol.size(); i++) {
        cout << mejorSol[i].letra << " ";
    }
    cout << endl;
    cout << "Ganancia: " << mejorPago << endl;


    return 0;
}

void llenarPuntos(vector <Punto>& puntos) {
    puntos = {
        {1,'A',{2,3,4,5,8},0},
         {2,'B',{3,4,6,8},20},
         {3,'C',{6},30},
         {4,'D',{},40},
         {5,'E',{3,6,7},40},
         {6,'F',{},40},
         {7,'G',{},10},
         {8,'H',{},50}
    };
}
