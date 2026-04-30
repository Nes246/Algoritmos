#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;



int main() {

    vector <int> longitud(20, 10);
    vector <int> requerimientos = {6,6,6,6,6,6,6,5,5,5,3,3,3,3,2,2,2,2,2,2,2,1,1,1};
    int n = requerimientos.size();
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (longitud[j]==0 or longitud[j] < requerimientos[i]) j = j+1;
        longitud[j] = longitud[j] - requerimientos[i];
    }
    int merma = 0;
    int k = 0;

    while (longitud.back() == 10) {
        longitud.pop_back();
    }

    for (int i = 0; i < longitud.size(); i++) {
        if (longitud[i] > 0) merma += longitud[i];
    }

    for (int i = 0; i < longitud.size(); i++) cout << longitud[i] << " ";
    cout << merma;

    return 0;
}