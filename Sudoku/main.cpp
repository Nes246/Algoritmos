#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

bool esValido(const vector<vector<int>> &sudoku, int num, int fila, int columna, int cantFilas) {
    if (sudoku[fila][columna] != 0) return false;
    //Verificar columna
    for (int i = 0; i < cantFilas; i++) {
        if (num == sudoku[i][columna]) return false;
    }

    //Verificar fila
    for (int i = 0; i < cantFilas; i++) {
        if (num == sudoku[fila][i]) return false;
    }

    //Revisar region
    if (cantFilas == 9) {
        int inicioX = fila - (fila%3);
        int inicioY = columna - (columna%3);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (sudoku[inicioX + i][inicioY + j] == num) return false;
            }
        }
    }

    return true;
}

bool llenarSudoku(int filas, vector<vector<int>> &sudoku, int pos) {
    if (pos == filas*filas) return true;

    for (int j=0; j<filas; j++) {
        for (int k=0; k<filas; k++) {
            if (sudoku[j][k] == 0) {
                for (int num = 1; num <= filas; num++) {
                    if (esValido(sudoku, num, j, k, filas)) {
                        sudoku[j][k] = num;
                        if (llenarSudoku(filas, sudoku, pos+1)) return true;
                        sudoku[j][k] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main() {

    int filas = 9;
    //vector<vector<int>> sudoku(filas, vector<int>(filas, 0));
    //sudoku[0][0] = 1;
    vector<vector<int>> sudoku = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    if (llenarSudoku(filas,sudoku, 0)) {
        for(int i=0;i<filas;i++) {
            for(int j=0;j<filas;j++) {
                cout<< sudoku[i][j]<<" ";
                if (j%3 == 2) cout << "| ";
            }
            cout<<endl;
            if (i%3 == 2) cout << "----------------------" << endl;
        }
    }

    return 0;
}
