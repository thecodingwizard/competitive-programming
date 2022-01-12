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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> A;
    for (int i = 0; i < m; i++) {
        int k; cin >> k;
        vector<int> tmp;
        for (int j = 0; j < k; j++) {
            int x; cin >> x;
            tmp.pb(x);
        }
        A.pb(tmp);
    }

    // conditions: shows up, stops showing up, shows up again
    // stuff above and stuff below must remain constant
    // stuff in the middle must remain constant
    // stuff can't be both above and in the middle
    // stuff in the middle must be entirely contained by me

    bool good = true;
    for (int i = 1; i <= n; i++) {
        // condition 1
        bool hasShownUp = false;
        bool hasFinishedShowingUp = false;
        for (auto &line : A) {
            if (find(all(line), i) != line.end()) {
                if (hasFinishedShowingUp) {
                    good = false;
                    //cerr << "cond 1" << endl;
                }
                hasShownUp = true;
            } else if (hasShownUp) {
                hasFinishedShowingUp = true;
            }
        }

        set<int> above, middle, below;
        for (auto &line : A) {
            vector<vector<int>> nums(4); // 0 = below, 1 = middle, 2 = above
            int idx = 0;
            for (int x : line) {
                if (x == i) idx++;
                else {
                    nums[idx].pb(x);
                }
            }
            if (idx == 2) {
                for (int x : nums[0]) below.insert(x);
                for (int x : nums[1]) middle.insert(x);
                for (int x : nums[2]) above.insert(x);
            }
        }
        for (int x : middle) {
            if (above.count(x) || below.count(x)) good = false;
            for (auto &line : A) {
                int idx = 0;
                vector<int> indices;
                for (int y : line) {
                    if (y == i) idx++;
                    if (y == x) {
                        indices.pb(idx);
                    }
                }
                if (indices.size() > 0 && idx == 0) good = false;
            }
        }
        for (int x : above) {
            if (below.count(x)) {
                // both
                for (auto &line : A) {
                    int idx = 0;
                    vector<int> indices;
                    for (int y : line) {
                        if (y == i) idx++;
                        if (y == x) {
                            indices.pb(idx);
                        }
                    }
                    if (indices.size() == 0) continue;
                    if (idx == 0) continue;
                    if (indices[0] != 0 || indices[1] != 2) good = false;
                }
            } else {
                for (auto &line : A) {
                    int idx = 0;
                    vector<int> indices;
                    for (int y : line) {
                        if (y == i) idx++;
                        if (y == x) {
                            indices.pb(idx);
                        }
                    }
                    if (indices.size() == 0) continue;
                    if (idx == 0) continue;
                    if (indices[0] != 2 || indices[1] != 2) good = false;
                }
            }
        }
        for (int x : below) {
            if (above.count(x)) {
                // both
                for (auto &line : A) {
                    int idx = 0;
                    vector<int> indices;
                    for (int y : line) {
                        if (y == i) idx++;
                        if (y == x) {
                            indices.pb(idx);
                        }
                    }
                    if (indices.size() == 0) continue;
                    if (idx == 0) continue;
                    if (indices[0] != 0 || indices[1] != 2) good = false;
                }
            } else {
                for (auto &line : A) {
                    int idx = 0;
                    vector<int> indices;
                    for (int y : line) {
                        if (y == i) idx++;
                        if (y == x) {
                            indices.pb(idx);
                        }
                    }
                    if (indices.size() == 0) continue;
                    if (idx == 0) continue;
                    if (indices[0] != 0 || indices[1] != 0) good = false;
                }
            }
        }
    }
    cout << (good ? "YES" : "NO") << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
