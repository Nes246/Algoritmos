#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

void backTracking(int nApertura, int nCierre, int n, vector<int> orden, int pos) {

    if (nApertura == nCierre and nApertura == n) {
        for (int i = 0; i < n*2; i++) {
            if (orden[i] == 0) cout << "(";
            else cout << ")";
        }
        cout << endl;
        return;
    }


    if (nApertura < n) {
        orden[pos] = 0;
        backTracking(nApertura + 1, nCierre, n, orden, pos + 1);
    }

    if (nCierre < nApertura) {
        orden[pos] = 1;
        backTracking(nApertura, nCierre + 1, n, orden, pos + 1);
    }

}


int main() {

    int n = 4;
    vector<int> orden(n*2, -1);

    orden[0] = 0;
    int pos = 1;
    backTracking(1, 0, n, orden, pos);

    return 0;
}
