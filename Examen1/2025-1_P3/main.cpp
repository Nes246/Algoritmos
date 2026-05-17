#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Orden {
    int num;
    int cant;
    double tiempo;
};

struct Linea {
    int num;
    double tiempo;
    vector<Orden> ordenes;
};

bool comparar(Linea l1, Linea l2) {
    if (l1.tiempo == l2.tiempo) return l1.num < l2.num;
    return l1.tiempo < l2.tiempo;
}

bool comparar2(Linea l1, Linea l2) {
    return l1.num < l2.num;
}


int main() {

    vector<Linea> lineas;
    vector<Orden> ordenes;

    //Llenar lineas vacias
    int cantLineas = 5;
    for (int i = 0; i < cantLineas; i++) {
        Linea l;
        l.num = i + 1;
        l.tiempo = 0;
        lineas.push_back(l);
    }

    //Llenar ordenes
    vector<int> cantidades = {
        103, 58,88,126,195,90,54,195,124,113,193,55,97,97,169,50,167,74,79,109
    };

    for (int i = 0; i < cantidades.size(); i++) {
        Orden o;
        o.num = i + 1;
        o.cant = cantidades[i];
        o.tiempo = o.cant * (2+1+1.5+1.5);
        ordenes.push_back(o);
    }

    for (int i = 0; i < ordenes.size(); i++) {
        sort(lineas.begin(), lineas.end(), comparar);
        lineas[0].ordenes.push_back(ordenes[i]);
        lineas[0].tiempo += ordenes[i].tiempo;
    }

    int makespan = 0;
    sort(lineas.begin(), lineas.end(), comparar2);
    for (int i = 0; i < lineas.size(); i++) {
        if (lineas[i].tiempo > makespan) makespan = lineas[i].tiempo;
        cout << "Linea " << i + 1 << " (" << lineas[i].tiempo << ") :" << endl;
        for (int j = 0; j < lineas[i].ordenes.size(); j++) {
            cout << " (" << lineas[i].ordenes[j].num << " " << lineas[i].ordenes[j].tiempo << ") " ;
        }
        cout << endl;
    }

    cout << makespan << endl;


    return 0;
}
