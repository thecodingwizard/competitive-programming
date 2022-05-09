#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

const int maxn = 100000;

int n, K;
vector<int> A(maxn);
int maxInRange[4*maxn], minInRange[4*maxn];
set<ii> canReach[4*maxn];

void build(int p, int i, int j) {
    if (i == j) {
        canReach[p].insert(mp(A[i], i));
        maxInRange[p] = minInRange[p] = A[i];
    } else {
        build(p*2, i, (i+j)/2);
        build(p*2+1, (i+j)/2+1, j);
        canReach[p] = canReach[p*2];
        for (auto x : canReach[p*2+1]) {
            if (x.f >= maxInRange[p*2]-K && x.f <= minInRange[p*2]+K) {
                canReach[p].insert(x);
            }
        }
        maxInRange[p] = max(maxInRange[p*2], maxInRange[p*2+1]);
        minInRange[p] = min(minInRange[p*2], minInRange[p*2+1]);
    }
}

vector<ii> upd(int p, int i, int j, int k) {
    if (i > k || j < k) return vector<ii>();
    if (i == j && i == k) {
        maxInRange[p] = -inf;
        minInRange[p] = inf;
        canReach[p].clear();
        return vector<ii>();
    } else {
        int prevMin = maxInRange[p*2]-K, prevMax = minInRange[p*2]+K;

        vector<ii> changes = upd(p*2, i, (i+j)/2, k);
        vector<ii> changes2 = upd(p*2+1, (i+j)/2+1, j, k);

        canReach[p].erase(mp(A[k], k));
        for (auto x : changes) canReach[p].insert(x);

        int newMin = maxInRange[p*2]-K, newMax = minInRange[p*2]+K;

        if (newMin != prevMin) {
            // add everything from newMin...prevMin-1
            auto it = canReach[p*2+1].lower_bound(mp(newMin, -1));
            while (it != canReach[p*2+1].end() && it->f <= prevMin-1) {
                canReach[p].insert(*it);
                changes.pb(*it);
                it++;
            }
        }
        if (newMax != prevMax) {
            // add everything from prevMax+1...newMax
            auto it = canReach[p*2+1].lower_bound(mp(prevMax+1, -1));
            while (it != canReach[p*2+1].end() && it->f <= newMax) {
                canReach[p].insert(*it);
                changes.pb(*it);
                it++;
            }
        }
        for (auto x : changes2) {
            if (x.f >= prevMin && x.f <= prevMax) {
                canReach[p].insert(x);
                changes.pb(x);
            }
        }

        maxInRange[p] = max(maxInRange[p*2], maxInRange[p*2+1]);
        minInRange[p] = min(minInRange[p*2], minInRange[p*2+1]);

        //cout << i<<","<<j << " ==> " << minInRange[p] << " , " << maxInRange[p] << " , " << canReach[p].size() << ", " << canReach[p*2+1].size() << ", " << (canReach[p].empty() ? -1 : canReach[p].begin()->f) << endl;
        return changes;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> K;
    F0R(i, n) cin >> A[i];
    build(1, 0, n-1);

    vector<int> out;
    F0R(i, n) {
        ii opt = *canReach[1].begin();
        out.pb(opt.f);
        upd(1, 0, n-1, opt.s);
    }
    F0R(i, n) cout << out[i] << endl;

    return 0;
}
