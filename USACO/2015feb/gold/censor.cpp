/*
 * Same solution as editorial, use rolling string hashes.
 *
 * At each location check every length that appears in the query; there are at most sqrt(N) such lengths
 * you need to check, so it runs in time.
 */

#include <bits/stdc++.h>

using namespace std;

#define mod 1000000007
#define ll long long

int pwr(int a, int b, int m) {
    if (b == 0) return 1;
    int p = pwr(a, b/2, m) % m;
    p = ((ll)p*p)%m;
    return (b%2 == 0) ? p : ((ll)a*p)%m;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

    string s; cin >> s;
    int n; cin >> n;

    int pow[100001];
    pow[0] = 1;
    for (int i = 1; i < 100001; i++) {
        pow[i] = ((ll)pow[i-1]*26) % mod;
    }
    int inv[100001];
    for (int i = 0; i < 100001; i++) {
        // calculate inverse of pow[i]
        inv[i] = pwr(pow[i], mod-2, mod);
    }

    set<int> censored[100001];
    vector<int> lengths;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        lengths.push_back(s.length());
        int hash = 0;
        for (int j = 0; j < (int)s.length(); j++) {
            hash = (hash + (ll)(s[j]-'a')*pow[j]) % mod;
        }
        censored[s.length()].insert(hash);
    }
    sort(lengths.begin(), lengths.end());
    lengths.erase(unique(lengths.begin(), lengths.end()), lengths.end());

    vector<int> hashes;
    vector<char> ans;
    hashes.push_back(0);
    for (int i = 0; i < (int)s.length(); i++) {
        hashes.push_back((hashes.back() + (ll)(s[i]-'a')*pow[hashes.size()-1]) % mod);
        ans.push_back(s[i]);

        for (int l : lengths) {
            if ((int)hashes.size() - l - 1 < 0) continue;
            int hsh = ((ll)(hashes.back() - hashes[(int)hashes.size() - l - 1] + mod) * inv[(int)hashes.size()-l-1]) % mod;
            if (censored[l].count(hsh)) {
                for (int j = 0; j < l; j++) {
                    hashes.pop_back();
                    ans.pop_back();
                }
                break;
            }
        }
    }

    for (char c : ans) cout << c;
    cout << "\n";

    return 0;
}
