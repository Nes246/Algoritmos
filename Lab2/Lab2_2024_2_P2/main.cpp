#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>

using namespace std;

int main() {

    int largo = 4;
    int costos[largo + 1] = {0,3,5,7,8};

    int dp[50];
    dp[0] = 0;
    for (int i = 1; i <= largo; i++) {
        dp[i] = 0;
        for (int j = 1; j <= i; j++) {
            dp[i] = max(dp[i], costos[j] + dp[i - j]);
        }
    }

    cout << "dp = ";
    for (int i = 0; i <= largo; i++) cout << setw(2) << dp[i] << " ";
    cout << endl;
    cout << dp[largo];

    return 0;
}