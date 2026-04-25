#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

//Tengo 2, 5, 10 en monedas o billetes, necesito saber cuanto de cambio
//se puede dar con solo esos

int main() {
    vector <int> monedas = {0, 2, 5, 10};
    int maxSum = 2 + 5 + 10;
    int n = monedas.size();

    int dp[n + 1][maxSum +1] = {}; // 0 = no se puede, 1 = se puede

    dp[0][0] = 1;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= maxSum; j++){
            dp[i][j] = dp[i - 1][j];

            if(j >= monedas[i]){
                dp[i][j] = max(dp[i - 1][j - monedas[i]], dp[i - 1][j]);
            }
        }
    }


    for (int i = 1; i <= maxSum; i++) {
        if (dp[n][i]) {
            cout << i << endl;
        }
    }
}