#include <iostream>
#include <iomanip>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define ITERACIONES 5000
#define alfa 0.83

using namespace std;

struct Orden {
    int num;
    int cant;
    int prioridad;
};

struct Linea {
    int num;
    double tiempo;
    vector<Orden> ordenes;
};

void llenarOrdenes(vector<Orden>& auxOrdenes);

bool comparaOrden(Orden a, Orden b) {
    if (a.prioridad == b.prioridad) return a.cant > b.cant;
    return a.prioridad < b.prioridad;
}

bool comparaLinea(Linea a, Linea b) {
    if (a.tiempo == b.tiempo) return a.num < b.num;
    return a.tiempo < b.tiempo;
}

int hallarInd(int rcl, const vector<Orden>& ordenes) {
    int cont = 0;
    for (int i = 0; i < ordenes.size(); i++) {
        if (ordenes[i].cant >= rcl) {
            cont++;
            if (ordenes[i].prioridad != ordenes[i+1].prioridad) break;
        }
        if (ordenes[i].cant < rcl) break;
    }
    return cont;
}

int hallarUltimo(vector<Orden> ordenes) {
    int mejorPrioridad = ordenes[0].prioridad;
    int ultimaPrioridad = ordenes[ordenes.size()-1].prioridad;

    if (mejorPrioridad == ultimaPrioridad) return ordenes.size()-1;

    int contador = 0;
    for (int i = 0; i < ordenes.size(); i++) {
        if (ordenes[i].prioridad == mejorPrioridad) contador++;
        if (ordenes[i].prioridad < mejorPrioridad) break;
    }
    return contador - 1;
}

int main() {

    srand(time(NULL));
    vector<Orden> auxOrdenes;
    vector<Linea> mejorSol;
    int mejorMakespan = INT_MAX;
    int cantLineas = 5;
    int tiempoPorBotella = (2+1+1.5+1.5); //minutos

    llenarOrdenes(auxOrdenes);
    sort(auxOrdenes.begin(), auxOrdenes.end(), comparaOrden);

    vector<Orden> ordenes;

    for (int i = 0; i < ITERACIONES; i++) {
        vector<Linea> solActual{{1,0},{2,0},{3,0},{4,0},{5,0}};
        ordenes = auxOrdenes;

        //Constructor
        while (!ordenes.empty()) {
            sort(solActual.begin(), solActual.end(), comparaLinea);
            int ultimoMejorPrioridad = hallarUltimo(ordenes);
            int beta = ordenes[0].cant;
            int tau = ordenes[ultimoMejorPrioridad].cant;
            double rcl = beta - (alfa*(beta-tau));
            int indRcl = hallarInd(rcl, ordenes);
            int posA = rand() % indRcl;

            //Pongo en la linea de menor tiempo
            solActual[0].ordenes.push_back(ordenes[posA]);
            solActual[0].tiempo += ordenes[posA].cant*tiempoPorBotella;

            //Elimino orden
            ordenes.erase(ordenes.begin() + posA);
        }

        //Verifico si es mejor solucion
        int makespanActual = INT_MIN;
        for (int i = 0; i < cantLineas; i++) {
            if (makespanActual < solActual[i].tiempo) makespanActual = solActual[i].tiempo;
        }

        if (makespanActual < mejorMakespan) {
            mejorMakespan = makespanActual;
            mejorSol = solActual;
        }
    }

    //Imprimir Mejor Solucion
    for (int i = 0; i < cantLineas; i++) {
        cout << mejorSol[i].num << " " << mejorSol[i].tiempo << ": ";
        for (int j = 0; j < mejorSol[i].ordenes.size(); j++) {
            //cout << " " << mejorSol[i].ordenes[j].num << " " << mejorSol[i].ordenes[j].cant << endl;
            cout << mejorSol[i].ordenes[j].num << " ";
        }
        cout << endl;
    }
    cout << "Mejor makespan: " << mejorMakespan << endl;


    return 0;
}

void llenarOrdenes(vector<Orden>& auxOrdenes) {

    // Órdenes
    auxOrdenes.push_back({1, 103, 2});
    auxOrdenes.push_back({2, 58, 1});
    auxOrdenes.push_back({3, 88, 3});
    auxOrdenes.push_back({4, 126, 1});
    auxOrdenes.push_back({5, 195, 2});
    auxOrdenes.push_back({6, 90, 2});
    auxOrdenes.push_back({7, 54, 3});
    auxOrdenes.push_back({8, 195, 1});
    auxOrdenes.push_back({9, 124, 2});
    auxOrdenes.push_back({10, 113, 3});
    auxOrdenes.push_back({11, 193, 2});
    auxOrdenes.push_back({12, 55, 1});
    auxOrdenes.push_back({13, 97, 1});
    auxOrdenes.push_back({14, 97, 2});
    auxOrdenes.push_back({15, 169, 2});
    auxOrdenes.push_back({16, 50, 2});
    auxOrdenes.push_back({17, 167, 3});
    auxOrdenes.push_back({18, 74, 1});
    auxOrdenes.push_back({19, 79, 2});
    auxOrdenes.push_back({20, 109, 1});

}