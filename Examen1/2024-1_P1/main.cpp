#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void backTracking(int matriz[5][5], int x, int y, int costo, int &mejorCosto);

int movimientosPosibles[4][2] = {{-1,0}, {1, 0}, {0, -1}, {0, 1}};
vector<vector<bool>> visitado(5, vector<bool>(5, false));


void imprimirMatriz(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {

    int matriz[5][5] = {
        {1,2,0,1,0},
        {3,2,3,1,1},
        {0,1,2,0,0},
        {3,1,1,2,3},
        {0,1,3,1,1}
    };


    int xIni = 0;
    int yIni = 0;
    int costo = matriz[xIni][yIni];
    int mejorCosto = INT_MAX;
    visitado[0][0] = true;

    backTracking(matriz,xIni,yIni,costo, mejorCosto);
        cout << mejorCosto << endl;

    return 0;
}

bool esPosible(int mov, int x, int y, int matriz[5][5]) {
    if (x < 0 || x >= 5 || y < 0 || y >= 5) return false;
    if (matriz[x][y] == 0) return false;
    if (visitado[x][y]) return false;
    return true;
}


void backTracking(int matriz[5][5], int x, int y, int costo, int &mejorCosto) {

    if (costo >= mejorCosto) return;

    if (x == y and x == 4) {
        if (costo < mejorCosto) mejorCosto = costo;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nuevoX = x + movimientosPosibles[i][0];
        int nuevoY = y + movimientosPosibles[i][1];
        if (esPosible(i, nuevoX, nuevoY, matriz)) {
            visitado[nuevoX][nuevoY] = true;
            backTracking(matriz, nuevoX, nuevoY, costo + matriz[nuevoX][nuevoY], mejorCosto);
            visitado[nuevoX][nuevoY] = false;
        }
    }
}