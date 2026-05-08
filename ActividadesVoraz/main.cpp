#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Actividad {
    int num;
    char actividad;
    int inicio;
    int fin;
    bool estado = false;
};

bool comparar(Actividad a, Actividad b) {
    return a.fin < b.fin;
}

void ordenarActividades(vector<Actividad>& actividades) {
    for (int i = 0; i < actividades.size()-1; i++) {
        for (int j = 0; j < actividades.size()-1-i; j++) {
            if (actividades[j].fin > actividades[j+1].fin) {
                Actividad aux = actividades[j];
                actividades[j] = actividades[j+1];
                actividades[j+1] = aux;
            }
        }
    }
};

int main() {

    vector<Actividad> actividades;
    vector<vector<int>> matriz = {
        {5,9},{1,4},{8,11},{0,6},{6,10},{3,5},{5,7},{3,9}
    };

    //Llenar Actividades
    for (int i = 0; i < matriz.size(); i++) {
        Actividad a;
        a.num = 1;
        a.actividad = 65 + i; //65 es A
        a.inicio = matriz[i][0];
        a.fin = matriz[i][1];
        actividades.push_back(a);
    }

    //sort(actividades.begin(), actividades.end(), comparar);
    ordenarActividades(actividades);

    //Elegir
    int ultimoFin = -1;
    vector<Actividad> elegidos;
    for (int i = 0; i < actividades.size(); i++) {
        if (ultimoFin == -1) {
            actividades[i].estado = true;
            elegidos.push_back(actividades[i]);
            ultimoFin = actividades[i].fin;
        } else {
            if (ultimoFin <= actividades[i].inicio) {
                actividades[i].estado = true;
                elegidos.push_back(actividades[i]);
                ultimoFin = actividades[i].fin;
            }
        }
    }


    //Imprimir Actividades
    for (int i = 0; i < elegidos.size(); i++) {
        cout << elegidos[i].actividad << " ";
        cout << elegidos[i].inicio << " ";
        cout << elegidos[i].fin << endl;
    }

    return 0;
}
