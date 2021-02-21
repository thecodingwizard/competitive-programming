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

int ps[26][100001];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s; cin >> s;
    int n = s.length();
    string s2 = s;
    vector<int> end; end.pb(n-1);
    for (int i = 0; i < n; i++) {
        ps[s[i]-'a'][i+1]++;
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 1; j <= n; j++) {
            ps[i][j] += ps[i][j-1];
        }
    }
    vector<int> score;
    vector<char> st;
    for (int i = 0; i < n; i++) {
        if (!st.empty() && s[i] == st.back()) {
            st.pop_back();
        } else {
            st.push_back(s[i]);
        }
        score.pb(st.size());
    }
    if (!st.empty()) {
        cout << -1 << endl;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (s2[i] == '(' || s2[i] == ')') continue;
        while (end.back() <= i) end.pop_back();
        for (int j = end.back(); ~j; j--) {
            if (j <= i) {
                assert(false);
                return 0;
            }
            if (s[i] == s[j]) {
                bool good = true;
                for (int k = 0; k < 26; k++) {
                    if ((ps[k][j+1]-ps[k][i]) % 2 == 1) good = false;
                }
                if (score[j]!=score[i-1]) good = false;
                if (good) {
                    s2[i] = '(';
                    s2[j] = ')';
                    end.pb(j-1);
                    break;
                }
            }
        }
    }
    cout << s2 << endl;

    return 0;
}
