#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void BackTracking(int numero, int suma);

int main() {

    int suma = 8;
    int numero = 111;

    BackTracking(numero, suma);

    return 0;
}

void obtenerNumeros(int numero, int& a, int& b, int& c) {
    a = numero/100;
    b = (numero - a*100)/10;
    c = (numero - a*100) - b*10;
}

void BackTracking(int numero, int suma) {
    if (numero > 999) return;
    int a, b, c;
    obtenerNumeros(numero, a, b, c);

    if ((a != b and a != c and b != c) and (a + b + c == suma) and (a!=0 and b!=0 and c!=0))
        cout << numero << endl;

    BackTracking(numero + 1, suma);

}
