#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

int n; 
set<string> features;
vector<string> populations[25];

bool check(string s, string t) {
    int onlyS = 0, onlyT = 0, both = 0;
    F0R(i, n) {
        bool isS = false, isT = false;
        for (string x : populations[i]) {
            if (x == s) isS = true;
            if (x == t) isT = true;
        }
        if (isS && !isT) onlyS++;
        if (!isS && isT) onlyT++;
        if (isS && isT) both++;
    }
    if (both == 0) return true;
    if (onlyS >= 0 && onlyT == 0) return true;
    if (onlyT >= 0 && onlyS == 0) return true;
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("evolution.in", "r", stdin);
    freopen("evolution.out", "w", stdout);

    cin >> n;
    F0R(i, n) {
        int x; cin >> x;
        F0R(j, x) {
            string s; cin >> s;
            features.insert(s);
            populations[i].push_back(s);
        }
    }

    for (string s : features) {
        for (string t : features) {
            if (!check(s, t)) {
                cout << "no" << endl;
                return 0;
            }
        }
    }

    cout << "yes" << endl;

    return 0;
}
