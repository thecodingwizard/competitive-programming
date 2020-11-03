#include <bits/stdc++.h>
 
using namespace std;
 
#define ii pair<int, int>
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define maxn 1000002
 
int n, m;
int pi[maxn];
// l[i] and r[i] give the previous and next greatest number of A[i]
// in the [0...i] prefix
int l[maxn], r[maxn];
int A[maxn];
int B[maxn];
 
bool eq(int i, int j) {
    int start = i - j;
    return (l[j] == -1 || A[start + l[j]] < A[i]) && (r[j] == n || A[i] < A[start + r[j]]);
}
bool eq2(int i, int j) {
    if (j == n) return false;
    int start = i - j;
    return (l[j] == -1 || B[start + l[j]] < B[i]) && (r[j] == n || B[i] < B[start + r[j]]);
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    int idxMap[n];
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        A[x-1] = i;
        idxMap[i] = x-1;
    }
    int L[n], R[n];
    for (int i = 0; i < n; i++) {
        L[i] = i-1, R[i] = i+1;
    }
    for (int idx = n-1; ~idx; idx--) {
        int i = A[idx];
        l[idx] = L[i] == -1 ? -1 : idxMap[L[i]], r[idx] = R[i] == n ? n : idxMap[R[i]];
        if (L[i] != -1) R[L[i]] = R[i];
        if (R[i] != n) L[R[i]] = L[i];
    }
 
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0) {
            if (!((l[j] == -1 || A[l[j]] < A[j]) && (r[j] == n || A[j] < A[r[j]]))) {
                cout << "???" << endl;
            }
            if (eq(i, j)) break;
            j = pi[j-1];
        }
        if (eq(i, j)) j++;
        pi[i] = j;
    }
 
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }
    vector<int> indexes;
    int j = 0;
    for (int i = 0; i < m; i++) {
        while (j > 0 && !eq2(i, j)) j = pi[j-1];
        if (eq2(i, j)) j++;
 
        if (j == n) indexes.pb(i-j+2);
    }
 
    cout << indexes.size() << endl;
    for (int x : indexes) cout << x << " ";
    cout << endl;
 
    return 0;
}
