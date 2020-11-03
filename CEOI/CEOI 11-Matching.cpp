/*
 * Same solution as editorial: https://oi.edu.pl/static/attachment/20110713/ceoi-2011.pdf
 *
 * Essentially, this problem can be converted to a KMP variant, where two subarrays are "equal"
 * if their "shape" is the same; ie. A and B are equal if B[i] < B[j] for all (i, j) where A[i] < A[j].
 *
 * We note that this comparison has the following properties:
 * - if A = B, then A[x...y] = B[x...y] for 1 <= x <= y <= n
 * - if A = B and B = C, then A = C
 * Hence, we can use KMP.
 *
 * Begin by defining the prefix function. pi[i] = max length of prefix that's also equal to suffix ending at i
 * pi[0] = 0. We want to be able to determine if we can extend pi[i] by one. In other words,
 * we want to check if A[0...i] and B[0...i] is equal, assuming we know that A[0...i-1] and B[0...i-1] is equal.
 *
 * Let u = index of largest number that's less than A[i], v = index of smallest number that's greater than A[i], u, v < i.
 * By definition, A[u] < A[i] < A[v].
 * It suffices to check whether B[u] < B[i] < B[v]; if that is true, then A[0...i] and B[0...i] are equal, otherwise it's not.
 *
 * To determine u, v fast, we can maintain a doubly linked list of values 1...n.
 * Then, iterate through A in reverse, removing values one by one from the doubly linked list.
 * Right before we remove a value, the neighbors of that value in the doubly linked list are u and v.
 *
 * After we find pi[i], the rest of the code is very similar to KMP; we just have a different function to
 * check for equality.
 */

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
