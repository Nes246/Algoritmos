#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Proyecto {
    int costo;
    int beneficio;
    double ratio;
};

bool comparar(Proyecto p1, Proyecto p2) {
    return p1.ratio > p2.ratio;
}

int main() {

    vector<int> costo = {2, 3, 4, 5, 9};
    vector<int> beneficio = {3, 4, 5, 8, 10};
    vector<Proyecto> proyectos;
    vector<Proyecto> incluido;
    int presupuesto = 15;

    for (int i = 0; i < costo.size(); i++) {
        Proyecto p;
        p.costo = costo[i];
        p.beneficio = beneficio[i];
        p.ratio = (double)beneficio[i]/costo[i];
        proyectos.push_back(p);
    }

    sort(proyectos.begin(), proyectos.end(), comparar);

    for (int i = 0; i < costo.size(); i++) {
        Proyecto o = proyectos[i];
        cout << o.ratio << " " << o.beneficio << " " << o.costo << endl;
    }

    int suma = 0;
    for (int i = 0; i < costo.size(); i++) {
        Proyecto o = proyectos[i];
        if (suma + o.costo <= presupuesto) {
            suma += o.costo;
            incluido.push_back(o);
        }
    }

    cout << "//" << endl;
    for (int i = 0; i < incluido.size(); i++) {
        Proyecto o = incluido[i];
        cout << o.ratio << " " << o.beneficio << " " << o.costo << endl;
    }


    return 0;
}
