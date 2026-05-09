#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

struct Paquete {
    int num;
    int ganancia;
    int peso;
    double ratio;
};

void ordenarPaquete(vector<Paquete>& paquetes) {
    for (int i = 0; i < paquetes.size(); i++) {
        for (int j = i; j < paquetes.size(); j++) {
            if (paquetes[i].ratio < paquetes[j].ratio) {
                Paquete aux = paquetes[i];
                paquetes[i] = paquetes[j];
                paquetes[j] = aux;
            }
        }
    }
}

int main() {

    vector<vector<int>> matriz = {
        {10,2},{15,3},{10,5},{24,12},{8,2}
    };

    //Llenar Datos
    vector<Paquete> paquetes;
    for (int i = 0; i < matriz.size(); i++) {
        Paquete p;
        p.num = i + 1;
        p.ganancia = matriz[i][0];
        p.peso = matriz[i][1];
        p.ratio = (double)p.ganancia / (double)p.peso;
        paquetes.push_back(p);
    }

    ordenarPaquete(paquetes);
    int pesoMaximo = 16, suma = 0, ganancia = 0;

    for (int i = 0; i < paquetes.size(); i++) {
        //cout << paquetes[i].num << " " << paquetes[i].ganancia << " " << paquetes[i].ratio << endl;
        if (paquetes[i].peso + suma <= pesoMaximo) {
            suma += paquetes[i].peso;
            ganancia += paquetes[i].ganancia;
        }
    }

    cout << "Ganancia de la exportacion: "<<ganancia << " en miles de dolares" << endl;
    cout << "Peso sobrante en el contenedor: " << pesoMaximo - suma << endl;

    return 0;
}
