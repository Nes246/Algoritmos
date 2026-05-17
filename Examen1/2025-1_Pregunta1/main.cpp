#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

bool backTracking(vector<vector<int>> regiones,vector<vector<int>> &matriz, int i, int filas, int cantRegiones);

bool esValido(vector<vector<int>> sudoku, int num, int fila, int columna, int cantRegiones, vector<vector<int>> regiones, int &numRegion) {
    if (sudoku[fila][columna] != 0) return false;
    //Verificar columna
    for (int i = 0; i < 3; i++) {
        if (num == sudoku[i][columna]) return false;
    }

    //Verificar fila
    for (int i = 0; i < 3; i++) {
        if (num == sudoku[fila][i]) return false;
    }

    bool encontrado = false;
    //Verificar suma region
    for (int i = 0; i < cantRegiones; i++) {
        int cantCeldas = regiones[i][1];
        for (int j = 0; j < cantCeldas; j++) {
            if (columna == regiones[i][3 + 2*j] and fila == regiones[i][2 + 2*j]) {
                numRegion = i;
                if (regiones[i][2 + 2*cantCeldas] + num > regiones[i][0]) return false;
                encontrado = true;
                break;
            }
        }
        if (encontrado) break;
    }

    //Verificar numeros region
    int cantCeldas = regiones[numRegion][1];
    for (int j = 0; j < cantCeldas; j++) {
        int x = regiones[numRegion][2 + 2*j];
        int y = regiones[numRegion][3 + 2*j];
        if (sudoku[x][y] == num) return false;
    }

    if (regiones[numRegion][3 + 2*cantCeldas] == cantCeldas
        and regiones[numRegion][2 + 2*cantCeldas] != regiones[numRegion][0]) return false;

    return true;
}

int main() {

    int filas, cantRegiones;
    cin >> filas >> cantRegiones;
    vector<vector<int>> regiones;
    vector<vector<int>> matriz(filas, vector<int>(filas, 0));

    for (int i = 0; i < cantRegiones; i++) {
        vector<int> prueba;
        int suma, cantCeldas;
        cin >> suma >> cantCeldas;
        prueba.push_back(suma);
        prueba.push_back(cantCeldas);
        for (int j = 0; j < cantCeldas; j++) {
            int x, y;
            cin >> x >> y;
            prueba.push_back(x);
            prueba.push_back(y);
            if (cantCeldas == 1) matriz[x][y] = suma;
        }
        prueba.push_back(0); //sumaActual
        prueba.push_back(0); //cantNumeros
        regiones.push_back(prueba);
    }


    //Imprimir Matriz
    if (backTracking(regiones, matriz, 0, filas, cantRegiones)) {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < filas; j++) {
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No se pudo encontrar solucion" << endl;
    }

    //regiones[i][1] == 1
    //x = regiones[i][2] y = regiones[i][3]
    //matriz[x][y] = regiones[i][0]


    return 0;
}

bool backTracking(vector<vector<int>> regiones, vector<vector<int>> &matriz, int i, int filas, int cantRegiones) {
    if (i == filas*filas) return (true);

    int numRegion = -1;
    for (int j = 0; j < filas; j++) {
        for (int k = 0; k < filas; k++) {
            if (matriz[j][k] == 0) {
                for (int num = 1; num <= filas; num++) {
                    if (esValido(matriz, num, j, k, cantRegiones, regiones, numRegion)) {
                        regiones[numRegion][2 + 2*regiones[numRegion][1]] += num;
                        regiones[numRegion][3 + 2*regiones[numRegion][1]]++;
                        matriz[j][k] = num;
                        if (backTracking(regiones, matriz, i + 1, filas, cantRegiones)) return true;
                        matriz[j][k] = 0;
                        regiones[numRegion][2 + 2*regiones[numRegion][1]] -= num;
                        regiones[numRegion][3 + 2*regiones[numRegion][1]]--;
                    }
                }
                return false;
            }
        }
    }
    return true;
}