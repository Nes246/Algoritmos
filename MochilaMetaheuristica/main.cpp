#include <iostream>
#include <iomanip>
#include <climits>
#include <ctime>
#include <vector>
#include <algorithm>
#define ITERACIONES 1000
#define alfa 0.7

using namespace std;

struct Objeto {
    int num;
    int peso;
    int valor;
    double ratio;
};

void llenarObjetos(vector<Objeto>& matrizObjetos);

bool compara(Objeto a, Objeto b) {
    return a.ratio < b.ratio;
}

int hallarIndice(double rcl, vector<Objeto> objetos) {
    int cont = 0;
    for (int i = 0; i < objetos.size(); i++) {
        if (objetos[i].ratio <= rcl) cont++;
    }
    return cont;
}

int main() {

    srand(time(NULL));
    vector<Objeto> matrizObjetos;
    llenarObjetos(matrizObjetos);
    sort(matrizObjetos.begin(), matrizObjetos.end(), compara);
    vector<Objeto> mejorSol;
    int mejorValor = INT_MIN;
    vector<Objeto> objetos;

    for (int i = 0; i < ITERACIONES; i++) {
        vector<Objeto> solActual;
        objetos = matrizObjetos;
        int valorActual = 0;
        int CapacidadPeso = 10;

        //Constructor
        while (!objetos.empty()) {
            double beta = objetos[0].ratio;
            double tau = objetos[objetos.size() - 1].ratio;
            double rcl = beta + (alfa*(tau-beta));
            int indRcl = hallarIndice(rcl, objetos);
            int pos = rand() % indRcl;
            if (objetos[pos].peso <= CapacidadPeso) {
                solActual.push_back(objetos[pos]);
                CapacidadPeso -= objetos[pos].peso;
                valorActual += objetos[pos].valor;
                if (CapacidadPeso == 0) break;
            }
            objetos.erase(objetos.begin() + pos);
        }

        //Ver si es mejor opcion
        if (valorActual > mejorValor) {
            mejorValor = valorActual;
            mejorSol = solActual;
        }
    }

    //Imprimir mejor solucion
    for (int i = 0; i < mejorSol.size(); i++) {
        cout << mejorSol[i].num << " " << mejorSol[i].peso << " " << mejorSol[i].valor << endl;
    }
    cout << mejorValor << endl;


    return 0;
}

void llenarObjetos(vector<Objeto>& matrizObjetos) {
    matrizObjetos.push_back({1, 2, 12});
    matrizObjetos.push_back({2, 1, 10});
    matrizObjetos.push_back({3, 3, 20});
    matrizObjetos.push_back({4, 2, 15});
    matrizObjetos.push_back({5, 5, 30});
    matrizObjetos.push_back({6, 4, 28});
    matrizObjetos.push_back({7, 6, 35});
    matrizObjetos.push_back({8, 3, 18});

    for (int i = 0; i < matrizObjetos.size(); i++) {
        matrizObjetos[i].ratio = (double)matrizObjetos[i].valor/matrizObjetos[i].peso;
    }

}