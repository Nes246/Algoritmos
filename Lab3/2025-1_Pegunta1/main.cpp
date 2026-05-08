#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

struct Velocidad {
    int num;
    int velocidad;
};

void llenarDatos(vector<int>num, vector<Velocidad>& tablas);

void ordenar(vector<Velocidad>& tablas) {
    for (int i = 0; i < tablas.size()-1; i++) {
        for (int j = 0; j < tablas.size()-1-i; j++) {
            if (tablas[j].velocidad < tablas[j+1].velocidad) {
                Velocidad temp = tablas[j];
                tablas[j] = tablas[j+1];
                tablas[j+1] = temp;
            }
        }
    }
}

int main() {

    //Llenar Datos
    vector<Velocidad> tablas;
    vector<Velocidad> discos;

    vector<int> num = {150,100,180,50,120,10};
    llenarDatos(num, tablas);
    vector<int> num2 = {250,200,200,100};
    llenarDatos(num2, discos);

    ordenar(tablas);
    ordenar(discos);
    vector<int> discosTablas(tablas.size(), -1);

    for (int i = 0; i < tablas.size(); i++) {
        ordenar(discos);
        for (int j = 0; j < discos.size(); j++) {
            if (discos[j].velocidad >= tablas[i].velocidad) {
                discosTablas[tablas[i].num - 1] = discos[j].num;
                discos[j].velocidad -= tablas[i].velocidad;
                break;
            }
        }
    }

    for (int i = 0; i < discos.size(); i++) {
        cout << "Disco " << i + 1 << ": ";
        for (int j = 0; j < discosTablas.size(); j++) {
            if (discosTablas[j] == discos[i].num) cout << j + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}

void llenarDatos(vector<int>num, vector<Velocidad>& tablas) {
    for (int i = 0; i < num.size(); i++) {
        Velocidad v;
        v.num = i+1;
        v.velocidad = num[i];
        tablas.push_back(v);
    }
}

