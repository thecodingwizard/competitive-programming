/*
 * For the 50% subtask where all books are on the same shelf, we can process
 * each shelf independently. The number of moves necessary for each shelf is
 * equal to the number of books on the shelf minus the longest common subsequence
 * of the initial ordering and the final ordering. We can find this in O(n log n).
 *
 * However, if the shelf does not have a 0, then we will need to add one to the
 * answer.
 *
 * For books that aren't in the right row, then it takes a minimum of one
 * step to move it to its correct position. However, we need to handle the case
 * where there is no zero, and we may need to add +1 to the answer.
 *
 * We can do this with union find: If a book begins on shelf i and ends up
 * on shelf j, we union shelves i and j. At the end, for any component that
 * a) has a change (ie the beginning state of that group of shelves does not
 * equal the end state) and b) does not start with a 0 in any of the shelves,
 * we need to add one to the answer.
 */

#include <bits/stdc++.h>

using namespace std;

int n, m; 
vector<int> A[1000], B[1000];

int lis(vector<int> &A) {
    vector<int> L;
    for (int x : A) {
        auto it = lower_bound(L.begin(), L.end(), x);
        if (it == L.end()) L.push_back(x);
        else *it = x;
    }
    return L.size();
}

pair<int, int> compute(vector<int> &A, vector<int> &B) {
    unordered_map<int, int> idx; for (int i = 0; i < (int)B.size(); i++) idx[B[i]] = i;
    vector<int> arr;
    int diffRow = 0;
    for (int x : A) {
        if (idx.count(x)) arr.push_back(idx[x]);
        else diffRow++;
    }
    return make_pair((int)arr.size() - lis(arr), diffRow);
}

int sz[1000], pa[1000], hasZero[1000], hasChange[1000];
int find(int x) {
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}
void Union(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    sz[b] += sz[a];
    pa[a] = b;
    hasZero[b] = hasZero[b] || hasZero[a];
    hasChange[b] = hasChange[b] || hasChange[a];
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x; if (x != 0) A[i].push_back(x);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x; if (x != 0) B[i].push_back(x);
        }
    }

    bool noZeroes = true;
    for (int i = 0; i < n; i++) {
        if ((int)A[i].size() != m) noZeroes = false;
    }
    if (noZeroes) {
        bool same = true;
        for (int i = 0; i < n; i++) {
            if (A[i] != B[i]) same = false;
        }
        if (!same) {
            cout << -1 << endl;
        } else {
            cout << 0 << endl;
        }
        return 0;
    }

    for (int i = 0; i < n; i++) {
        sz[i] = 1; pa[i] = i;
        hasZero[i] = (int)A[i].size() != m;
        hasChange[i] = A[i] != B[i];
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        pair<int, int> res = compute(A[i], B[i]);
        int add = res.first + res.second;
        ans += add;
    }

    unordered_map<int, int> row;
    for (int i = 0; i < n; i++) {
        for (int j : B[i]) row[j] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j : A[i]) Union(i, row[j]);
    }
    for (int i = 0; i < n; i++) {
        if (pa[i] == i) {
            if (hasChange[i] && !hasZero[i]) {
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
