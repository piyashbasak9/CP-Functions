#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 105; // Adjust according to problem constraints
int arr[N][N][N], prefix[N][N][N];

// Function to compute 3D prefix sum
void computePrefixSum(int n, int m, int k) {
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            for (int z = 1; z <= k; z++) {
                prefix[x][y][z] = arr[x][y][z]
                                + prefix[x - 1][y][z]
                                + prefix[x][y - 1][z]
                                + prefix[x][y][z - 1]
                                - prefix[x - 1][y - 1][z]
                                - prefix[x - 1][y][z - 1]
                                - prefix[x][y - 1][z - 1]
                                + prefix[x - 1][y - 1][z - 1];
            }
        }
    }
}

// Function to query sum in a sub-cube (x1, y1, z1) → (x2, y2, z2)
int querySum(int x1, int y1, int z1, int x2, int y2, int z2) {
    return prefix[x2][y2][z2]
         - prefix[x1 - 1][y2][z2]
         - prefix[x2][y1 - 1][z2]
         - prefix[x2][y2][z1 - 1]
         + prefix[x1 - 1][y1 - 1][z2]
         + prefix[x1 - 1][y2][z1 - 1]
         + prefix[x2][y1 - 1][z1 - 1]
         - prefix[x1 - 1][y1 - 1][z1 - 1];
}

int32_t main() {
    int n, m, k, q;
    cin >> n >> m >> k; // Dimensions of 3D array

    // Input array (1-based indexing)
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            for (int z = 1; z <= k; z++) {
                cin >> arr[x][y][z];
            }
        }
    }

    // Precompute prefix sum
    computePrefixSum(n, m, k);

    cin >> q; // Number of queries
    while (q--) {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        cout << querySum(x1, y1, z1, x2, y2, z2) << endl;
    }

    return 0;
}
