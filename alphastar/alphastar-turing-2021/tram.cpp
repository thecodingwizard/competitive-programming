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

int n, m; 
bool A[150][2];

vector<ii> spots;

void sit() {
    long double bestDist = -inf;
    ii best;
    F0R(i, n) {
        F0R(j, 2) {
            if (A[i][j]) continue;
            long double maxDist = inf;
            F0R(k, n) {
                F0R(l, 2) {
                    if (A[k][l]) {
                        maxDist = min(maxDist, sqrt((long double)abs(l-j)*abs(l-j)+abs(k-i)*abs(k-i)));
                    }
                }
            }
            if (bestDist < maxDist) {
                bestDist = maxDist;
                best = mp(i, j);
            }
        }
    }
    if (bestDist == -inf) best = mp(0, 0);
    spots.pb(best);
    A[best.f][best.s] = 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    F0R(i, m) {
        char c; cin >> c;
        if (c == 'E') {
            sit();
            cout << spots.back().f+1 << " " << spots.back().s+1 << endl;
        } else {
            int x; cin >> x; --x;
            A[spots[x].f][spots[x].s] = 0;
            spots.pb(mp(0, 0));
        }
    }

    return 0;
}
