#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

struct Pais {
    int num;
    string nombre;
    int grado;
    int color = -1;
    vector<int> vecinos;
};

void llenarDatos(vector<Pais>& paises);
int buscarIndices(int num, vector<Pais> paises);
void ordenarColores(vector<int>& coloresProhibidos);

// void ordenarPaises(vector<Pais>& paises) {
//     for (int i = 0; i < paises.size()-1; i++) {
//         for (int j = 0; j < paises.size()-1-i; j++) {
//             if (paises[j].grado < paises[j+1].grado) {
//                 Pais p = paises[j];
//                 paises[j] = paises[j+1];
//                 paises[j+1] = p;
//             }
//         }
//     }
// }

void ordenarPaises(vector<Pais>& paises) {
    for (int i = 0; i < paises.size(); i++) {
        for (int j = i+1; j < paises.size(); j++) {
            if (paises[i].grado < paises[j].grado) {
                Pais p = paises[i];
                paises[i] = paises[j];
                paises[j] = p;
            }
        }
    }
}

int main() {

    vector<Pais> paises;
    llenarDatos(paises);

    ordenarPaises(paises); //Se ordena por grado de forma descendente
    int maximoColor = -1;

    //Pintar paises
    for (int i = 0; i < paises.size(); i++) {
        vector<int> coloresProhibidos;
        for (int j = 0; j < paises[i].grado; j++) {
            int num = buscarIndices(paises[i].vecinos[j], paises);
            if (num!=-1 and paises[num].color != -1) coloresProhibidos.push_back(paises[num].color);
            ordenarColores(coloresProhibidos);
        }
        int c = 0;
        while (coloresProhibidos.size() > c and coloresProhibidos[c] == c) c++;
        paises[i].color = c;
        if (maximoColor < c) maximoColor = c;
    }

    for (int i = 0; i <= maximoColor; i++) {
        cout << "Color " << i+1 << ": ";
        for (int j = 0; j < paises.size(); j++) {
            if (paises[j].color == i) cout << paises[j].nombre << " ";
        }
        cout << endl;
    }

    return 0;
}


void llenarDatos(vector<Pais>& paises) {
    vector<vector<int>> matriz = {
        {4,2,8,3,11},          // 1 Argentina
        {9,3,8,1,4},           // 2 Bolivia
        {11,1,8,2,9,5,12,7,10}, // 3 Brasil
        {9,2,1},               // 4 Chile
        {12,3,9,6},            // 5 Colombia
        {5,9},                 // 6 Ecuador
        {12,3,10},             // 7 Guyana
        {2,3,1},               // 8 Paraguay
        {6,5,3,2,4},           // 9 Perú
        {7,3},                 // 10 Surinam
        {3,1},                 // 11 Uruguay
        {5,3,7}                // 12 Venezuela
    };
    vector<string>nombres = {"Argentina",
    "Bolivia",
    "Brasil",
    "Chile",
    "Colombia",
    "Ecuador",
    "Guyana",
    "Paraguay",
    "Peru",
    "Surinam",
    "Uruguay",
    "Venezuela"};

    for (int i = 0; i < nombres.size(); i++) {
        Pais p;
        p.nombre = nombres[i];
        p.num = i + 1;
        p.vecinos = matriz[i];
        p.grado = matriz[i].size();
        paises.push_back(p);
    }
}

int buscarIndices(int num, vector<Pais> paises) {
    for (int i = 0; i < paises.size(); i++) {
        if (paises[i].num == num) return i;
    }
    return -1;
}

void ordenarColores(vector<int>& coloresProhibidos) {
    if (coloresProhibidos.size() == 0) return;
    for (int i = 0; i < coloresProhibidos.size()-1; i++) {
        for (int j = 0; j < coloresProhibidos.size()-1-i; j++) {
            if (coloresProhibidos[j] > coloresProhibidos[j+1]) {
                int aux = coloresProhibidos[j];
                coloresProhibidos[j] = coloresProhibidos[j+1];
                coloresProhibidos[j+1] = aux;
            }
        }
    }
}