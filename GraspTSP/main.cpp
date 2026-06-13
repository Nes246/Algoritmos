#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#define ITERACIONES 5000
#define alfa 0.7

using namespace std;

bool todosELegidos(vector<bool> visited) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == false) return false;
    }
    return true;
}

void llenarDistanciasCiudadElegida(vector<vector<int>>& distanciasElegida, vector<vector<int>> distancias, int ciudad, vector<bool> visited) {
    for (int i = 0; i < distancias[ciudad].size(); i++) {
        if (distancias[ciudad][i] != 0 and visited[i] == false) {
            distanciasElegida.push_back({i, distancias[ciudad][i]});
        }
        //if (distancias[ciudad][i] == 0 or ) distanciasElegida.pop_back();
    }
}

bool compara(vector<int> a, vector<int> b) {
    return a[1] < b[1];
}

int hallarInd(double rcl, const vector<vector<int>>& distanciasElegida) {
    int cont = 0;
    for (int i = 0; i < distanciasElegida.size(); i++) {
        if (distanciasElegida[i][1] <= rcl) cont++;
    }
    return cont;
}

int main() {
    srand(time(NULL));

    //Llenar Matriz Ciudades
    int cantCiudades = 6;
    vector<vector<int>> distancias =
        {
        {0,6,0,9,10,12},{6,0,5,8,0,11},{0,5,0,7,0,8},
        {9,8,7,0,7,6},{10,0,0,7,0,9},{12,11,8,6,9,0}
    };
    int mejorDistancia = INT_MAX;
    vector<int> mejorOrden;

    for (int i = 0; i < ITERACIONES; i++) {
        vector<bool> visited(cantCiudades, false);
        vector<int> orden;
        int distanciaRecorrida = 0;
        int ciudadElegida = 0;
        visited[0] = true;
        orden.push_back(0);

        //Constructor
        while (!todosELegidos(visited)) {
            vector<vector<int>> distanciasElegida;
            llenarDistanciasCiudadElegida(distanciasElegida, distancias, ciudadElegida, visited);
            if (distanciasElegida.size() == 0) break;
            sort(distanciasElegida.begin(), distanciasElegida.end(), compara);
            int beta = distanciasElegida[0][1];
            int tau = distanciasElegida[distanciasElegida.size() - 1][1];
            double rcl = beta + alfa*(tau-beta);
            int indRcl = hallarInd(rcl, distanciasElegida);
            int posA = rand() % indRcl;

            distanciaRecorrida += distanciasElegida[posA][1];
            ciudadElegida = distanciasElegida[posA][0];
            orden.push_back(ciudadElegida);
            visited[ciudadElegida] = true;
        }

        //Agrega el retorno a la ciudad inicial
        if (todosELegidos(visited) and distancias[ciudadElegida][0] != 0) {
            orden.push_back(0);
            distanciaRecorrida += distancias[ciudadElegida][0];

            //Hallar mejor
            if (mejorDistancia > distanciaRecorrida) {
                mejorDistancia = distanciaRecorrida;
                mejorOrden = orden;
            }
        }
    }

    //Imprimir Mejor
    for (int i = 0; i < mejorOrden.size(); i++) {
        cout << (char)(65+mejorOrden[i]) << " ";
    }
    cout << endl;
    cout << mejorDistancia << endl;


    return 0;
}

