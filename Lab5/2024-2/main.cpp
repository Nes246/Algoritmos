#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#define ITERACIONES 1000
#define NUMIND 20
#define PCASAMIENTO 0.8
#define PMUTACION 0.1
#define TSELECCION 0.5

using namespace std;

int calcularFitness(const vector<int>& ind, const vector<vector<int>>& ganancias);
void matarClones(vector<vector<int>>& poblacion);
void generarPoblacion(vector<vector<int>>& poblacion, const vector<vector<int>>& ganancias);
void seleccion(vector<vector<int>>&  padres, const vector<vector<int>>& ganancias, const vector<vector<int>>& poblacion, int cantEmpleados, int cantTareas);
void casamiento(const vector<vector<int>>&  padres, const vector<vector<int>>& ganancias, vector<vector<int>>& poblacion, int cantEmpleados, int cantTareas);
void mutacion(vector<vector<int>> padres, const vector<vector<int>>& ganancias, vector<vector<int>>& poblacion);
void regeneraPoblacion(vector<vector<int>>& poblacion, const vector<vector<int>>& ganancias);

int main() {

    srand(time(NULL));
    vector<vector<int>> ganancias{{9,2,7,8,6},
        {6,4,3,7,8},
        {5,8,1,8,3},
        {7,6,9,4,2},
        {8,6,7,5,9}};
    int cantEmpleados = 5, cantTareas = 5;
    vector<vector<int>> poblacion;

    generarPoblacion(poblacion, ganancias);

    for (int i = 0; i < ITERACIONES; i++) {
        vector<vector<int>> padres;
        seleccion(padres, ganancias, poblacion, cantEmpleados, cantTareas);
        casamiento(padres, ganancias, poblacion, cantEmpleados, cantTareas);
        mutacion(padres, ganancias, poblacion);
        regeneraPoblacion(poblacion, ganancias);
    }

    for (int i = 0; i < poblacion[0].size(); i++) {
        cout << poblacion[0][i] << " ";
    }
    cout << endl;
    cout << calcularFitness(poblacion[0], ganancias) << endl;

    cout << "Mejor asignacion:" << endl;

    for (int i = 0; i < poblacion[0].size(); i++) {

        if (poblacion[0][i] == 1) {

            int empleado = i / cantTareas;
            int tarea = i % cantTareas;

            cout << "Empleado " << empleado + 1
                 << " => Tarea " << tarea + 1 << endl;
        }
    }

    cout << "Ganancia total: "
         << calcularFitness(poblacion[0], ganancias) << endl;


    return 0;
}

bool esRepetido(const vector<int>& ind, const vector<vector<int>>& poblacion) {
    for (int i = 0; i < poblacion.size(); i++) {
        if (ind == poblacion[i]) return true;
    }
    return false;
}

bool aberracion(const vector<int>& ind, const vector<vector<int>>& ganancias) {
    int cantEmpleados = ganancias.size();
    int cantTareas = ganancias[0].size();

    vector<int> tareasXempleado(cantTareas, 0);
    for (int i = 0; i < cantEmpleados; i++) {
        int sumaEmpleados = 0;
        for (int j = i * cantEmpleados; j < (i+1)*cantEmpleados; j++) {
            if (ind[j] == 1) {
                sumaEmpleados++;
                tareasXempleado[j - (i * cantEmpleados)]++;
            }
        }
        if (sumaEmpleados != 1) return true;
    }

    for (int i = 0; i < cantTareas; i++) {
        if (tareasXempleado[i] != 1) return true;
    }

    return false;
}


void generarPoblacion(vector<vector<int>>& poblacion, const vector<vector<int>>& ganancias) {

    int contador = 0;
    int intentos = 0;
    int cantGenes = 25;
    while (contador < NUMIND) {
        vector<int> ind(cantGenes,0);
        for (int i = 0; i < ganancias[0].size(); i++) {
            int empleadoSeleccionado = rand()% ganancias.size();
            int pos = empleadoSeleccionado * ganancias[0].size() + i;
            ind[pos] = 1;
        }

        if (!aberracion(ind, ganancias) && !esRepetido(ind, poblacion)) {
            poblacion.push_back(ind);
            contador++;
        }
        intentos++;
    }
}

int calcularFitness(const vector<int>& ind, const vector<vector<int>>& ganancias) {
    int fitness = 0;
    for (int i = 0; i < ind.size(); i++) {
        int empleado, tarea;
        if (ind[i] == 1) {
            empleado = i / 5;
            tarea = i % 5;
            fitness += ganancias[empleado][tarea];
        }
    }
    return fitness;
}

void calcularSupervivencia(vector<int>& supervivencia, const vector<vector<int>>& padres, const vector<vector<int>>& ganancias, const vector<vector<int>>& poblacion, int cantEmpleados, int cantTareas) {

    vector<int> fitness;
    int sumaFitness = 0;
    for (int i = 0; i < poblacion.size(); i++) {
        fitness.push_back(calcularFitness(poblacion[i], ganancias));
        sumaFitness += fitness[i];
    }

    for (int i = 0; i < poblacion.size(); i++) {
        supervivencia.push_back(100*((double)fitness[i]/sumaFitness));
    }

}

void generarRuleta(const vector<int>& supervivencia, vector<int>& ruleta) {
    int cont = 0;
    for (int i = 0; i < supervivencia.size(); i++) {
        for (int j = 0; j < supervivencia[i]; j++) {
            ruleta[cont++] = i;
        }
    }

}

void seleccion(vector<vector<int>>&  padres, const vector<vector<int>>& ganancias, const vector<vector<int>>& poblacion, int cantEmpleados, int cantTareas) {

    int numPadres = round(ganancias.size()*0.5);
    vector<int> supervivencia;
    calcularSupervivencia(supervivencia, padres, ganancias, poblacion, cantEmpleados, cantTareas);

    vector<int> ruleta(100, -1);
    generarRuleta(supervivencia, ruleta);

    int contador = 0;
    while (contador < numPadres){
        int ticket = rand() % 100;
        if (ruleta[ticket] != -1) {
            padres.push_back(poblacion[ruleta[ticket]]);
            contador++;
        }
    }
}

void crearHijo(vector<int>& hijo, const vector<int>& padre, const vector<int>& madre) {

    int pGen = round(padre.size()*PCASAMIENTO);

    for (int i = 0; i < pGen; i++) {
        hijo.push_back(padre[i]);
    }

    for (int i = pGen; i < madre.size(); i++) {
        hijo.push_back(madre[i]);
    }

}

void casamiento(const vector<vector<int>>&  padres, const vector<vector<int>>& ganancias, vector<vector<int>>& poblacion, int cantEmpleados, int cantTareas) {

    for (int i = 0; i < padres.size(); i++) {
        for (int j = 0; j < padres.size(); j++) {
            vector<int> hijo;
            if (i != j) {
                crearHijo(hijo, padres[i], padres[j]);
                if (!aberracion(hijo, ganancias) && !esRepetido(hijo, poblacion)) {
                    poblacion.push_back(hijo);
                }
            }
        }
    }
}

void mutacion(vector<vector<int>> padres, const vector<vector<int>>& ganancias, vector<vector<int>>& poblacion) {

    int cantMutaciones = round(padres[0].size()*PMUTACION);

    for (int i = 0; i < padres.size(); i++) {
        int cont = 0;
        while (cont<cantMutaciones) {
            int gen = rand()%padres[i].size();
            padres[i][gen] = 1 - padres[i][gen];
            cont++;
        }
        if (!aberracion(padres[i], ganancias) && !esRepetido(padres[i], poblacion)) {
            poblacion.push_back(padres[i]);
        }
    }
}

void matarClones(vector<vector<int>>& poblacion) {

    vector<vector<int>> nuevaPoblacion;

    for (int i = 0; i < poblacion.size(); i++) {
        if (!esRepetido(poblacion[i], nuevaPoblacion)) {
            nuevaPoblacion.push_back(poblacion[i]);
        }
    }
    poblacion = nuevaPoblacion;
}


void regeneraPoblacion(vector<vector<int>>& poblacion, const vector<vector<int>>& ganancias) {

    //matarClones(poblacion);

    sort(poblacion.begin(), poblacion.end(), [&ganancias](const vector<int>& a, const vector<int>& b) {
        return calcularFitness(a, ganancias) > calcularFitness(b, ganancias);
    });

    poblacion.erase(poblacion.begin() + NUMIND, poblacion.end());

}
