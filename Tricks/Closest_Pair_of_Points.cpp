#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;
#define x first
#define y second

long long dist2(pair<int, int> a, pair<int, int> b) {
    return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}

pair<int, int> closest_pair(vector<pair<int, int>> a) {
    int n = a.size();
    assert(n >= 2);
    
    vector<pair<pair<int, int>, int>> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = {a[i], i};
    }
    sort(p.begin(), p.end());
    
    int l = 0;
    long long ans = dist2(p[0].x, p[1].x);
    pair<int, int> ret = {p[0].y, p[1].y};
    
    set<pair<int, int>> active_points;
    
    for (int r = 0; r < n; r++) {
        int current_x = p[r].x.x;
        
        // Remove points that are too far to the left
        while (!active_points.empty()) {
            auto leftmost = *active_points.begin();
            if (1LL * (current_x - leftmost.first) * (current_x - leftmost.first) >= ans) {
                active_points.erase(active_points.begin());
            } else {
                break;
            }
        }
        
        // Check candidate points in the active set
        if (!active_points.empty()) {
            auto it = active_points.lower_bound({p[r].x.y - sqrt(ans), INT_MIN});
            while (it != active_points.end()) {
                int y_val = it->first;
                int idx = it->second;
                if (1LL * (y_val - p[r].x.y) * (y_val - p[r].x.y) >= ans) {
                    break;
                }
                long long nw = dist2(a[idx], p[r].x);
                if (nw < ans) {
                    ans = nw;
                    ret = {idx, p[r].y};
                }
                it++;
            }
        }
        
        active_points.insert({p[r].x.y, p[r].y});
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }
    
    pair<int, int> z = closest_pair(p);
    if (z.x > z.y) {
        swap(z.x, z.y);
    }
    
    cout << z.x << ' ' << z.y << ' ' << fixed << setprecision(6) 
         << sqrt(dist2(p[z.x], p[z.y])) << '\n';
    
    return 0;
}
