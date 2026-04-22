#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>

using namespace std;

//El problema se basa en que tengo varias columnas de monedas,
//quiero tener la mayor cantidad de monedas pero no tener de dos columnas juntas
//La funcion a usar sera Max{dp(i-1), dp(i-2)+c[i]}
//En la mayoria de labs nos daran esta funcion

int monedasBottomUp(int *c, int n);

int main() {

    int c[7] = {0,5,1,2,10,6,2};
    int n = 7;

    int suma = monedasBottomUp(c, n);
    cout << suma << endl;


    return 0;
}

int monedasBottomUp(int *c, int n) {
    if(n == 0) return 0;
    if(n == 1) return c[1];

    int dp[n] = {};
    dp[0] = 1;
    dp[1] = c[1];
    for(int i = 2; i <= n; i++) {
        dp[i] = max(dp[i-1], dp[i-2]+c[i]);
    }
    return dp[n];

}