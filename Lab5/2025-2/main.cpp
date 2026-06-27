#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#define NUMIND 10
#define TSELECCION 0.3
#define PCASAMIENTO 0.5
#define ITERACIONES 10

using namespace std;

int calcularFitness(const vector<int>& individuo, const vector<int>& paquetes, const vector<int>& camiones);
void generaPoblacion(vector<vector<int>>& poblacion, const vector<int>& paquetes, const vector<int>& camiones);
bool aberracion(const vector<int>& individuo, const vector<int>& paquetes, const vector<int>& camiones);
bool esRepetido(const vector<int>& individuo, const vector<vector<int>>& poblacion);
void seleccion( vector<vector<int>>& padres, const vector<vector<int>>& poblacion, const vector<int>& paquetes, const vector<int>& camiones);
void casamiento(const vector<vector<int>>& padres, vector<vector<int>>& poblacion, const vector<int>& paquetes, const vector<int>& camiones);
void regeneraPoblacion(vector<vector<int>>&  poblacion, const vector<int>& paquetes, const vector<int>& camiones);


int sumaTotalCamiones;

void sumarTotalCamiones(vector<int> camiones) {
    sumaTotalCamiones = 0;
    for (int i = 0; i < camiones.size(); i++) {
        sumaTotalCamiones += camiones[i];
    }
}

int main() {

    srand(time(NULL));
    // vector<int> paquetes = {150,100,180,50,120,10};
    // vector<int> camiones = {250,200,200,100};
    vector<int> paquetes = {150,150,150,50,50,50};
    vector<int> camiones = {300,300,300};
    sumarTotalCamiones(camiones);

    vector<vector<int>> poblacion;
    generaPoblacion(poblacion, paquetes, camiones);
    cout << endl;

    for (int i = 0; i < ITERACIONES; i++) {
        vector<vector<int>> padres;
        seleccion(padres, poblacion, paquetes, camiones);
        casamiento(padres, poblacion, paquetes, camiones);
        regeneraPoblacion(poblacion, paquetes, camiones);
    }


    for (int i = 0; i < poblacion[0].size(); i++) {
        cout << poblacion[0][i] << " ";
    }
    int fitness = calcularFitness(poblacion[0], paquetes, camiones);
    cout << endl;
    cout << fitness << endl;
    //Imprimir paquetes por camion
    for (int i = 0; i < camiones.size(); i++) {
        int suma = 0;
        cout << "Camion " << i + 1 << ": ";
        for (int j = 0; j < paquetes.size(); j++) {
            int pos = i * paquetes.size() + j;
            if (poblacion[0][pos] == 1) {
                cout << j + 1 << " ";
                suma += paquetes[j];
            }
        }
        cout << " Total: " << suma << " Sobrante: " << camiones[i] - suma << endl;
    }

    return 0;
}

void generaPoblacion(vector<vector<int>>& poblacion, const vector<int>& paquetes, const vector<int>& camiones) {

    int contador = 0;
    //Seran 24 genes por individuo, 6 (numPaquetes) por cada camion
    int cantGenes = paquetes.size()*camiones.size();

    while (contador < NUMIND) {
        vector<int> individuo(cantGenes, 0);
        for (int i = 0; i < paquetes.size(); i++) {
            int camionSeleccionado = rand()%camiones.size();
            int pos = camionSeleccionado * paquetes.size() + i;
            individuo[pos] = 1;
        }

        if (!aberracion(individuo, paquetes, camiones) && !esRepetido(individuo,poblacion)) {
            poblacion.push_back(individuo);
            contador++;
        }
    }

}

bool aberracion(const vector<int>& individuo, const vector<int>& paquetes, const vector<int>& camiones) {

    vector<int> paquetesUsados(paquetes.size(), 0);
    for (int i = 0; i < camiones.size(); i++) {
        int sumaCamion = 0;
        for (int j = i * paquetes.size(); j < (i+1) * paquetes.size(); j++) {
            if (individuo[j] == 1) {
                sumaCamion += paquetes[j - (i*paquetes.size())];
                paquetesUsados[j - (i*paquetes.size())]++;
            }
        }
        if (sumaCamion > camiones[i]) return true;
    }

    for (int i = 0; i < paquetes.size(); i++) {
        if (paquetesUsados[i] != 1) return true;
    }
    return false;
}

bool esRepetido(const vector<int>& individuo, const vector<vector<int>>& poblacion) {
    for (int i = 0; i < poblacion.size(); i++) {
        if (poblacion[i] == individuo) return true;
    }
    return false;
}

int calcularFitness(const vector<int>& individuo, const vector<int>& paquetes, const vector<int>& camiones) {
    int mayorSuma = 0;
    int sumaSobra = 0;
    for (int i = 0; i < camiones.size(); i++) {
        int sumaCamion = 0;
        for (int j = 0; j < paquetes.size(); j++) {
            int pos = i * paquetes.size() + j;
            sumaCamion += individuo[pos]*paquetes[j];
        }
        sumaSobra = (camiones[i] - sumaCamion);
        if (mayorSuma < sumaSobra) mayorSuma = sumaSobra;
    }
    return sumaTotalCamiones - mayorSuma;
}

void calcularSupervivencia(const vector<vector<int>>& poblacion, const vector<int>& paquetes, const vector<int>& camiones, vector<int>& supervivencia) {
    vector<int> fitnessInd;
    int sumaFitness = 0;
    for (int i = 0; i < poblacion.size(); i++) {
        fitnessInd.push_back(calcularFitness(poblacion[i], paquetes, camiones));
        sumaFitness += fitnessInd[i];
    }
    for (int i = 0; i < poblacion.size(); i++) {
        supervivencia.push_back(100*((double)fitnessInd[i])/sumaFitness);
    }
}

void generarRuleta(const vector<int>&  supervivencia, vector<int>& ruleta) {

    int contador = 0;
    for (int i = 0; i < supervivencia.size(); i++) {
        for (int j = 0; j < supervivencia[i]; j++) {
            ruleta[contador++] = i;
        }
    }
}


void seleccion(vector<vector<int>>& padres, const vector<vector<int>>& poblacion, const vector<int>& paquetes, const vector<int>& camiones) {
    int numPadres = poblacion.size()*TSELECCION;
    int contador = 0;
    vector<int> ruleta(100,-1);
    vector<int> supervivencia;
    calcularSupervivencia(poblacion, paquetes, camiones, supervivencia);
    generarRuleta(supervivencia, ruleta);

    while (contador < numPadres) {
        int ticket = rand() % 100;
        if (ruleta[ticket] != -1) {
            padres.push_back(poblacion[ruleta[ticket]]);
            contador++;
        }
    }
}

void crearHijo(const vector<int>& padre, const vector<int>& madre, vector<int>& hijo) {

    int genPadre = padre.size()*PCASAMIENTO;

    for (int i = 0; i < genPadre; i++) {
        hijo.push_back(padre[i]);
    }

    for (int j = genPadre; j < madre.size(); j++) {
        hijo.push_back(madre[j]);
    }
}


void casamiento(const vector<vector<int>>& padres, vector<vector<int>>& poblacion, const vector<int>& paquetes, const vector<int>& camiones) {

    for (int i = 0; i < padres.size(); i++) {
        for (int j = 0; j < padres.size(); j++) {
            if (i != j) {
                vector<int> hijo;
                crearHijo(padres[i], padres[j], hijo);

                if (!aberracion(hijo, paquetes, camiones) && !esRepetido(hijo, poblacion)) {
                    poblacion.push_back(hijo);
                }
            }
        }
    }
}

void matarClones(vector<vector<int>>& poblacion) {
    vector<vector<int>> nuevaPoblacion;
    for (int i = 0; i < poblacion.size(); i++) {
        if (!esRepetido(poblacion[i], nuevaPoblacion)) {
            nuevaPoblacion.push_back(poblacion[i]);
        }
    }
    poblacion = nuevaPoblacion;
}


void regeneraPoblacion(vector<vector<int>>&  poblacion, const vector<int>& paquetes, const vector<int>& camiones) {

    matarClones(poblacion);
    //Se ordenan por mejor fitness
    sort(poblacion.begin(), poblacion.end(), [&paquetes, &camiones](const vector<int>& a, const vector<int>& b) {
        return calcularFitness(a, paquetes, camiones) > calcularFitness(b, paquetes, camiones);
    });

    //Seleccionamos a los mejores
    if (poblacion.size() > NUMIND) {
        poblacion.erase(poblacion.begin() + NUMIND, poblacion.end());
    }
}