#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


int main() {

    vector<double> monedas = {0.1,0.2,0.5,1,2,5};
    double vuelto = 19.7;
    vector<double> usadas;

    sort(monedas.rbegin(), monedas.rend());

    double suma = 0, i = 0;

    while (true) {
        if (suma + monedas[i] <= vuelto) {
            suma += monedas[i];
            usadas.push_back(monedas[i]);
            if (suma == vuelto) break;
        } else {
            i++;
        }
    }

    cout << "Se usaran " << usadas.size() << " monedas para dar un vuelto de " << vuelto << endl;
    for (int j = 0; j < usadas.size(); j++) {
        cout << usadas[j] << " ";
    }

    return 0;
}
