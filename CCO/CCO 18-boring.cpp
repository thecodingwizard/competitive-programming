/*
 * My code works online, but doesn't run fast enough to pass the online version
 * of the problem with Q <= 10^6.
 *
 * The idea is we want to maintain a set of all legal pairs of lectures.
 * However, we only need to store the pairs where one of the numbers
 * is the biggest number in the range [i-k+1, i+k-1] (ie there's no number
 * bigger than it within k).
 *
 * Maintain a max seg tree. We begin by looping through all numbers and
 * adding it into the set if the max number on its left & right (within k) are
 * both smaller than the number. Add the pair to the set.
 *
 * To handle updates:
 * - If the number we're adding isn't part of any pair, do nothing
 * - If the number we're adding is the biggest number in its range, remove
 *   the pair it belongs to
 * - If the number we're adding is part of a pair, remove all pairs it's part of.
 *   Note that it will be part of at most two pairs.
 *
 * In all cases, after we finish this, we then check the number to see if it's
 * the max number in its range. If it is, add it to the set.
 * If it is not, then check + add the largest number within k steps on its left / right.
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second

int n, k, q; 
int A[1000000]; 
vector<int> dependency[1000000];
int partner[1000000];

struct cmp {
    bool operator()(const ii &x, const ii &y) const {
        if (A[x.f]+A[x.s] == A[y.f]+A[y.s]) return x < y;
        return A[x.f]+A[x.s] > A[y.f] + A[y.s];
    }
};

set<pair<int, ii>> best;

struct Seg {
    vector<int> st;
    void init() {
        st.assign(4*n, -1);
    }
    int qry(int p, int i, int j, int L, int R) {
        if (i > R || j < L) return -1;
        if (L <= i && j <= R) return st[p];
        int a = qry(2*p, i, (i+j)/2, L, R), b = qry(2*p+1, (i+j)/2+1, j, L, R);
        if (a == -1) return b;
        if (b == -1) return a;
        return A[a] < A[b] ? b : a;
    }
    void upd(int p, int i, int j, int k) {
        if (i > k || j < k) return;
        if (i == j) {
            st[p] = k;
            return;
        }
        upd(2*p, i, (i+j)/2, k);
        upd(2*p+1, (i+j)/2+1, j, k);
        int l = st[2*p], r = st[2*p+1];
        if (l == -1) {
            st[p] = r;
        } else if (r == -1) {
            st[p] = l;
        } else {
            st[p] = A[l] > A[r] ? l : r;
        }
    }
} st;

void insert(int u, bool remove = false, bool addLR = false) {
    if (partner[u] != -1) {
        int v = partner[u];
        //cout << "REMOVED " << u << " " << v << endl;
        assert(best.erase(make_pair(A[u]+A[v], make_pair(u, v))) == 1);
        dependency[v].erase(find(dependency[v].begin(), dependency[v].end(), u));
        partner[u] = -1;
    }
    if (remove) return;
    int l = u == 0 ? -1 : st.qry(1, 0, n-1, max(u-k+1, 0), u-1);
    int r = u == n-1 ? -1 : st.qry(1, 0, n-1, u+1, min(u+k-1, n-1));

    if (addLR) {
        if (l != -1) {
            insert(l);
        }
        if (r != -1) {
            insert(r);
        }
    }

    if (l != -1 && A[l] >= A[u]) return;
    if (r != -1 && A[r] > A[u]) return;
    int v;
    if (l == -1) v = r;
    else if (r == -1) v = l;
    else v = A[l] > A[r] ? l : r;

    best.insert(make_pair(A[u]+A[v], make_pair(u, v)));
    //cout << "ADDED " << u << " " << v << endl;
    dependency[v].push_back(u);
    partner[u] = v;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    cin >> n >> k >> q;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        partner[i] = -1;
    }

    st.init();
    for (int i = 0; i < n; i++) st.upd(1, 0, n-1, i);

    for (int i = 0; i < n; i++) {
        insert(i);
    }

    int prv = A[best.rbegin()->s.f] + A[best.rbegin()->s.s]; 
    cout << prv << "\n";

    //q = 10000;
    for (int i = 0; i < q; i++) {
        int idx, x; cin >> idx >> x;
        // If online version, uncomment next line + optimize constant factor??
        idx ^= prv; x ^= prv;
        --idx;
        //int idx = rand()%n, x = rand()%(int)1e9;
        //cout << idx << " " << x << endl;
        vector<int> deps(dependency[idx]);
        vector<int>().swap(dependency[idx]);
        //assert(deps.size() <= 2);
        for (int v : deps) {
            int tmp = best.erase(make_pair(A[v]+A[idx], make_pair(v, idx)));
            partner[v] = -1;
            if (tmp != 1) {
                cout << "(" << v << "; " << idx << ")" << endl;
                cout << tmp << "!!!" << endl;
                //assert(tmp == 1);
            }
        }
        insert(idx, true);
        A[idx] = x;
        st.upd(1, 0, n-1, idx);
        for (int v : deps) {
            insert(v);
        }
        insert(idx, false, true);
        int ans = A[best.rbegin()->s.f] + A[best.rbegin()->s.s];

        /*
        int ans2 = 0;
        for (int a = 0; a < n; a++) {
            for (int b = a+1; b < min(n, a+k); b++) {
                if (A[a] + A[b] > ans2) ans2 = A[a] + A[b];
            }
        }
        for (int i = 0; i < n; i++) cout << A[i] << " ";
        cout << endl;
        for (pair<int, ii> x : best) {
            cout << "(" << x.f << "," << x.s.f << "," << x.s.s << ") " << endl;
            assert(x.f == A[x.s.f]+A[x.s.s]);
        }
        cout << endl;
        cout << "Answer: " << ans << "(" << best.rbegin()->s.f << " " << best.rbegin()->s.s << ")" << " " << ans2 << endl;
        assert(ans == ans2);
        */
        cout << ans << "\n";
        prv = ans;
    }

    return 0;
}
