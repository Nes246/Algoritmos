#include <iostream>
#include <iomanip>

using namespace std;

//El primero es numero de internos, segundo kilos que se lavaran
//y el tercero es el costo por kilo
int matriz[5][3] = {
    {6,0,5}, {7,0,6}, {4,0,8}, {5,0,5}, {2,0,9}
};

int kilos[5][7] = {
    {14,11,10,19,14,11,0}, {20,11,11,10,15,17,8},
    {15,16,15,16,0,0,0}, {11,4,19,12,10,0,0}, {18,12,0,0,0,0,0}
};


void BackTracking(int maximo, int acumulado, int i, int j, int &kilosTotal, int &mejorKilos);

int main() {

    for (int i = 0; i < 5; i++) {
        int kilosTotal = 0;
        int mejorKilos = 0;
        BackTracking(50, 0, i, 0, kilosTotal, mejorKilos);
        cout << kilosTotal << " " << kilosTotal * matriz[i][2] << endl;
        matriz[i][1] = kilosTotal;
    }

    return 0;
}

void BackTracking(int maximo, int acumulado, int i, int j, int &kilosTotal, int &mejorKilos) {
    if (acumulado > maximo) return;
    if (j == 7) {
        if (acumulado > mejorKilos)
            mejorKilos = acumulado;
        kilosTotal = mejorKilos;
        return;
    }

    BackTracking(maximo, acumulado, i, j + 1, kilosTotal, mejorKilos);

    if (acumulado + kilos[i][j] <= maximo) {
        BackTracking(maximo, acumulado + kilos[i][j], i, j + 1, kilosTotal, mejorKilos);
    }

}