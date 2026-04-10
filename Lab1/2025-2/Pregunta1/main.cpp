#include <iostream>
#include <iomanip>

using namespace std;

void imprimirMatriz(int matriz[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << " " << setw(2) << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

bool BackTracking(int matriz[8][8], int movimientos[8][2], int x, int y, int NumMov);
bool esMagico(int matriz[8][8]);

int main() {

    int tablero[8][8]{};
    int movimientos[8][2] = {{-1,-1}, {-1,0},{-1,1}, {0,-1},{0,1},{1,-1},{1,0}, {1,1}};

    int x =3, y=4;

    tablero[x][y] = 1;

    if (BackTracking(tablero, movimientos, x, y, 1) == true) {
        imprimirMatriz(tablero);
    }
    if (esMagico(tablero) == true) {
        cout << "Es un cuadrado magico" << endl;
    }
    else
        cout << "No es un cuadrado magico" << endl;

    return 0;
}

bool BackTracking(int matriz[8][8], int movimientos[8][2], int x, int y, int NumMov) {
    if (NumMov == 64) return true;
    else {
        for (int i = 0; i < 8; i++) {
            int nuevoX = x + movimientos[i][0];
            int nuevoY = y + movimientos[i][1];
            if (nuevoX <= 7 and nuevoX >= 0 and nuevoY <= 7 and nuevoY >=0 and matriz[nuevoX][nuevoY] == 0) {
                matriz[nuevoX][nuevoY] = NumMov + 1;
                if (BackTracking(matriz, movimientos, nuevoX, nuevoY, NumMov + 1) == true) return true;
                else matriz[nuevoX][nuevoY] = 0;
            }
        }
    }
    return false;
}

bool esMagico(int matriz[8][8]) {
    int constante = 260;
    int contador;

    //Filas
    for (int i = 0; i < 8; i++) {
        contador = 0;
        for (int j = 0; j < 8; j++) {
            contador += matriz[i][j];
        }
        if (contador != constante) return false;
    }

    //Columnas
    for (int i = 0; i < 8; i++) {
        contador = 0;
        for (int j = 0; j < 8; j++) {
            contador += matriz[j][i];
        }
        if (contador != constante) return false;
    }

    //Diagonal
    for (int i = 0; i < 8; i++) {
        contador = 0;
        contador += matriz[i][i];
        if (contador != constante) return false;
    }

    //Diagonal2
    for (int i = 0; i < 8; i++) {
        int j = 7;
        contador = 0;
        contador += matriz[i][j];
        j--;
        if (contador != constante) return false;
    }

    return true;
}
