#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    vector <int >billetes = {2,2,5,5,5,10};
    int n = billetes.size();
    int cantidad = 27;
    int dp[n + 1][cantidad + 1]{};
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j<= cantidad; j++) {
            dp[i][j] = dp[i - 1][j];

            if (j >= billetes[i-1]) {
                dp[i][j] = max(dp[i][j],dp[i - 1][j - billetes[i-1]]);
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= cantidad; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}