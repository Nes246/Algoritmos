#include <iostream>
#include <iomanip>
#include <cstring>


using namespace std;


int FiboncacciTopDown(int *memo, int n);
int FibonacciBottomUp(int *memo, int n);

int main() {

    int memo[10], num;

    for (int i = 0; i < 10; i++) {
        memo[i] = -1;
    }

    num = 6;
    //int n = FiboncacciTopDown(memo, num);
    int n = FibonacciBottomUp(memo, num);

    cout << n << endl;
    return 0;
}

int FiboncacciTopDown(int *memo, int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = FiboncacciTopDown(memo, n - 1) + FiboncacciTopDown(memo, n - 2);
    return memo[n];
}

int FibonacciBottomUp(int *memo, int n) {
    memo[0] = 0;
    memo[1] = 1;
    for (int i = 2; i <= n; i++) {
        memo[i] = memo[i - 1] + memo[i - 2];
    }
    return memo[n];
}
