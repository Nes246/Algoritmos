#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

int matriz[8][8]{};
int movimientosPosibles[8][2] = {
    {2,1}, {1,2},{-1,2}, {-2,1}, {-2,-1},{-1,-2},{1,-2},{2,-1}
};

void imprimirMatriz();
bool recorridoCaballo(int x, int y, int numMov);

int main() {

    matriz[4][5] = 1;
    if ((recorridoCaballo(4, 5, 2)) == false)
        cout << "No se encontro solucion";
    else
        imprimirMatriz();

    return 0;
}

void imprimirMatriz() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << " " << setw(2) << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

bool recorridoCaballo(int x, int y, int numMov) {

    if (numMov == 64) return true;
    else {
        for (int i = 0; i < 8; i++) {
            int nuevoX = x + movimientosPosibles[i][0];
            int nuevoY = y + movimientosPosibles[i][1];
            if ((nuevoX <= 7 and nuevoY <= 7) and (nuevoX >= 0 and nuevoY >= 0) and matriz[nuevoX][nuevoY] == 0) {
                matriz[nuevoX][nuevoY] = numMov;
                if ((recorridoCaballo(nuevoX, nuevoY, numMov + 1)) == true) return true;
                else matriz[nuevoX][nuevoY] = 0;
            }
        }
    }
    return false;
}