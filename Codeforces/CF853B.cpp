#include <bits/stdc++.h> // see /general/running-code-locally
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

void setIO(string name = "") {
	cin.tie(0)->sync_with_stdio(0); // see /general/fast-io
	if (sz(name)) {
		freopen((name+".in").c_str(), "r", stdin); // see /general/io
		freopen((name+".out").c_str(), "w", stdout);
	}
}

struct flight {
    int day, from, to, cost;
};
bool operator<(flight a, flight b) {
    return a.day < b.day;
}

int n, m, k;
vector<flight> flights;
ll enterCost[100001];
multiset<ll> exitCost[100001];

int main() {
	setIO();
	
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        enterCost[i] = 1e13;
        exitCost[i].insert(1e13);
    }
    for (int i = 0; i < m; i++) {
        int d, f, t, c; cin >> d >> f >> t >> c;
        flights.pb({d,f,t,c});
    }
    sort(all(flights));

    ll bestCost = 1e18;
    ll curCost = 0;
    // initially all exit flights are usable
    for (int i = 0; i < m; i++) {
        if (flights[i].from == 0) {
            exitCost[flights[i].to].insert(flights[i].cost);
        }
    }
    for (int i = 1; i <= n; i++) {
        curCost += enterCost[i];
        curCost += *exitCost[i].begin();
    }

    // these pointers are inclusive
    int lptr = -1, rptr = 0;
    while (lptr + 1 < m) {
        lptr++;
        // add flight lptr
        if (enterCost[flights[lptr].from] > flights[lptr].cost) {
            curCost -= enterCost[flights[lptr].from];
            enterCost[flights[lptr].from] = flights[lptr].cost;
            curCost += enterCost[flights[lptr].from];
        }

        // move rptr until the time between lptr and rptr is > k
        while (rptr < m && flights[rptr].day - flights[lptr].day <= k) {
            if (flights[rptr].to != 0) {
                // this is a return flight that we can no longer use
                curCost -= *exitCost[flights[rptr].to].begin();
                exitCost[flights[rptr].to].erase(exitCost[flights[rptr].to].find(flights[rptr].cost));
                curCost += *exitCost[flights[rptr].to].begin();
            }
            rptr++;
        }

        bestCost = min(bestCost, curCost);
    }

    if (bestCost >= 1e13) {
        // max cost is n*max_c*2
        cout << -1 << endl;
    } else {
        cout << bestCost << endl;
    }
}
