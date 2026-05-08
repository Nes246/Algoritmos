#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

struct Orden {
    int num;
    int tipo; //Lavar 0, Secar 1
    int kilos;
    int tiempo;
};

struct Lavadora {
    int tiempo = 0;
    vector<Orden> ordenes;
};

void ordenarOrdenes(vector<Orden>& ordenes) {
    for (int i = 0; i < ordenes.size()-1; i++) {
        for (int j = 0; j < ordenes.size()-1-i; j++) {
            if (ordenes[j].tiempo < ordenes[j+1].tiempo) {
                Orden aux = ordenes[j];
                ordenes[j] = ordenes[j+1];
                ordenes[j+1] = aux;
            }
        }
    }
}

void ordenarLavadoras(Lavadora lavadoras[5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = i+1; j < 5; j++) {
            if (lavadoras[i].tiempo > lavadoras[j].tiempo) {
                Lavadora aux = lavadoras[i];
                lavadoras[i] = lavadoras[j];
                lavadoras[j] = aux;
            }
        }
    }
}

int main() {

    //Llenar Datos
    vector<vector<int>> tipoKilos = {{0,10},{0,10},{1,8},
        {0,15},{1,9},{1,11},{0,12},{1,15},{0,6},
        {1,10},{0,8},{1,15},{0,11},{0,7},{0,7},
        {1,8},{1,9},{0,11},{1,12},{0,15}};

    vector<Orden> ordenes;
    for (int i = 0; i < tipoKilos.size(); i++) {
        Orden o;
        o.num = i + 1;
        o.tipo = tipoKilos[i][0];
        o.kilos = tipoKilos[i][1];
        //Calcular Tiempo
        if (tipoKilos[i][0] == 1) o.tiempo = o.kilos*2;
        else o.tiempo = o.kilos*4;
        ordenes.push_back(o);
    }

    Lavadora lavadoras[5];

    //ordenarOrdenes(ordenes); //Con esto queda mejor pero no es lo que pide el ejercicio

    for (int i = 0; i < ordenes.size(); i++) {
        ordenarLavadoras(lavadoras);
        lavadoras[0].ordenes.push_back(ordenes[i]);
        lavadoras[0].tiempo += ordenes[i].tiempo;
    }

    for (int i = 0; i < 5; i++) {
        cout << "Lavadora " << i +1 << ": " << lavadoras[i].tiempo << " min" << endl;
        for (int j = 0; j < lavadoras[i].ordenes.size(); j++) {
            cout << "  " << lavadoras[i].ordenes[j].num << " " << lavadoras[i].ordenes[j].tiempo << endl;
        }
        cout << endl;
    }

    return 0;
}
