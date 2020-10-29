/*
 * See: https://usaco.guide/solutions/joi-13-bubblesort
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define mp make_pair
#define ii pair<int, int>
#define f first
#define s second

int n; 
int A[100000], opt[100000];
vector<int> increasing;
int ft[100001];

void upd(int k, int v) {
    while (k <= n) {
        ft[k] += v;
        k += k&-k;
    }
}
int qry(int k) {
    int s = 0;
    while (k) {
        s += ft[k];
        k -= k&-k;
    }
    return s;
}

int ans = -1;
void dnc(int l, int r, int L, int R) {
    if (l >= r) return;
    int mid = (l+r)/2;
 
    int best = max(L, increasing[mid]);
    int bestVal = -1;
    for (int i = max(L, increasing[mid]); i <= R; i++) {
        upd(A[i], 1);
        int d = A[i], u = A[increasing[mid]];
        if (i == increasing[mid] || u < d) continue;
        int op = qry(u) - qry(d-1) + qry(u-1) - qry(d) - (u == d ? 0 : 1);
 
        if (op > bestVal) {
            bestVal = op;
            best = i;
        }
    }

    for (int i = max(L, increasing[mid]); i <= R; i++) {
        upd(A[i], -1);
    }
 
    int mid2 = (l+mid)/2;
    for (int i = increasing[mid2]; i < min(L, increasing[mid]); i++) {
        upd(A[i], 1);
    }
    dnc(l, mid, L, best);
    for (int i = increasing[mid2]; i < min(L, increasing[mid]); i++) {
        upd(A[i], -1);
    }
 
    mid2 = (mid+1+r)/2;
    for (int i = increasing[mid]; i < min(increasing[mid2], L); i++) {
        upd(A[i], -1);
    }
    for (int i = max(increasing[mid2], L); i < best; i++) {
        upd(A[i], 1);
    }
    dnc(mid+1, r, best, R);
    for (int i = increasing[mid]; i < min(increasing[mid2], L); i++) {
        upd(A[i], 1);
    }
    for (int i = max(increasing[mid2], L); i < best; i++) {
        upd(A[i], -1);
    }
 
    ans = max(ans, bestVal);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i];
    map<int, int> compress; int ct = 1; set<int> s;
    for (int i = 0; i < n; i++) {
        s.insert(A[i]);
    }
    for (auto x : s) compress[x]=ct++;
    for (int i = 0; i < n; i++) {
        A[i] = compress[A[i]];
    }
    for (int i = 0; i < n; i++) {
        if (increasing.empty() || A[increasing.back()] < A[i]) {
            increasing.pb(i);
        }
    }
    dnc(0, increasing.size(), 0, n-1);

    /*
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            upd(A[j], 1);
            if (A[j] < A[i]) {
                ans = max(ans, qry(A[i]) - qry(A[j]-1) + qry(A[i]-1) - qry(A[j]) - 1);
            }
        }
        for (int j = i; j < n; j++) {
            upd(A[j], -1);
        }
    }
    */


    ll num = 0;
    for (int i = n-1; i >= 0; i--) {
        num += qry(A[i]-1);
        upd(A[i], 1);
    }
    //cout << num << " " << ans << endl;
    cout << num-ans << endl;
    return 0;
}
