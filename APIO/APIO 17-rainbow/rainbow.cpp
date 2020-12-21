/*
 * https://usaco.guide/solutions/apio-17-rainbow
 *
 * Euler's Formula:
 * - For a planar graph, Euler's formula is:
 *   F = E - V + 1 + C
 *   Where C is the number of connected components
 *
 * - Use 2d segment tree to calculate E, V, and # of rivers
 * - Can do online static 2d range queries with a persistent segment tree
 */

#include <bits/stdc++.h>
#include "rainbow.h"
using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)

const int maxn = 2e5+10;
const int maxst = maxn*22*4*10;

int st[maxst], L[maxst], R[maxst], ctr = 0;

struct SegTree {
    map<int, set<int>> points;
    int roots[maxn];
    void add(int r, int c) {
        points[r].insert(c);
    }
    void build() {
        F0R(i, maxn) {
            roots[i] = i==0?0:roots[i-1];
            for (int p : points[i]) {
                update(roots[i], 0, maxn-1, p);
            }
        }
    }
    void update(int &node, int i, int j, int k) {
        st[ctr+1] = st[node];
        L[ctr+1] = L[node];
        R[ctr+1] = R[node];
        node = ctr+1;
        ctr++;

        st[node]++;

        if (i == j) return;

        int m = (i+j)/2;
        if (m >= k) {
            update(L[node], i, m, k);
        } else {
            update(R[node], m+1, j, k);
        }
    }

    int query(int r1, int c1, int r2, int c2) {
        //cout << r1 << " " << c1 << "; " << r2 << " "<< c2 << endl;
        //cout << query(roots[r2], c1, c2, 0, maxn-1) << ", " <<  (r1>0?query(roots[r1-1], c1, c2, 0, maxn-1):0) << endl;
        return query(roots[r2], c1, c2, 0, maxn-1) - (r1>0?query(roots[r1-1], c1, c2, 0, maxn-1):0);
    }

    int query(int node, int l, int r, int i, int j) {
        if (l <= i && j <= r) return st[node];
        if (l > j || r < i) return 0;
        return query(L[node], l, r, i, (i+j)/2) + query(R[node], l, r, (i+j)/2+1, j);
    }
} vertices, edges_horiz, edges_vert, rivers;

int min_r = maxn, min_c = maxn, max_r = 0, max_c = 0;
void addRiver(int r, int c) {
    min_r = min(min_r, r);
    max_r = max(max_r, r);
    min_c = min(min_c, c);
    max_c = max(max_c, c);
    vertices.add(r, c);
    vertices.add(r+1, c);
    vertices.add(r, c+1);
    vertices.add(r+1, c+1);
    edges_horiz.add(r, c);
    edges_horiz.add(r+1, c);
    edges_vert.add(r, c);
    edges_vert.add(r, c+1);
    rivers.add(r, c);
    //cout << "adding " << r << ", " << c << endl;
}

void init(int R, int C, int sr, int sc, int M, char *S) {
    --sr; --sc;
    addRiver(sr, sc);
    F0R(i, M) {
        char c = S[i];
        if (c == 'N') sr--;
        else if (c == 'E') sc++;
        else if (c == 'S') sr++;
        else if (c == 'W') sc--;
        else assert(false);
        addRiver(sr, sc);
    }
    vertices.build();
    edges_horiz.build();
    edges_vert.build();
    rivers.build();
}

int colour(int ar, int ac, int br, int bc) {
    --ar; --ac;
    int riverCt = rivers.query(ar, ac, br-1, bc-1);
    int vertexCt = vertices.query(ar+1, ac+1, br-1, bc-1) + (br-ar-1)*2 + (bc-ac-1)*2 + 4;
    int edgeCt = edges_horiz.query(ar+1, ac, br-1, bc-1) + edges_vert.query(ar, ac+1, br-1, bc-1) + (br-ar)*2 + (bc-ac)*2;
    int connectedComponents = (ar < min_r && br-1 > max_r && ac < min_c && bc-1 > max_c) ? 2 : 1;
    int ans = edgeCt - vertexCt + 1 + connectedComponents - 1 - riverCt;
    //cout << ar << " "<< ac << " " << br << " " << bc << " " << riverCt << " " << vertexCt << " " << edgeCt << " " << connectedComponents << endl;
    return ans;
}

