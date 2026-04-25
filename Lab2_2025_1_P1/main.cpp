#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

//Usare dos arreglos, uno para los de franja blanca, y otro para los de franja roja

void hallarCantidad(int cantidad);

int main() {

    int cantidad = 3;

    hallarCantidad(cantidad);

    return 0;
}

void hallarCantidad(int cantidad) {
    int arr_rojo[cantidad + 1] = {};
    int arr_blanco[cantidad + 1] = {};

    arr_rojo[0] = 0;
    arr_rojo[1] = 1;
    arr_blanco[0] = 0;
    arr_blanco[1] = 1;

    for (int i = 2; i <= cantidad; i++) {
        arr_rojo[i] = arr_rojo[i - 2] + arr_rojo[i - 1];
        arr_blanco[i] = arr_blanco[i - 2] + arr_blanco[i - 1];
    }

    cout << "La cantidad total es: " << arr_rojo[cantidad] + arr_blanco[cantidad] << endl;

}