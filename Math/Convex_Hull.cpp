#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    
    Point() {
        this->x = 0;
        this->y = 0;
    }
    
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    
    bool operator==(const Point& p) const {
        return (this->x == p.x && this->y == p.y);
    }
    
    bool operator<(const Point& p) const {
        return make_pair(this->x, this->y) < make_pair(p.x, p.y);
    }
    
    void operator-=(const Point& p) {
        this->x -= p.x;
        this->y -= p.y;
    }
    
    Point operator-(const Point& p) const {
        return Point(this->x - p.x, this->y - p.y);
    }
    
    Point operator+(const Point& p) const {
        return Point(this->x + p.x, this->y + p.y);
    }
    
    long long operator*(const Point& p) const {
        return 1LL * x * p.y - 1LL * y * p.x;
    }
    
    long long dot(const Point& p) const {
        return 1LL * x * p.x + 1LL * y * p.y;
    }
    
    bool isInside(const Point& a, const Point& b) const {
        if ((a - *this) * (b - *this) != 0) return false;
        bool d1 = this->x >= min(a.x, b.x) && this->x <= max(a.x, b.x);
        bool d2 = this->y >= min(a.y, b.y) && this->y <= max(a.y, b.y);
        return d1 && d2;
    }
    
    bool rayIntersect(const Point& a, const Point& b) const {
        Point q(this->x, INT32_MAX);
        
        for (int rep = 0; rep < 2; ++rep) {
            if ((a - *this) * (q - *this) <= 0 && 
                (b - *this) * (q - *this) > 0 && 
                (a - *this) * (b - *this) < 0) {
                return true;
            }
            swap(a, b);
        }
        return false;
    }
    
    friend istream& operator>>(istream& cin, Point& p) {
        cin >> p.x >> p.y;
        return cin;
    }
    
    friend ostream& operator<<(ostream& cout, const Point& p) {
        cout << p.x << " " << p.y;
        return cout;
    }
};

// Upper and lower hull (Andrew's monotone chain algorithm)
void convex_hull_upper_lower() {
    int n;
    cin >> n;
    vector<Point> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    
    if (v.size() < 2) {
        cout << v.size() << "\n";
        for (auto p : v) {
            cout << p << "\n";
        }
        return;
    }
    
    vector<Point> hull;
    
    // Build lower hull
    for (int i = 0; i < v.size(); i++) {
        while (hull.size() >= 2) {
            Point A = hull[hull.size() - 2];
            Point B = hull[hull.size() - 1];
            Point C = v[i];
            if ((B - A) * (C - A) <= 0) {
                break;
            }
            hull.pop_back();
        }
        hull.push_back(v[i]);
    }
    
    // Build upper hull
    int lower_size = hull.size();
    for (int i = v.size() - 2; i >= 0; i--) {
        while (hull.size() > lower_size) {
            Point A = hull[hull.size() - 2];
            Point B = hull[hull.size() - 1];
            Point C = v[i];
            if ((B - A) * (C - A) <= 0) {
                break;
            }
            hull.pop_back();
        }
        hull.push_back(v[i]);
    }
    
    hull.pop_back(); // Remove duplicate starting point
    
    cout << hull.size() << "\n";
    for (auto p : hull) {
        cout << p << "\n";
    }
}

// Sorting by angle (Graham scan)
void convex_hull_graham() {
    int n;
    cin >> n;
    vector<Point> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    
    // Find the point with lowest y (and leftmost if tie)
    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if (v[i].y < v[min_idx].y || 
            (v[i].y == v[min_idx].y && v[i].x < v[min_idx].x)) {
            min_idx = i;
        }
    }
    swap(v[0], v[min_idx]);
    
    Point pivot = v[0];
    
    // Sort by polar angle relative to pivot
    sort(v.begin() + 1, v.end(), [&](const Point& a, const Point& b) {
        Point vecA = a - pivot;
        Point vecB = b - pivot;
        long long cross = vecA * vecB;
        if (cross != 0) return cross > 0;
        return vecA.dot(vecA) < vecB.dot(vecB);
    });
    
    vector<Point> hull;
    hull.push_back(v[0]);
    
    for (int i = 1; i < n; i++) {
        while (hull.size() >= 2) {
            Point A = hull[hull.size() - 2];
            Point B = hull[hull.size() - 1];
            Point C = v[i];
            if ((B - A) * (C - A) <= 0) {
                break;
            }
            hull.pop_back();
        }
        hull.push_back(v[i]);
    }
    
    cout << hull.size() << "\n";
    for (auto p : hull) {
        cout << p << "\n";
    }
}

int main() {
    // Choose which convex hull algorithm to use
    // convex_hull_upper_lower();
    // convex_hull_graham();
    
    return 0;
}
