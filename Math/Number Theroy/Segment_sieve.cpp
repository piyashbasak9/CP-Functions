#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> segmentedSieve(int low, int high) {
    if (low > high) return {};
    
    vector<int> primes;
    int limit = floor(sqrt(high)) + 1;
    
    // Step 1: Simple sieve to find base primes
    vector<bool> baseSieve(limit + 1, true);
    baseSieve[0] = baseSieve[1] = false;
    for (int p = 2; p * p <= limit; p++) {
        if (baseSieve[p]) {
            for (int multiple = p * p; multiple <= limit; multiple += p) {
                baseSieve[multiple] = false;
            }
        }
    }
    
    // Step 2: Segmented sieve for the target range
    vector<bool> segmentSieve(high - low + 1, true);
    if (low == 1) segmentSieve[0] = false;
    
    for (int p = 2; p <= limit; p++) {
        if (baseSieve[p]) {
            int firstMultiple = max(p * p, ((low + p - 1) / p) * p);
            for (int multiple = firstMultiple; multiple <= high; multiple += p) {
                segmentSieve[multiple - low] = false;
            }
        }
    }
    
    // Collect primes
    for (int i = 0; i < segmentSieve.size(); i++) {
        if (segmentSieve[i]) {
            primes.push_back(low + i);
        }
    }
    
    return primes;
}

int main() {
    int low = 100, high = 200;
    vector<int> primes = segmentedSieve(low, high);
    
    cout << "Primes between " << low << " and " << high << ":\n";
    for (int prime : primes) cout << prime << " ";
    
    return 0;
}
