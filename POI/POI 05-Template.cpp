/*
 * Define pi[x] = longest prefix of s[0...x] that's also a suffix of s[0...x]
 *
 * We can make a list of all possible templates (a template has to be a prefix
 * and a suffix of the whole string). Then, we try the shortest possible template
 * first. To test to see if a template works, we can just greedily
 * stamp the template whenever we can (use the pi array to speed things up).
 * If a template works, output the length; otherwise, the next template we try
 * should be more than 2x the length of our current template. If it's less than
 * 2x the length of our current template, then we know for sure it won't work.
 * Hence, we only have to try log n templates.
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

string s; 

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s; int n = s.size();
    int pref[n]; pref[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = pref[i-1];
        while (j > 0 && s[i] != s[j]) {
            j = pref[j-1];
        }
        if (s[i] == s[j]) j++;
        pref[i] = j;
    }

    vector<int> lengths;
    int x = pref[n-1];
    while (x >= 1) {
        lengths.pb(x);
        x = pref[x-1];
    }
    reverse(all(lengths));

    int idx = 0;
    while (idx < lengths.size()) {
        int curLen = lengths[idx];
        int prevGood = 2*curLen-1;
        bool good = 1;
        for (int i = 0; i < n; i++) {
            if (pref[i] >= curLen) {
                if (prevGood < i) good = 0;
                prevGood = i + curLen;
            }
        }
        if (good) {
            cout << lengths[idx] << endl;
            return 0;
        }
        while (idx < lengths.size() && lengths[idx] < curLen*2) idx++;
    }
    
    cout << n << endl;

    return 0;
}
