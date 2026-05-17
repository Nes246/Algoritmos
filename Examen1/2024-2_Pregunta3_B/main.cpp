#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Tarea {
    char letra;
    int horaMax;
    int ganancia;
    bool usado;
};

bool compara(Tarea t1, Tarea t2) {
    return t1.ganancia > t2.ganancia;
}

bool esValido(vector<bool> horas, Tarea t, int &num) {
    int horaMax = t.horaMax;

    for (int i = 0; i < horaMax; i++) {
        if (horas[i] == false) {
            num = i;
            return true;
        }
    }
    return false;

}

int main() {

    // vector<vector<int>> matriz = {
    //     {2,100},{1,19},{2,27},{1,25},{3,15}
    // };

    vector<vector<int>> matriz = {
        {4,20},{1,10},{2,40},{2,30}
    };

    int ultimaHora = 0;
    vector<Tarea> tareas;
    for (int i = 0; i < matriz.size(); i++) {
        Tarea t;
        t.letra = 65+i; //65 = A
        t.horaMax = matriz[i][0];
        t.ganancia = matriz[i][1];
        t.usado = false;
        if (matriz[i][0] > ultimaHora) ultimaHora = matriz[i][0];
        tareas.push_back(t);
    }

    int ganancia = 0;
    vector<bool> horas(ultimaHora, false);

    sort(tareas.begin(), tareas.end(), compara);
    for (int i = 0; i < tareas.size(); i++) {
        int num = -1;
        if (esValido(horas, tareas[i], num)) {
            horas[num] = true;
            ganancia += tareas[i].ganancia;
            tareas[i].usado = true;
        }
    }

    for (int i = 0; i < tareas.size(); i++) {
        if (tareas[i].usado) {
            cout << tareas[i].letra << endl;
        }
    }
    cout << ganancia << endl;

    return 0;
}
