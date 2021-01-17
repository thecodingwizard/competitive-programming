/*
 * Same sol as editorial
 *
 * bitmask dp with meet in the middle
 *
 * leftBest[mask][ct] = max cover with ct dominoes using only dominoes in the mask
 *
 * Compute leftBest[mask] in increasing value of mask
 *
 * leftBest[mask] = max(dp(mask), leftBest[mask with one 1-bit turned into a 0-bit])
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define maxn 2000
#define maxk 8
#define maxa 20
#define maxb 30

int n, k; 
int A[maxn][maxn];
int leftBest[(1 << maxa)][maxk+1];
vector<pair<int, pair<ii, int>>> dominoes;

// if adj[i][j] then dominoes i and j can be taken together
bool adj[50][50];
// if taking domino i, which other dominoes are okay to take?
ll okayDominoes[50];

void dp_left(int mask, int takeMask, int idx, int ct, int val) {
    if (idx == maxa) {
        leftBest[takeMask][ct] = max(leftBest[takeMask][ct], val);
        return;
    }

    dp_left(mask, takeMask, idx+1, ct, val);

    if ((ct < k) && (mask & (1 << idx))) {
        dp_left(mask&okayDominoes[idx], takeMask|(1<<idx), idx+1, ct+1, val + dominoes[idx].f);
    }
}

int save = 0;
void dp_right(ll mask, int idx, int ct, int val) {
    if (idx == maxa+maxb) {
        save = max(save, val + leftBest[mask&((1<<maxa)-1)][k-ct]);
        return;
    }

    dp_right(mask, idx+1, ct, val);

    if ((ct < k) && (mask & (1LL << idx))) {
        dp_right(mask&okayDominoes[idx], idx+1, ct+1, val + dominoes[idx].f);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    ll tot = 0;
    F0R(i, n) F0R(j, n) {
        cin >> A[i][j];
        tot += A[i][j];
    }
    n = max(n, 10); // make sure there are enough dominoes
    F0R(i, n) F0R(j, n) {
        if (i+1<n) dominoes.pb(mp(A[i][j]+A[i+1][j], mp(mp(i, j), 0)));
        if (j+1<n) dominoes.pb(mp(A[i][j]+A[i][j+1], mp(mp(i, j), 1)));
    }
    sort(all(dominoes));
    reverse(all(dominoes));
    F0R(i, 50) {
        F0R(j, 50) {
            ii locA = dominoes[i].s.f;
            ii locA2 = locA; if (dominoes[i].s.s == 0) locA2.f++; else locA2.s++;
            ii locB = dominoes[j].s.f;
            ii locB2 = locB; if (dominoes[j].s.s == 0) locB2.f++; else locB2.s++;
            if (locA == locB || locA == locB2 || locA2 == locB || locA2 == locB2) adj[i][j] = 0;
            else adj[i][j] = 1;
            if (adj[i][j]) okayDominoes[i] |= (1LL << j);
        }
    }

    dp_left((1<<maxa)-1, 0, 0, 0, 0);

    for (int i = 0; i < (1 << maxa); i++) {
        F0R(j, maxa) {
            F0R(x, k+1) {
                if (i & (1 << j)) leftBest[i][x] = max(leftBest[i][x], leftBest[i^(1<<j)][x]);
            }
        }
    }

    dp_right((1LL << 50)-1, maxa, 0, 0);

    cout << tot-save << endl;

    return 0;
}
