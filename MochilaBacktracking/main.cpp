#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

int objetos[4][2] = {{40,30}, {60,15}, {30,10}, {90,20}}; //El primero es el peso y el segundo el valor
void backtracking(int i, int pesoActual, int valorActual, int max, int &acumulado);

int main() {

    int maximo, acumulado = 0;

    cout<<"Ingresar peso maximo: ";
    cin>>maximo;

    backtracking(0, 0, 0, maximo, acumulado);

    cout<<"Acumulado: "<< acumulado<<endl;

    return 0;
}

void backtracking(int i, int pesoActual, int valorActual, int max, int &acumulado) {

    if (pesoActual > max) return;
    if (i == 4) {
        if (valorActual > acumulado) {
            acumulado = valorActual;
        }
        return;
    }
    backtracking(i+1, pesoActual, valorActual, max, acumulado);

    if (pesoActual + objetos[i][0] <= max) {
        backtracking(i+1, pesoActual + objetos[i][0], valorActual + objetos[i][1], max, acumulado);
    }

}
