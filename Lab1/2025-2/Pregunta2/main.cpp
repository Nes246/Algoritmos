#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


void BackTracking(int pos, int sumaBuscada, int sumaActual, int numero, bool usados[]);

int main() {
    int suma = 8;
    bool usados[10] = {false};

    BackTracking(0, suma, 0, 0, usados);

    return 0;
}

void BackTracking(int pos, int sumaBuscada, int sumaActual, int numero, bool usados[]) {
    if (sumaActual > sumaBuscada) return;

    if (pos == 3) {
        if (sumaActual == sumaBuscada) {
            cout << numero << endl;
        }
        return;
    }

    for (int d = 1; d <= 9; d++) {
        if (!usados[d]) {
            usados[d] = true;

            BackTracking(pos + 1, sumaBuscada, sumaActual + d, numero * 10 + d, usados);

            usados[d] = false;
        }
    }
}