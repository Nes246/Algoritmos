#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Tarea {
    int num;
    vector<int> tiempos;
    bool usado = false;
};

struct Maquina {
    int num;
    vector<Tarea> tareas;
    int tiempo;
};

bool compararTareas(Tarea t1, Tarea t2, int numMaquina) {
    return t1.tiempos[numMaquina - 1] < t2.tiempos[numMaquina - 1];
}

bool compararMaquina(Maquina a, Maquina b) {
    return a.tiempo < b.tiempo;
}

bool comparar2(Maquina a, Maquina b) {
    return a.num < b.num;
}

int main() {
    vector<vector<int>> tiemposTareas = {
        {6,4,3,2},{7,6,4,3},{4,3,2,2},{8,5,11,4},
        {5,3,2,3},{9,6,5,4},{7,4,3,3},{6,5,4,3},{8,5,4,4},{9,6,5,3}
    };

    vector<Tarea> tareas;

    for (int i = 0; i < tiemposTareas.size(); i++) {
        Tarea t;
        t.num = i + 1;
        t.tiempos = tiemposTareas[i];
        tareas.push_back(t);
    }

    vector<Maquina> maquinas;
    for (int i = 0; i < 4; i++) {
        Maquina m;
        m.num = i + 1;
        m.tiempo = 0;
        maquinas.push_back(m);
    }

    for (int i = 0; i < tareas.size(); i++) {
        sort(maquinas.begin(), maquinas.end(), compararMaquina);
        int numMaquina = maquinas[0].num;
        sort(tareas.begin(), tareas.end(), [numMaquina](Tarea t1, Tarea t2){return compararTareas(t1, t2, numMaquina);});
        int j = 0;
        while (true) {
            if (tareas[j].usado == false) {
                tareas[j].usado = true;
                maquinas[0].tareas.push_back(tareas[j]);
                maquinas[0].tiempo += tareas[j].tiempos[numMaquina - 1];
                break;
            }
            j++;
        }
    }

    int makespan = 0;
    sort(maquinas.begin(), maquinas.end(), comparar2);
    for (int i = 0; i < maquinas.size(); i++) {
        if (maquinas[i].tiempo > makespan) makespan = maquinas[i].tiempo;
        cout << maquinas[i].num << " " << maquinas[i].tiempo << endl;
        for (int j = 0; j < maquinas[i].tareas.size(); j++) {
            cout << " " << maquinas[i].tareas[j].num << " " << maquinas[i].tareas[j].tiempos[maquinas[i].num - 1] << endl; " ";
        }
    }

    cout << makespan << endl;

    return 0;
}