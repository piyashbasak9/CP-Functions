#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long llu;
typedef long long ll;

// Macros to replace the undefined functions
#define full(x) x.begin(), x.end()
#define pb push_back

class BIG_INT {
private:
    string result;

public:
    string bigfinder(string a, string b) {
        if (a.size() < b.size()) swap(a, b);
        string d = b;
        reverse(full(b));
        while (b.size() < a.size()) b.pb('0');
        reverse(full(b));
        
        for (size_t i = 0; i < a.size(); i++) {
            if (a[i] > b[i]) return a;
            else if (a[i] < b[i]) return d;
        }
        return "same";
    }

    llu stringtonumber(string a) {
        llu n = 0;
        for (size_t i = 0; i < a.size(); i++) {
            n = (n * 10) + (a[i] - '0');
        }
        return n;
    }

    string add(string a, string b) {
        result.clear();
        reverse(full(a));
        reverse(full(b));
        
        if (a.size() < b.size()) swap(a, b);
        while (b.size() < a.size()) b.pb('0');
        
        int carry = 0;
        for (size_t i = 0; i < a.size(); i++) {
            int sum = (a[i] - '0') + (b[i] - '0') + carry;
            result.pb((sum % 10) + '0');
            carry = sum / 10;
        }
        
        while (carry > 0) {
            result.pb((carry % 10) + '0');
            carry /= 10;
        }
        
        reverse(full(result));
        return result;
    }

    string subtraction(string a, string b) {
        result.clear();
        bool is_negative = false;
        
        if (bigfinder(a, b) == b) {
            swap(a, b);
            is_negative = true;
        }
        
        reverse(full(a));
        reverse(full(b));
        while (b.size() < a.size()) b.pb('0');
        
        int borrow = 0;
        for (size_t i = 0; i < a.size(); i++) {
            int digit_a = a[i] - '0';
            int digit_b = b[i] - '0';
            
            if (digit_a < digit_b + borrow) {
                digit_a += 10;
                int diff = digit_a - digit_b - borrow;
                result.pb(diff + '0');
                borrow = 1;
            } else {
                int diff = digit_a - digit_b - borrow;
                result.pb(diff + '0');
                borrow = 0;
            }
        }
        
        // Remove leading zeros
        while (result.size() > 1 && result.back() == '0') {
            result.pop_back();
        }
        
        if (is_negative) result.pb('-');
        reverse(full(result));
        return result;
    }

    string multiplication(string a, string b) {
        if (a == "0" || b == "0") return "0";
        if (b.size() > a.size()) swap(a, b);
        
        vector<string> partial_products;
        
        for (int i = b.size() - 1; i >= 0; i--) {
            int digit_b = b[i] - '0';
            int carry = 0;
            string product;
            
            for (int j = a.size() - 1; j >= 0; j--) {
                int digit_a = a[j] - '0';
                int temp = digit_a * digit_b + carry;
                product.pb((temp % 10) + '0');
                carry = temp / 10;
            }
            
            if (carry > 0) {
                product.pb(carry + '0');
            }
            
            reverse(full(product));
            
            // Add trailing zeros
            int zeros_to_add = b.size() - 1 - i;
            for (int z = 0; z < zeros_to_add; z++) {
                product.pb('0');
            }
            
            partial_products.pb(product);
        }
        
        // Sum all partial products
        result = "0";
        for (const auto& product : partial_products) {
            result = add(result, product);
        }
        
        return result;
    }
};

// Helper function to get number of digits
int Digit(ll number) {
    if (number == 0) return 1;
    int count = 0;
    while (number != 0) {
        number /= 10;
        count++;
    }
    return count;
}

// Big Integer Division
string bigDivision(string a, ll b) {
    if (b == 0) return "Error: Division by zero";
    
    ll remainder = 0;
    string quotient;
    
    for (size_t i = 0; i < a.size(); i++) {
        remainder = remainder * 10 + (a[i] - '0');
        quotient.pb((remainder / b) + '0');
        remainder %= b;
    }
    
    // Remove leading zeros
    size_t pos = quotient.find_first_not_of('0');
    if (pos != string::npos) {
        quotient = quotient.substr(pos);
    } else {
        quotient = "0";
    }
    
    return quotient; // Returns quotient, remainder is lost
}

int main() {
    BIG_INT big_int;
    
    // Test examples
    cout << "Addition: " << big_int.add("123", "456") << endl;
    cout << "Subtraction: " << big_int.subtraction("456", "123") << endl;
    cout << "Multiplication: " << big_int.multiplication("12", "34") << endl;
    cout << "Division: " << bigDivision("50", 6) << endl;
    
    return 0;
}
