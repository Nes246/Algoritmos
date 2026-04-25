#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

//Tengo 2, 5, 10 en monedas o billetes, necesito saber cuanto de cambio
//se puede dar con solo esos

int main() {
    int arrMonedas[3] = {2, 5, 10};
    int maxSum = 2 + 5 + 10;

    int dp[100] = {}; // 0 = no se puede, 1 = se puede

    dp[0] = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = maxSum; j >= arrMonedas[i]; j--) {
            int a = dp[j - arrMonedas[i]];
            if (dp[j - arrMonedas[i]] == 1) {
                dp[j] = 1;
            }
        }
    }

    for (int i = 1; i <= maxSum; i++) {
        if (dp[i]) {
            cout << i << endl;
        }
    }
}