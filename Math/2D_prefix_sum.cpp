#include <bits/stdc++.h>
using namespace std;

#define int long long

template <size_t N = 105> // Adjust default size as needed
struct PrefixSum2D {
    int arr[N][N], prefix[N][N];
    int n, m;

    // Initialize with dimensions
    void init(int _n, int _m) {
        n = _n; m = _m;
        memset(arr, 0, sizeof arr);
        memset(prefix, 0, sizeof prefix);
    }

    // Set value at (x,y) - 1-based indexing
    void set(int x, int y, int val) {
        arr[x][y] = val;
    }

    // Compute prefix sums
    void compute() {
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                prefix[x][y] = arr[x][y] 
                             + prefix[x-1][y]
                             + prefix[x][y-1]
                             - prefix[x-1][y-1];
            }
        }
    }

    // Query sum from (x1,y1) to (x2,y2) inclusive
    int query(int x1, int y1, int x2, int y2) {
        return prefix[x2][y2]
             - prefix[x1-1][y2]
             - prefix[x2][y1-1]
             + prefix[x1-1][y1-1];
    }

    // Optional: Print the prefix matrix (for debugging)
    void print() {
        cout << "Prefix Matrix:\n";
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                cout << prefix[x][y] << " ";
            }
            cout << "\n";
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    PrefixSum2D<> ps;
    int n, m, q;
    cin >> n >> m;

    ps.init(n, m);

    // Input array (1-based indexing)
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            int val; cin >> val;
            ps.set(x, y, val);
        }
    }

    // Precompute prefix sum
    ps.compute();
    // ps.print(); // Uncomment to debug prefix matrix

    // Handle queries
    cin >> q;
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << ps.query(x1, y1, x2, y2) << '\n';
    }

    return 0;
}
