#include <iostream>
#include <iomanip>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define ITERACIONES 100000
#define alfa 0.3

using namespace std;

struct Objeto {
    int num;
    int capacidad;
    int velocidad;
};

void llenarTablas(vector<Objeto> &tablas);

bool compara(const Objeto &a, const Objeto &b) {
    return a.velocidad > b.velocidad;
}

int hallarInd(double rcl, const vector<Objeto> &tablas) {
    int cont = 0;
    for (int i = 0; i < tablas.size(); i++) {
        if (tablas[i].velocidad >= rcl) cont++;
    }
    return cont;
};

int hallarMenorVelocidad(const vector<Objeto>& solDiscos) {
    int menorVelocidad = INT_MAX;
    for (int i = 0; i < solDiscos.size(); i++) {
        if (solDiscos[i].velocidad < menorVelocidad) menorVelocidad = solDiscos[i].velocidad;
    }
    return menorVelocidad;
}

int main() {

    srand(time(NULL));
    vector<Objeto> discos = {
        {1,800,250},{2,750,200},{3,850,200}
    };

    vector<Objeto> mejorSolDisc;
    vector<vector<int>> mejorTablas;
    vector<Objeto> tablasAux;
    llenarTablas(tablasAux);
    sort(tablasAux.begin(), tablasAux.end(), compara);
    int mejorSol = INT_MIN;

    vector<Objeto> tablas;
    for (int i = 0; i < ITERACIONES; i++) {
        tablas = tablasAux;
        int solActual;
        vector<Objeto> solDiscos = discos;
        vector<vector<int>> solTablas= {{},{},{}};

        //Constructor
        while (!tablas.empty()) {
            //Tablas
            int betat = tablas[0].velocidad;
            int taot = tablas[tablas.size() - 1].velocidad;
            double rclt = betat - alfa*(betat-taot);
            int indRclt = hallarInd(rclt, tablas);
            int posA = rand() % indRclt;


            //Discos
            sort(solDiscos.begin(), solDiscos.end(), compara);
            int betad = solDiscos[0].velocidad;
            int taod = solDiscos[solDiscos.size() - 1].velocidad;
            double rclD = betad - alfa*(betad-taod);
            int indRclD = hallarInd(rclD, solDiscos);
            int posB = rand() % indRclD;

            if (solDiscos[posB].velocidad >= tablas[posA].velocidad) {
                solDiscos[posB].velocidad -= tablas[posA].velocidad;
                solTablas[solDiscos[posB].num - 1].push_back(tablas[posA].num);
                tablas.erase(tablas.begin() + posA);
            }

        }

        //Hallar si es mejor
        int menorVelocidad = hallarMenorVelocidad(solDiscos);
        if (mejorSol < menorVelocidad) {
            mejorSol = menorVelocidad;
            mejorSolDisc = solDiscos;
            mejorTablas = solTablas;
        }

    }

    //Imprimir mejor
    for (int i = 0; i < mejorSolDisc.size(); i++) {
        cout << i + 1 << ": ";
        //cout << mejorSolDisc[i].num << " " << mejorSolDisc[i].velocidad << endl;
        for (int j = 0; j < mejorTablas[i].size(); j++) {
            cout << mejorTablas[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Menor tiempo: " << mejorSol << endl;


    return 0;
}

void llenarTablas(vector<Objeto> &tablas) {
    tablas = {
        {1,20,150},
        {2,10,100},
        {3,15,80},
        {4,100,50},
        {5,50,120},
        {6,100,10}
    };
}
