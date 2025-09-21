#include <vector>
using namespace std;

struct Congruence {
    long long a, m;
};

// Extended Euclidean Algorithm to find modular inverse
long long extended_gcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// Function to find modular inverse of a modulo m
long long mod_inv(long long a, long long m) {
    long long x, y;
    long long gcd = extended_gcd(a, m, x, y);
    if (gcd != 1) {
        // Modular inverse doesn't exist if a and m are not coprime
        return -1;
    }
    return (x % m + m) % m; // Ensure positive result
}

long long chinese_remainder_theorem(vector<Congruence> const& congruences) {
    long long M = 1;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }
    
    long long solution = 0;
    for (auto const& congruence : congruences) {
        long long a_i = congruence.a;
        long long m_i = congruence.m;
        long long M_i = M / m_i;
        long long N_i = mod_inv(M_i, m_i);
        
        if (N_i == -1) {
            // Modular inverse doesn't exist, CRT cannot be applied
            return -1;
        }
        
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    
    return solution;
}

// Alternative implementation that handles non-coprime moduli
long long chinese_remainder_theorem_safe(vector<Congruence> const& congruences) {
    if (congruences.empty()) return 0;
    
    long long a1 = congruences[0].a;
    long long m1 = congruences[0].m;
    
    for (size_t i = 1; i < congruences.size(); i++) {
        long long a2 = congruences[i].a;
        long long m2 = congruences[i].m;
        
        long long gcd = extended_gcd(m1, m2, x, y);
        
        if ((a1 - a2) % gcd != 0) {
            // No solution exists
            return -1;
        }
        
        long long lcm = m1 / gcd * m2;
        long long solution = a1 + (a2 - a1) * (m1 / gcd) % lcm * x % lcm;
        solution = (solution % lcm + lcm) % lcm;
        
        a1 = solution;
        m1 = lcm;
    }
    
    return a1;
}
