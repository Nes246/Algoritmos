#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

struct Punto {
    int num;
    char punto;
    vector<int>siguientes;
    vector<int>distanciasSiguientes;
    int cantidadSiguientes = 0;
};

void ordenarVecinos(struct Punto& punto) {
    if (punto.cantidadSiguientes == 1) return;
    for (int i = 0; i < punto.cantidadSiguientes; i++) {
        for (int j = i; j < punto.cantidadSiguientes; j++) {
            if (punto.distanciasSiguientes[i] > punto.distanciasSiguientes[j]) {
                int aux1 = punto.distanciasSiguientes[i];
                int aux2 = punto.siguientes[i];
                punto.siguientes[i] = punto.siguientes[j];
                punto.siguientes[j] = aux2;
                punto.distanciasSiguientes[i] = punto.distanciasSiguientes[j];
                punto.distanciasSiguientes[j] = aux1;
            }
        }
    }
}

int main() {

    //LlenarDatos
    vector<vector<int>> siguientes = {
        {4,3,2},{5},{8}, {6}, {7}, {7,8}, {}, {}
    };
    vector<vector<int>> distanciasSiguientes = {
        {6,5,4},{2},{3},{3},{10},{2,5},{},{}
    };

    vector<Punto> puntos;

    for (int i = 0; i < siguientes.size(); i++) {
        Punto p;
        p.num = i+1;
        p.punto = 65+i;
        p.siguientes = siguientes[i];
        p.distanciasSiguientes =distanciasSiguientes[i];
        p.cantidadSiguientes = p.siguientes.size();
        puntos.push_back(p);
    }

    int ini = 1, fin = 8, tiempo = 0;

    int i = ini-1;
    while (true) {
        if (puntos[i].cantidadSiguientes != 0) {
            ordenarVecinos(puntos[i]);
            tiempo += puntos[i].distanciasSiguientes[0];
            i = puntos[i].siguientes[0] - 1;
        }
        if (puntos[i].num == fin) {
            cout << "Se llego al destino en " << tiempo;
            break;
        }
        if (puntos[i].cantidadSiguientes == 0) {
            cout << "NO se pudo llegar";
            break;
        }
    }

    return 0;
}
