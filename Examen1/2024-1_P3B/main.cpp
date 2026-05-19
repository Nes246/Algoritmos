#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Telar {
    int num;
    int velocidad;
    int tiempo;
    vector <int> tareas;
};

bool compara(Telar a, Telar b) {
    if (a.tiempo == b.tiempo) return a.velocidad < b.velocidad;
    return a.tiempo < b.tiempo;
}

int main() {

    vector<int> telares = {5,4,6};
    vector<int> telas = {10,7,9,12,6,8};

    vector<Telar> telares2;

    for(int i = 0; i < telares.size(); i++) {
        Telar t;
        t.num = i + 1;
        t.velocidad = telares[i];
        t.tiempo = 0;
        telares2.push_back(t);
    }

    for(int i = 0; i < telas.size(); i++) {
        vector <int> aux(telares2.size(), 0);
        int menor = INT_MAX, indice = -1;
        for(int j = 0; j < telares2.size(); j++) {
            aux[j] = telares2[j].tiempo + telares2[j].velocidad*telas[i];
            if (aux[j] < menor) {
                menor = aux[j];
                indice = j;
            }
        }
        telares2[indice].tiempo += telares2[indice].velocidad*telas[i];
        telares2[indice].tareas.push_back(telas[i]);
    }

    //Esta es mejor pero la otra es igual al ejemplo
    // sort(telas.rbegin(), telas.rend());
    // for(int i = 0; i < telas.size(); i++) {
    //     sort(telares2.begin(), telares2.end(), compara);
    //     telares2[0].tiempo += telares2[0].velocidad*telas[i];
    //     telares2[0].tareas.push_back(telas[i]);
    // }


    for(int i = 0; i < telares2.size(); i++) {
        cout << telares2[i].num << " ";
        cout << telares2[i].tiempo << endl;
        for(int j = 0; j < telares2[i].tareas.size(); j++) {
            cout << " " << telares2[i].tareas[j];
        }
        cout << endl;
    }



    return 0;
}
