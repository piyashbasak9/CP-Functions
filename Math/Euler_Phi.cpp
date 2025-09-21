#include <vector>
#include <iostream>
using namespace std;

/*
1. phi(n) = n * (p1 - 1) / p1 * (p2 - 1) / p2 . . . .
2. gcd d: phi(n / d)
3. Sum of coprime numbers of an integer = phi(n) * n / 2
4. N = phi(d) where, d | N
*/

vector<int> phi(n + 1);

void prec(int n) { //nlogn
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i - 1;
    for (int i = 2; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
            phi[j] -= phi[i];
}

int phi(int n) { //sqrt(n)
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}
