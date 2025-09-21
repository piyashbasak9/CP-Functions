#include <vector>
using namespace std;

const int N = 1e6 + 9, LOG = 21;
int up[N][LOG], depth[N];
vector<int> children[N];

void dfs(int a) {
    for (auto b : children[a]) {
        depth[b] = depth[a] + 1;
        up[b][0] = a; // a is parent of b
        for (int i = 1; i < LOG; ++i) {
            up[b][i] = up[up[b][i-1]][i-1];
        }
        dfs(b);
    }
}

int getKthAncestor(int node, int k) {
    if (depth[node] < k) return -1;
    for (int i = 0; i < LOG; ++i) {
        if (k & (1 << i)) {
            node = up[node][i];
        }
    }
    return node;
}

int getLCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    u = getKthAncestor(u, depth[u] - depth[v]);
    if (u == v) return v;
    for (int i = LOG - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[v][0];
}
