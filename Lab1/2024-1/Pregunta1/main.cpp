#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

bool validaK(vector<int>&pesos,int k) {
    int anterior=0;
    for(int i=0;i<pesos.size();i++) {
        if (i!=0) {
            int dif=abs(pesos[i]-anterior);
            if (dif<=k)return true;
        }
        anterior=pesos[i];
    }
    return false;
}
void empacar(int pos, int n,int P,int k,int*arrCarnes,int&cont,vector<int>&pesos,
    vector<vector<int>>&listaCortes) {
    //terminador:


    if (pos==n or P<0)return;
    if (P==0) {
        if (validaK(pesos,k)) {
            cont++;
            sort(pesos.begin(), pesos.end());//ordenar
            listaCortes.push_back(pesos);
        }
        return;
    }
    //avanzar
    pesos.push_back(arrCarnes[pos]);
    empacar(pos+1,n,P-arrCarnes[pos],k,arrCarnes,cont,pesos,listaCortes);
    pesos.pop_back();
    //retroceder
    empacar(pos+1,n,P,k,arrCarnes,cont,pesos,listaCortes);
}
int main() {
    int P=15;
    int arrCarnes[]={2,8,9,6,7,6};
    int k=4;
    int n=sizeof(arrCarnes)/sizeof(arrCarnes[0]);
    int cont=0;
    vector<int>pesos;
    vector<vector<int>>listaCortes;

    cout<<"Numero de pedidos que se puede atender de "<<P<<"kg : ";
    empacar(0,n,P,k,arrCarnes,cont,pesos,listaCortes);
    cout<<cont<<endl;
    cout<<"Cortes:"<<endl;
    for(int i=0;i<listaCortes.size();i++) {
        vector<int>aux=listaCortes[i];
        cout<<"[";
        for(int j=0;j<aux.size();j++) {
            cout<<aux[j]<<" ";
        }
        cout<<"]"<<endl;
    }

    return 0;
}