#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void hallarCantidad(int cantidad, vector <int> Monedas);


int main() {

    int cantidad = 19;
    vector<int> monedas = {2 , 5 , 10};
    sort(monedas.rbegin(), monedas.rend());

    hallarCantidad(cantidad, monedas);

    return 0;
}

void hallarCantidad(int cantidad,vector <int> Monedas){

    int suma = 0;
    int num = 0;
    vector<int> cambio;
    while (true) {
        if (suma == cantidad) break;
        if (suma + Monedas[num] <= cantidad) {
            suma += Monedas[num];
            cambio.push_back(Monedas[num]);
        }
        else {
            num++;
        }
    }

    for (int i = 0; i < cambio.size(); i++) {
        cout << cambio[i] << " ";
    }

}