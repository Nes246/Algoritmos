#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Articulo {
    int peso;
    int valor;
    double ratio;
};

bool comparar(Articulo a, Articulo b) {
    return a.ratio > b.ratio;
}

int main() {

    vector<int> peso = {2, 1, 3, 2, 5, 7, 4, 6};
    vector<int> valor = {12, 10, 20, 15, 30, 35, 25, 40};
    int W = 15;
    vector<Articulo> articulos;
    vector<Articulo> usados;

    for (int i = 0; i < peso.size(); i++) {
        Articulo articulo;
        articulo.peso = peso[i];
        articulo.valor = valor[i];
        articulo.ratio = (double)valor[i]/ peso[i];
        articulos.push_back(articulo);
    }

    sort(articulos.begin(), articulos.end(), comparar);

    for (int i = 0; i < articulos.size(); i++) {
        Articulo articulo = articulos[i];
        cout << articulo.peso << " " << articulo.valor << " " << articulo.ratio << endl;
    }

    int suma = 0;
    for (int i = 0; i < articulos.size(); i++) {
        Articulo articulo = articulos[i];
        if (suma + articulo.peso <= W) {
            suma += articulo.peso;
            usados.push_back(articulo);
        }
    }

    cout << "//" << endl;
    for (int i = 0; i < usados.size(); i++) {
        Articulo articulo = usados[i];
        cout << articulo.peso << " " << articulo.valor << endl;
    }


    return 0;
}