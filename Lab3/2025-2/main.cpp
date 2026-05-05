#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Paquete {
    int num;
    int peso;
    bool usado;
};

struct Camion {
    int num;
    int capacidad;
    vector<Paquete> paquetes;
};

bool compararCamion(Camion c1, Camion c2) {
    return c1.capacidad < c2.capacidad;
}
bool compararPaquete(Paquete p1, Paquete p2) {
    return p1.peso > p2.peso;
}

bool ordenarNum(Camion c1, Camion c2) {
    return c1.num < c2.num;
}

int main() {

    //Llenar datos
    vector<int> pesos = {150,100,180,50,120,10};
    vector<int> capacidades = {250,200,200,100,300};
    vector<Paquete> paquetes;
    vector<Camion> camiones;

    for (int i = 0; i < pesos.size(); i++) {
        Paquete p;
        p.num = i+1;
        p.peso = pesos[i];
        p.usado = false;
        paquetes.push_back(p);
    }

    for (int i = 0; i < capacidades.size(); i++) {
        Camion c;
        c.num = i+1;
        c.capacidad = capacidades[i];
        camiones.push_back(c);
    }

    //Ordenar camiones de menor a mayor por peso
    sort(camiones.begin(), camiones.end(), compararCamion);
    //Ordenar paquetes de mayor a menor por peso
    sort(paquetes.begin(), paquetes.end(), compararPaquete);


    //Algoritmo voraz
    for (int i = 0; i < camiones.size(); i++) {
        Camion camion = camiones[i];
        int suma = 0;
        for (int j = 0; j < paquetes.size(); j++) {
            Paquete p = paquetes[j];
            if (p.usado == false) {
                if (suma + p.peso <= camion.capacidad) {
                    suma += p.peso;
                    paquetes[j].usado = true;
                    camiones[i].paquetes.push_back(paquetes[j]);
                }
            }
        }
    }


    //Imprimir Camiones
    sort(camiones.begin(), camiones.end(), ordenarNum);
    for (int i = 0; i < camiones.size(); i++) {
        Camion camion = camiones[i];
        cout << camion.num << " " << camion.capacidad << endl;
        for (int j = 0; j < camion.paquetes.size(); j++) {
            Paquete p = camion.paquetes[j];
            cout << "  " << p.num << " " << p.peso << endl;
        }
    }



    return 0;
}
