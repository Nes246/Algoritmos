#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Color {
    int num;
    vector<int> adyacencias;
    int grado;
    int color;
};

void llenarDatos(vector<Color>& colores, int n);

bool compararColor(Color c1, Color c2) {
    return c1.grado > c2.grado;
}

int buscarIndice(int num, vector<Color> colores);

int main() {

    int n = 6, maximoColor = -1;
    vector<Color>colores;

    llenarDatos(colores, n);

    sort(colores.begin(), colores.end(), compararColor);

    for (int i = 0; i < colores.size(); i++) {
        Color color = colores[i];
        vector<int> coloresProhibidos;
        for (int j = 0; j < color.adyacencias.size(); j++) {
            int num = buscarIndice(color.adyacencias[j], colores);
            if (colores[num].color != -1) coloresProhibidos.push_back(colores[num].color);
            sort(coloresProhibidos.begin(), coloresProhibidos.end());
        }
        int c = 0;
        while (coloresProhibidos.size()>c and coloresProhibidos[c] == c) c++;
        colores[i].color = c;
        if (c > maximoColor) maximoColor = c;
    }

    cout << maximoColor +1 << endl;

    for (int i = 0; i < colores.size(); i++) {
        cout << colores[i].num << " ";
        cout << colores[i].grado << " ";
        cout << colores[i].color << endl;
    }


    return 0;
}


void llenarDatos(vector<Color>& colores, int n) {
    vector<vector<int>> adyacencias = {
        {2,3,4},
        {1,3,5},
        {1,2,4,6},
        {1,3,6},
        {2,6},
        {3,4,5}
    };

    for (int i = 0; i < n; i++) {
        Color c;
        c.num = i + 1;
        c.adyacencias = adyacencias[i];
        c.grado = adyacencias[i].size();
        c.color = -1;
        colores.push_back(c);
    }
}

int buscarIndice(int num, vector<Color> colores) {
    int i = 0;
    while (true) {
        if (colores[i].num == num) return i;
        i++;
    }
}
