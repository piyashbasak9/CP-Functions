/*
   This code implements a Merge Sort Tree.
   
   Merge Sort Tree is a Segment Tree where each node stores a sorted list of elements corresponding to the segment it represents.
   It allows efficient range queries to count elements greater than a given value in O(log^2 N) time.
   
   Functionality:
   - `store()`: Builds the Merge Sort Tree recursively.
   - `help()`: Queries the number of elements greater than `k` in a given range [i, j].
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5; // Define maximum size
vector<int> tree[N * 4]; // Segment tree where each node contains a sorted array
int ar[N]; // Input array

// Function to build the Merge Sort Tree
void store(int node , int l, int r) {
    if(l == r) { // If leaf node, store the single element
        tree[node].push_back(ar[l]);
        return;
    }
    
    int left = node * 2; // Left child
    int right = (node * 2) + 1; // Right child
    int mid = (l + r) / 2;
    
    // Recursively build left and right children
    store(left, l, mid);
    store(right, mid + 1, r);
    
    // Merge the sorted arrays from left and right child into the current node
    int i = 0, j = 0;
    while(i < tree[left].size() && j < tree[right].size()) {
        if(tree[left][i] < tree[right][j]) {
            tree[node].push_back(tree[left][i]);
            i++;
        } else {
            tree[node].push_back(tree[right][j]);
            j++;
        }
    }
    
    // Add remaining elements from left child
    while(i < tree[left].size()) {
        tree[node].push_back(tree[left][i]);
        i++;
    }
    
    // Add remaining elements from right child
    while(j < tree[right].size()) {
        tree[node].push_back(tree[right][j]);
        j++;
    }
}

// Function to count numbers greater than `k` in range [i, j]
int help(int node, int l, int r, int i, int j, int k) {
    // If the range of this node is completely inside the query range
    if(l >= i && r <= j) {
        // Use upper_bound to find first element greater than `k`
        int value = tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), k);
        return value;
    }
    
    // If the range is completely outside the query range
    if(r < i || l > j) {
        return 0;
    }
    
    int left = node * 2;
    int right = (node * 2) + 1;
    int mid = (l + r) / 2;
    
    // Combine results from left and right children
    return help(left, l, mid, i, j, k) + help(right, mid + 1, r, i, j, k);
}
