#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

struct Proyecto {
    int num;
    int costo;
    int ganancia;
    int beneficio;
    double ratio;
    vector<int>predecesores;
    int cantPredecesores;
    bool escogido = false;
};

void ordenarProyectos(vector<Proyecto> &proyectos) {
    for (int i = 0; i < proyectos.size(); i++) {
        for (int j = i+1; j < proyectos.size(); j++) {
            if (proyectos[i].ratio < proyectos[j].ratio) {
                Proyecto aux = proyectos[i];
                proyectos[i] = proyectos[j];
                proyectos[j] = aux;
            }
        }
    }
}

bool cumple(vector<int> predecesores, vector<Proyecto> elegidos) {
    if (predecesores.size() == 0) return true;
    if (elegidos.size() == 0) return false;
    for (int i = 0; i < predecesores.size(); i++) {
        int n = -1;
        for (int j = 0; j < elegidos.size(); j++) {
            if (predecesores[i] == elegidos[j].num) n = 1;
        }
        if (n == -1) return false;
    }
    return true;
}

int main() {

    vector<Proyecto> proyectos;
    vector<vector<int>> numeros = {
        {80,150,2}, {20,80,5},{100,300,1},{100,150,4},
        {50,80,2},{10,50,1},{50,120,2},{50,150,4}
    };

    //Llenar Datos
    for (int i = 0; i < numeros.size(); i++) {
        Proyecto p;
        p.costo = numeros[i][0];
        p.ganancia = numeros[i][1];
        p.beneficio = numeros[i][2];
        p.ratio = (double)(p.ganancia*p.beneficio)/p.costo;
        //p.ratio = (double)p.ganancia/p.costo;
        p.num = i + 1;
        proyectos.push_back(p);
    }

    proyectos[1].predecesores = {4};
    proyectos[2].predecesores = {1,2};
    proyectos[5].predecesores = {2};
    proyectos[6].predecesores = {6};
    proyectos[7].predecesores = {6};

    for (int i = 0; i < proyectos.size(); i++) {
        proyectos[i].cantPredecesores = proyectos[i].predecesores.size();
    }

    ordenarProyectos(proyectos);

    // for (int i = 0; i < proyectos.size(); i++) {
    //     cout << proyectos[i].num << " " << proyectos[i].costo << " " << proyectos[i].ratio << endl;
    // }

    //Elegir
    vector<Proyecto> elegidos;
    int presupuesto = 250, suma = 0, sumaGanancia = 0;
    bool termina = false;
    while (true) {
        for (int i = 0; i < proyectos.size(); i++) {
            if (cumple(proyectos[i].predecesores, elegidos)){
                if (suma + proyectos[i].costo<= presupuesto) {
                    proyectos[i].escogido = true;
                    elegidos.push_back(proyectos[i]);
                    suma += proyectos[i].costo;
                    sumaGanancia += proyectos[i].ganancia;
                    proyectos.erase(proyectos.begin() + i);
                    break;
                } else
                    termina = true;
            }
        }
        if (termina) break;
    }


    cout << sumaGanancia << endl;
    for (int i = 0; i < elegidos.size(); i++) {
        cout << elegidos[i].num << " " << elegidos[i].costo << " " << elegidos[i].ganancia << endl;
    }

    return 0;
}
