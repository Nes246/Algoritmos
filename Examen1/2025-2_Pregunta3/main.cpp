#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Tarea {
    int num;
    int tiempo1;
    int tiempo2;
    int tiempo3;
    int tiempo4;
    double promedio;
};

struct Maquina {
    int num;
    vector<Tarea> tareas;
    int tiempo;
};

bool compararTareas(Tarea t1, Tarea t2) {
    return t1.promedio > t2.promedio;
}

bool compararMaquina(Maquina a, Maquina b) {
    return a.tiempo < b.tiempo;
}

bool comparar2(Maquina a, Maquina b) {
    return a.num < b.num;
}

int main() {
    vector<vector<int>> matriz = {
        {6,4,3,2},{7,6,4,3},{4,3,2,2},{8,5,11,4},
        {5,3,2,3},{9,6,5,4},{7,4,3,3},{6,5,4,3},{8,5,4,4},{9,6,5,3}
    };

    vector<Tarea> tareas;

    for (int i = 0; i < matriz.size(); i++) {
        Tarea t;
        t.num = i + 1;
        t.tiempo1 = matriz[i][0];
        t.tiempo2 = matriz[i][1];
        t.tiempo3 = matriz[i][2];
        t.tiempo4 = matriz[i][3];
        t.promedio = (double)(t.tiempo1 + t.tiempo2 + t.tiempo3 + t.tiempo4) / 4;
        tareas.push_back(t);
    }

    vector<Maquina> maquinas;
    for (int i = 0; i < 4; i++) {
        Maquina m;
        m.num = i + 1;
        m.tiempo = 0;
        maquinas.push_back(m);
    }

    sort(tareas.begin(), tareas.end(), compararTareas);
    for (int i = 0; i < tareas.size(); i++) {
        sort(maquinas.begin(), maquinas.end(), compararMaquina);
        maquinas[0].tareas.push_back(tareas[i]);
        int tiempo;
        if (maquinas[0].num == 1) tiempo = tareas[i].tiempo1;
        else if (maquinas[0].num == 2) tiempo = tareas[i].tiempo2;
        else if (maquinas[0].num == 3) tiempo = tareas[i].tiempo3;
        else tiempo = tareas[i].tiempo4;
        maquinas[0].tiempo += tiempo;
        // cout << tareas[i].num << " " << tareas[i].promedio << endl;
    }

    sort(maquinas.begin(), maquinas.end(), comparar2);
    for (int i = 0; i < maquinas.size(); i++) {
        cout << maquinas[i].num << " " << maquinas[i].tiempo << endl;
        for (int j = 0; j < maquinas[i].tareas.size(); j++) {
            cout << " " << maquinas[i].tareas[j].num << " ";
            if (i == 0) cout << maquinas[i].tareas[j].tiempo1 << endl;
            else if (i == 1) cout << maquinas[i].tareas[j].tiempo2 << endl;
            else if (i == 2) cout << maquinas[i].tareas[j].tiempo3 << endl;
            else cout << maquinas[i].tareas[j].tiempo4 << endl;
        }
    }


    return 0;
}